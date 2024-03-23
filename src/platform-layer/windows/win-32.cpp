#include <windows.h>
#include <stdio.h>

#include "..\..\tanks.h"
#include "win-32.h"

#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1080

GlobalVariable bool32 IS_RUNNING = false;
GlobalVariable bool32 IS_PAUSED  = false;
GlobalVariable BackBuffer BACK_BUFFER;
GlobalVariable int64 PERFORMANCE_COUNTER_FREQUENCY;
GlobalVariable bool32 SOUND_IS_VALID = false;

GlobalVariable DWORD LAST_PLAY_CURSOR = 0;

inline LARGE_INTEGER GetCounterStamp()
{
    LARGE_INTEGER result;

    QueryPerformanceCounter(&result);

    return result;
}

inline real32 GetSecondsElapsed(LARGE_INTEGER start, LARGE_INTEGER end)
{
    real32 diff = (real32)(end.QuadPart - start.QuadPart);
    real32 result = diff / (real32)PERFORMANCE_COUNTER_FREQUENCY;

    return result;
}

Internal void CatStrings(char* source_a, size_t source_a_count,
    char* source_b, size_t source_b_count,
    char* destination, size_t destination_count)
{
    for (int i = 0; i < source_a_count; ++i)
        *destination++ = *source_a++;

    for (int i = 0; i < source_b_count; ++i)
        *destination++ = *source_b++;

    *destination++ = 0;
}

Internal int StringLength(char* string)
{
    int count = 0;
    if (string) while(*string++) ++count;

    return count;
}

Internal char* GetPathBasenameSubstring(char* path)
{
    char* basename = path;
    for (char* symbol = path; *symbol; ++symbol)
    {
        if (*symbol == '\\') basename = symbol + 1;
    }

    return basename;
}

void FreeFileMemory(ThreadContext* thread, void* memory)
{
    if (!memory) return;

    VirtualFree(memory, 0, MEM_RELEASE);
}

ReadFileResult ReadFile(ThreadContext* thread, char* filename)
{
    ReadFileResult result = {};
    result.Size = 0;
    result.Content = 0;

    FileData file = {};

    HANDLE handle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0,
        OPEN_EXISTING, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) return result;

    LARGE_INTEGER size;
    if (!GetFileSizeEx(handle, &size)) return result;

    uint32 size32 = TruncateUInt64(size.QuadPart);
    file.Content = VirtualAlloc(0, size32, MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE);
    if (!file.Content) return result;

    DWORD bytes_read;
    if (ReadFile(handle, file.Content, size32, &bytes_read, 0)
        && (bytes_read == size32))
    {
        file.Size = size32;
        result.Size = size32;
        result.Content = file.Content;
    }
    else
    {
        FreeFileMemory(thread, file.Content);
        file.Content = 0;
        result.Content = 0;
    }

    CloseHandle(handle);

    return result;
}

bool32 WriteFile(ThreadContext* thread, char* filename, uint32 size,
    void *memory)
{
    bool32 result = false;

    HANDLE handle = CreateFileA(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) return result;

    DWORD bytes_written;
    if(WriteFile(handle, memory, size, &bytes_written, 0))
        result = (bytes_written == size);

    CloseHandle(handle);

    return result;
}

#include "input.h"
#include "audio.h"

Internal FILETIME GetLastEditTime(char* filepath)
{
    FILETIME write_time = {};

    WIN32_FILE_ATTRIBUTE_DATA data;
    if (GetFileAttributesEx(filepath, GetFileExInfoStandard, &data))
        write_time = data.ftLastWriteTime;

    return write_time;
}

Internal GameCode LoadGameCode(char* dll_filename, char* dll_temp_filename)
{
    GameCode result = {};

    CopyFile(dll_filename, dll_temp_filename, FALSE);

    result.DllLastEditTime = GetLastEditTime(dll_filename);
    result.Dll = LoadLibrary(dll_temp_filename);

    if (result.Dll)
    {
        result.UpdateAndRender = (FPtrUpdateAndRender*)GetProcAddress(
            result.Dll, "UpdateAndRender");
        result.GetSoundSamples = (FPtrGetSoundSamples*)GetProcAddress(
            result.Dll, "GetSoundSamples");

        result.IsValid = (result.UpdateAndRender && result.GetSoundSamples);
    }

    if (!result.IsValid)
    {
        result.UpdateAndRender = 0;
        result.GetSoundSamples = 0;
    }

    return result;
}

Internal void UnloadGameCode(GameCode* game_code)
{
    if (game_code->Dll)
    {
        FreeLibrary(game_code->Dll);
        game_code->Dll = 0;
    }

    game_code->IsValid = false;
    game_code->UpdateAndRender = 0;
    game_code->GetSoundSamples = 0;
}

Internal void ResizeBuffer(BackBuffer *buffer, int width, int height)
{
    if (buffer->Memory) VirtualFree(buffer->Memory, 0, MEM_RELEASE);

    int bytes_per_pixel = 4;

    buffer->Width = width;
    buffer->Height = height;
    buffer->BytesPerPixel = bytes_per_pixel;

    buffer->Info.bmiHeader.biSize = sizeof(buffer->Info.bmiHeader);
    buffer->Info.bmiHeader.biWidth = buffer->Width;
    buffer->Info.bmiHeader.biHeight = -buffer->Height;
    buffer->Info.bmiHeader.biPlanes = 1;
    buffer->Info.bmiHeader.biBitCount = 32;
    buffer->Info.bmiHeader.biCompression = BI_RGB;

    int memory_size = (buffer->Width * buffer->Height) * bytes_per_pixel;
    buffer->Memory = VirtualAlloc(0, memory_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    buffer->Pitch = width * bytes_per_pixel;
}

Internal WindowDimension GetWindowDimension(HWND window)
{
    WindowDimension dimension;

    RECT client_rect;
    GetClientRect(window, &client_rect);
    dimension.Width  = client_rect.right - client_rect.left;
    dimension.Height = client_rect.bottom - client_rect.top;

    return dimension;
}

Internal void DisplayBufferInWindow(BackBuffer *buffer, HDC device_context,
    int window_width, int window_height)
{
    StretchDIBits(
        device_context,
        0, 0, window_width, window_height,
        0, 0, buffer->Width, buffer->Height,
        buffer->Memory,
        &buffer->Info,
        DIB_RGB_COLORS, SRCCOPY);
}

Internal LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM w_param,
    LPARAM l_param)
{
    LRESULT result = 0;
    switch (message)
    {
        case WM_CLOSE:
        {
            IS_RUNNING = false;
        } break;

        case WM_QUIT:
        {
            IS_RUNNING = false;
        } break;

        case WM_DESTROY:
        {
            IS_RUNNING = false;
        } break;

        case WM_ACTIVATEAPP:
        {
            // if (w_param == TRUE)
                SetLayeredWindowAttributes(window, RGB(0,0,0), 255, LWA_ALPHA);
            // else
            //     SetLayeredWindowAttributes(window, RGB(0,0,0), 64, LWA_ALPHA);
        } break;

        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC device_context = BeginPaint(window, &paint);

            WindowDimension dimension = GetWindowDimension(window);
            DisplayBufferInWindow(&BACK_BUFFER, device_context, dimension.Width,
                dimension.Height);

            EndPaint(window, &paint);
        } break;

        default:
        {
            result = DefWindowProcA(window, message, w_param, l_param);
        } break;
    }

    return result;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int cmd_size)
{
    WindowsState windows_state = {};

    LARGE_INTEGER performance_counter_frequency;
    QueryPerformanceFrequency(&performance_counter_frequency);
    PERFORMANCE_COUNTER_FREQUENCY = performance_counter_frequency.QuadPart;

    DWORD exe_filepath_length = GetModuleFileName(0, windows_state.ExeFilepath,
        sizeof(windows_state.ExeFilepath));
    windows_state.ExeBasename = GetPathBasenameSubstring(
        windows_state.ExeFilepath);

    char dll_basename[] = "tanks.dll";
    char dll_filepath[MAX_PATH];
    CatStrings(windows_state.ExeFilepath,
        windows_state.ExeBasename - windows_state.ExeFilepath,
        dll_basename, sizeof(dll_basename) - 1,
        dll_filepath, sizeof(dll_filepath));

    char dll2load_basename[] = "tanks_tmp.dll";
    char dll2load_filepath[MAX_PATH];
    CatStrings(windows_state.ExeFilepath,
        windows_state.ExeBasename - windows_state.ExeFilepath,
        dll2load_basename, sizeof(dll2load_basename) - 1,
        dll2load_filepath, sizeof(dll2load_filepath));

    UINT desired_scheduler_ms = 1;
    bool32 sleep_is_granular = (timeBeginPeriod(desired_scheduler_ms)
        == TIMERR_NOERROR);

    IS_RUNNING = false;
    LoadXInput();

    ResizeBuffer(&BACK_BUFFER, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Register the window class.
    const char CLASS_NAME[]   = "Tanks";
    const char WINDOW_TITLE[] = "Tanks";

    WNDCLASS window_class = { };
    window_class.style         = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc   = WindowProc;
    window_class.hInstance     = instance;
    window_class.lpszClassName = CLASS_NAME;

    RegisterClass(&window_class);

    // Create the window.
    HWND window = CreateWindowExA(
        0, // WS_EX_TOPMOST | WS_EX_LAYERED,
        CLASS_NAME,
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,
        NULL,
        instance,
        NULL
    );

    if (window == NULL) return 0;

    int monitor_refresh_rate = 60;
    HDC refresh_dc = GetDC(window);
    int refresh_rate = GetDeviceCaps(refresh_dc, VREFRESH);
    ReleaseDC(window, refresh_dc);
    if (refresh_rate > 1)
        monitor_refresh_rate = refresh_rate;
    int game_update_hz = monitor_refresh_rate / 2;
    real32 target_seconds_per_frame = 1.0f / (real32)game_update_hz;

    SoundOutput sound_output = {};
    sound_output.SamplesPerSecond = 48000;
    sound_output.BytesPerSample = sizeof(int16) * 2;
    sound_output.BufferSize = sound_output.SamplesPerSecond
        * sound_output.BytesPerSample;
    sound_output.LatencySampleCount = 3
        * (sound_output.SamplesPerSecond / game_update_hz);
    sound_output.SafetyBytes = (int)(((real32)sound_output.SamplesPerSecond
        * (real32)sound_output.BytesPerSample / game_update_hz) / 3);
    InitDirectSound(window, sound_output.SamplesPerSecond,
        sound_output.BufferSize);
    ClearSoundBuffer(&sound_output);
    SOUND_BUFFER->Play(0, 0, DSBPLAY_LOOPING);

    int16 *samples = (int16 *)VirtualAlloc(
        0, sound_output.BufferSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!samples) return 0;

    LPVOID base_address = 0;
    GameMemory game_memory = {};
    game_memory.PermanentStorageSize = MEGABYTES(64);
    game_memory.TransientStorageSize = GIGABYTES(1);
    game_memory.FreeFileMemory = FreeFileMemory;
    game_memory.ReadFile = ReadFile;
    game_memory.WriteFile = WriteFile;

    windows_state.TotalSize = game_memory.PermanentStorageSize
        + game_memory.TransientStorageSize;
    windows_state.GameMemory = VirtualAlloc(
        base_address,
        (size_t)windows_state.TotalSize,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE);

    game_memory.PermanentStorage = windows_state.GameMemory;
    game_memory.TransientStorage = ((uint8 *)game_memory.PermanentStorage
        + game_memory.PermanentStorageSize);

    if (!game_memory.PermanentStorage
        || !game_memory.TransientStorage) return 0;

    for (int i = 0; i < ArrayCount(windows_state.InputReplayBuffers); ++i)
    {
        InputReplayBuffer *buffer = &windows_state.InputReplayBuffers[i];
        GetInputRecordsFilepath(&windows_state, false, i, buffer->Filepath,
            sizeof(buffer->Filepath));

        buffer->FileHandle = CreateFileA(buffer->Filepath,
            GENERIC_WRITE|GENERIC_READ, 0, 0, CREATE_ALWAYS, 0, 0);

        LARGE_INTEGER max_size;
        max_size.QuadPart = windows_state.TotalSize;
        buffer->MemoryMap = CreateFileMapping(
            buffer->FileHandle, 0, PAGE_READWRITE,
            max_size.HighPart, max_size.LowPart, 0);

        buffer->Memory = MapViewOfFile(
            buffer->MemoryMap, FILE_MAP_ALL_ACCESS, 0, 0,
            windows_state.TotalSize);

        if(buffer->Memory)
        {
        }
        else
        {
        }
    }


    GameInput inputs[2] = {};
    GameInput* new_input = &inputs[0];
    GameInput* old_input = &inputs[1];

    LARGE_INTEGER counter_frame_start = GetCounterStamp();
    LARGE_INTEGER counter_frame_flip  = GetCounterStamp();
    uint64 cpu_frame_start = __rdtsc();

    int time_marker_index = 0;
    TimeMarker time_markers[30] =  {{}, {}};

    uint32 game_code_load_time = 0;
    GameCode game_code = LoadGameCode(dll_filepath, dll2load_filepath);

    SOUND_IS_VALID = false;
    IS_RUNNING = true;
    while (IS_RUNNING)
    {
        FILETIME dll_last_edit_time = GetLastEditTime(dll_filepath);
        if (CompareFileTime(&dll_last_edit_time, &game_code.DllLastEditTime) != 0)
        {
            UnloadGameCode(&game_code);
            game_code = LoadGameCode(dll_filepath, dll2load_filepath);

            game_code_load_time = 0;
        }

        ControllerState* keyboard_old = GetController(old_input, 0);
        ControllerState* keyboard_new = GetController(new_input, 0);
        *keyboard_new = {};
        keyboard_new->IsConnected = true;

        int32 all_buttons = ArrayCount(keyboard_new->Buttons);
        for (int button_index = 0; button_index < all_buttons; ++button_index)
        {
            keyboard_new->Buttons[button_index].EndedDown =
                keyboard_old->Buttons[button_index].EndedDown;
        }

        ProcessMouse(window, new_input);
        ProcessKeyboard(&windows_state, keyboard_new);
        ProcessGamepadStates(old_input, new_input);

        if (IS_PAUSED) continue;

        ThreadContext thread = {};

        GameBackBuffer game_buffer = {};
        game_buffer.Memory        = BACK_BUFFER.Memory;
        game_buffer.Height        = BACK_BUFFER.Height;
        game_buffer.Width         = BACK_BUFFER.Width;
        game_buffer.Pitch         = BACK_BUFFER.Pitch;
        game_buffer.BytesPerPixel = BACK_BUFFER.BytesPerPixel;

        if (windows_state.InputRecordingIndex)
            InputRecordWrite(&windows_state, new_input);

        if (windows_state.InputPlaybackIndex)
            InputRecordRead(&windows_state, new_input);

        if (game_code.UpdateAndRender)
            game_code.UpdateAndRender(&thread, &game_memory, new_input, &game_buffer);

        CorrectAndOutputSound(
            &thread,
            counter_frame_flip,
            &sound_output,
            game_update_hz,
            target_seconds_per_frame,
            samples,
            &game_memory,
            time_markers,
            time_marker_index,
            &game_code);

        LARGE_INTEGER counter_work_end = GetCounterStamp();
        real32 seconds_elapsed_work = GetSecondsElapsed(
            counter_frame_start,
            counter_work_end);

        real32 seconds_elapsed_for_frame = seconds_elapsed_work;
        if (seconds_elapsed_for_frame < target_seconds_per_frame)
        {
            if (sleep_is_granular)
            {
                real32 remaining_seconds_for_frame = target_seconds_per_frame
                    - seconds_elapsed_for_frame;
                DWORD sleep_ms = (DWORD)(1000.0f * remaining_seconds_for_frame);

                if (sleep_ms > 0) Sleep(sleep_ms);
            }

            real32 test_seconds_elapsed_for_frame = GetSecondsElapsed(
                counter_frame_start, GetCounterStamp());
            Assert(test_seconds_elapsed_for_frame < target_seconds_per_frame);

            while (seconds_elapsed_for_frame < target_seconds_per_frame)
                seconds_elapsed_for_frame = GetSecondsElapsed(
                    counter_frame_start, GetCounterStamp());
        }
        else
        {
            // TODO: Log error; Missed frame rate;
        }

        LARGE_INTEGER counter_frame_end = GetCounterStamp();
        real32 ms_per_frame = 1000.0f * GetSecondsElapsed(counter_frame_start, counter_frame_end);
        counter_frame_start = counter_frame_end;

        WindowDimension dimension = GetWindowDimension(window);

        HDC device_context = GetDC(window);
        DisplayBufferInWindow(
            &BACK_BUFFER,
            device_context,
            dimension.Width,
            dimension.Height);
        counter_frame_flip = GetCounterStamp();
        ReleaseDC(window, device_context);

#if WIN32_DEBUG_SOUND

        DWORD play_cursor;
        DWORD write_cursor;
        // TODO: Handle all errors
        if (SOUND_BUFFER->GetCurrentPosition(&play_cursor, &write_cursor) == DS_OK)
        {
            Assert(time_marker_index < ArrayCount(time_markers));
            TimeMarker* marker = &time_markers[time_marker_index];
            marker->FlipPlayCursor = play_cursor;
            marker->FlipWriteCursor = write_cursor;
        }

#endif

        GameInput* temp = new_input;
        new_input = old_input;
        old_input = temp;

        uint64 cpu_frame_end = __rdtsc();
        uint64 cycles_elapsed = cpu_frame_end - cpu_frame_start;
        cpu_frame_start = cpu_frame_end;

        real64 fps = 0.0f;
        real64 mc_per_frame = (real64)cycles_elapsed / (1000.0f * 1000.0f);

        char dbg_msg_buffer[256];
        sprintf_s(dbg_msg_buffer, "%.02fms/f,  %.02ff/s,  %.02fmc/f\n", ms_per_frame, fps, mc_per_frame);
        OutputDebugStringA(dbg_msg_buffer);

        ++time_marker_index;
        if (time_marker_index == ArrayCount(time_markers))
            time_marker_index = 0;
    }

    return 0;
}
