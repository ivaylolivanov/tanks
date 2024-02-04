#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "win-32.h"
#include "dsound.h"

#include "..\..\tanks.h"
#include "..\..\tanks.cpp"

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

#include "input.h"
#include "audio.h"

Internal void FreeFileMemory(void* memory)
{
    if (!memory) return;

    VirtualFree(memory, 0, MEM_RELEASE);
}

Internal FileData ReadFile(char* filename)
{
    FileData file = {};

    HANDLE handle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0,
        OPEN_EXISTING, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) return file;

    LARGE_INTEGER size;
    if (!GetFileSizeEx(handle, &size)) return file;

    uint32 size32 = TruncateUInt64(size.QuadPart);
    file.Content = VirtualAlloc(0, size32, MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE);
    if (!file.Content) return file;

    DWORD bytes_read;
    if (ReadFile(handle, file.Content, size32, &bytes_read, 0)
        && (bytes_read == size32))
    {
        file.Size = size32;
    }
    else
    {
        FreeFileMemory(file.Content);
        file.Content = 0;
    }

    CloseHandle(handle);

    return file;
}

Internal bool32 WriteFile(char* filename, void *memory, uint32 size)
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
            OutputDebugStringA("WM_ACTIVATEAPP\n");
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
    LARGE_INTEGER performance_counter_frequency;
    QueryPerformanceFrequency(&performance_counter_frequency);
    PERFORMANCE_COUNTER_FREQUENCY = performance_counter_frequency.QuadPart;

    UINT desired_scheduler_ms = 1;
    bool32 sleep_is_granular = (timeBeginPeriod(desired_scheduler_ms)
        == TIMERR_NOERROR);

    IS_RUNNING = false;
    LoadXInput();

    ResizeBuffer(&BACK_BUFFER, 1280, 720);

    // Register the window class.
    const char CLASS_NAME[]   = "Tanks";
    const char WINDOW_TITLE[] = "Tanks";

    WNDCLASS window_class = { };
    window_class.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc   = WindowProc;
    window_class.hInstance     = instance;
    window_class.lpszClassName = CLASS_NAME;

    RegisterClass(&window_class);

    int monitor_refresh_rate = 60;
    // TODO: Check if this is reliabled enough
    /* Disabled until checked
    DEVMODE devmode;
    devmode.dmSize = sizeof(devmode);
    if (EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &devmode) != 0)
        monitor_refresh_rate = devmode.dmDisplayFrequency;
    */
    int game_update_hz = monitor_refresh_rate / 2;
    real32 target_seconds_per_frame = 1.0f / (real32)game_update_hz;

    // Create the window.
    HWND window = CreateWindowExA(
        NULL,
        CLASS_NAME,
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        instance,
        NULL
    );

    if (window == NULL) return 0;

    HDC device_context = GetDC(window);

    SoundOutput sound_output = {};
    sound_output.SamplesPerSecond = 48000;
    sound_output.BytesPerSample = sizeof(int16) * 2;
    sound_output.BufferSize = sound_output.SamplesPerSecond
        * sound_output.BytesPerSample;
    sound_output.LatencySampleCount = 3
        * (sound_output.SamplesPerSecond / game_update_hz);
    sound_output.SafetyBytes = (sound_output.SamplesPerSecond
        * sound_output.BytesPerSample / game_update_hz) / 3;
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

    uint64 total_size = game_memory.PermanentStorageSize
        + game_memory.TransientStorageSize;
    game_memory.PermanentStorage = VirtualAlloc(
        base_address,
        (size_t)total_size,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE);

    game_memory.TransientStorage = ((uint8 *)game_memory.PermanentStorage
        + game_memory.PermanentStorageSize);

    if (!game_memory.PermanentStorage
        || !game_memory.TransientStorage) return 0;

    GameInput inputs[2] = {};
    GameInput* new_input = &inputs[0];
    GameInput* old_input = &inputs[1];

    LARGE_INTEGER counter_frame_start = GetCounterStamp();
    LARGE_INTEGER counter_frame_flip  = GetCounterStamp();
    uint64 cpu_frame_start = __rdtsc();

    /* TODO: Find way to do it dynamically; Probably like this: ?
    int time_markers_size = game_update_hz / 2;
    TimeMarker* time_markers = (TimeMarker*)VirtualAlloc(0, time_markers_size,
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0; i < time_markers_size; ++i)
        time_markers[i] = {0};
     */
    // TODO: With size 15, the game crashes
    int time_marker_index = 0;
    TimeMarker time_markers[30] =  {{}, {}};

    SOUND_IS_VALID = false;
    IS_RUNNING = true;
    while (IS_RUNNING)
    {
        ControllerState* keyboard_old = GetController(old_input, 0);
        ControllerState* keyboard_new = GetController(new_input, 0);
        *keyboard_new = {};
        keyboard_new->IsConnected = true;

        // TODO: Find a better way ?
        int32 all_buttons = ArrayCount(keyboard_new->Buttons);
        for (int button_index = 0; button_index < all_buttons; ++button_index)
        {
            keyboard_new->Buttons[button_index].EndedDown =
                keyboard_old->Buttons[button_index].EndedDown;
        }

        ProcessKeyboard(keyboard_new);
        ProcessGamepadStates(old_input, new_input);

        if (IS_PAUSED) continue;

        GameBackBuffer game_buffer = {};
        game_buffer.Memory        = BACK_BUFFER.Memory;
        game_buffer.Height        = BACK_BUFFER.Height;
        game_buffer.Width         = BACK_BUFFER.Width;
        game_buffer.Pitch         = BACK_BUFFER.Pitch;
        game_buffer.BytesPerPixel = BACK_BUFFER.BytesPerPixel;
        UpdateAndRender(&game_memory, new_input, &game_buffer);

        CorrectAndOutputSound(
            counter_frame_flip,
            &sound_output,
            game_update_hz,
            target_seconds_per_frame,
            samples,
            &game_memory,
            time_markers,
            time_marker_index);

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

#if WIN32_DEBUG_SOUND

        DebugSyncDisplay(&BACK_BUFFER, ArrayCount(time_markers),
            time_marker_index - 1, time_markers, &sound_output,
            target_seconds_per_frame);

#endif

        DisplayBufferInWindow(
            &BACK_BUFFER,
            device_context,
            dimension.Width,
            dimension.Height);
        counter_frame_flip = GetCounterStamp();

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
        sprintf(dbg_msg_buffer, "%.02fms/f,  %.02ff/s,  %.02fmc/f\n", ms_per_frame, fps, mc_per_frame);
        OutputDebugStringA(dbg_msg_buffer);

        ++time_marker_index;
        if (time_marker_index == ArrayCount(time_markers))
            time_marker_index = 0;
    }

    return 0;
}
