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

GlobalVariable DWORD LAST_PLAY_CURSOR = 0;

#include "input.h"

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

#if WIN32_DEBUG

Internal void DrawVertical(BackBuffer* buffer, int x, int top, int bottom, uint32 color)
{
    if (top < 0) top = 0;
    if (bottom > buffer->Height) bottom = buffer->Height;

    if (x < 0 || x > buffer->Width) return;

    uint8* pixel = ((uint8*)buffer->Memory +
        x * buffer->BytesPerPixel +
        top * buffer->Pitch);

    for (int y = top; y < bottom; ++y)
    {
        *(uint32 *)pixel = color;
        pixel += buffer->Pitch;
    }
}

inline void DrawSoundBufferMarker(BackBuffer* buffer, SoundOutput* sound_output, real32 c, int pad_x, int top, int bottom, DWORD value, uint32 color)
{
    real32 x_real32 = (c * (real32)value);
    int x = pad_x + (int)x_real32;
    DrawVertical(buffer, x, top, bottom, color);
}

Internal void DebugSyncDisplay(BackBuffer* buffer, int markers_count, int current_marker_index, TimeMarker* markers, SoundOutput* sound_output, real32 target_seconds_per_frame)
{
    int pad_x = 16;
    int pad_y = 16;

    int line_height = 64;

    real32 c = (real32)(buffer->Width - 2 * pad_x) / (real32)sound_output->BufferSize;
    for(int marker_index = 0; marker_index < markers_count; ++marker_index)
    {
        TimeMarker* marker = &markers[marker_index];

        Assert(marker->OutputPlayCursor  < sound_output->BufferSize);
        Assert(marker->OutputWriteCursor < sound_output->BufferSize);
        Assert(marker->OutputLocation    < sound_output->BufferSize);
        Assert(marker->OutputByteCount   < sound_output->BufferSize);
        Assert(marker->FlipPlayCursor    < sound_output->BufferSize);
        Assert(marker->FlipWriteCursor   < sound_output->BufferSize);

        DWORD play_color = 0xFFFFFFFF;
        DWORD write_color = 0xFFFF0000;
        DWORD expected_flip_color = 0xFFFFFF00;
        DWORD play_window_color = 0xFFFF00FF;

        int top = pad_y;
        int bottom = pad_y + line_height;
        if(marker_index == current_marker_index)
        {
            top += line_height + pad_y;
            bottom += line_height + pad_y;

            int first_top = top;

            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputPlayCursor, play_color);
            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputWriteCursor, write_color);

            top += line_height + pad_y;
            bottom += line_height +pad_y;

            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputLocation, play_color);
            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputLocation + marker->OutputByteCount, write_color);

            top += line_height + pad_y;
            bottom += line_height + pad_y;

            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, first_top, bottom, marker->ExpectedFlipPlayCursor, expected_flip_color);
        }

        DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->FlipPlayCursor, play_color);
        DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->FlipPlayCursor + 480 * sound_output->BytesPerSample, play_window_color);
        DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->FlipWriteCursor, write_color);
    }
}

#endif

Internal void ClearSoundBuffer(SoundOutput *sound_output)
{
    VOID *region1;
    DWORD region1_size;
    VOID *region2;
    DWORD region2_size;

    HRESULT buffer_lock_result = SOUND_BUFFER->Lock(
        0, sound_output->BufferSize,
        &region1, &region1_size,
        &region2, &region2_size,
        0);
    if (FAILED(buffer_lock_result))
        return;

    uint8 *destination_sample = (uint8 *)region1;
    for (DWORD byte_index = 0; byte_index < region1_size; ++byte_index)
        *destination_sample++ = 0;

    destination_sample = (uint8 *)region2;
    for (DWORD byte_index = 0; byte_index < region2_size; ++byte_index)
        *destination_sample++ = 0;

    SOUND_BUFFER->Unlock(region1, region1_size, region2, region2_size);
}

Internal void FillSoundBuffer(SoundOutput *sound_output, DWORD byte_to_lock,
    DWORD bytes_to_write, GameSoundBuffer *game_sound_buffer)
{
    VOID *region1;
    DWORD region1_size;
    VOID *region2;
    DWORD region2_size;

    HRESULT buffer_lock_result = SOUND_BUFFER->Lock(
        byte_to_lock, bytes_to_write,
        &region1, &region1_size,
        &region2, &region2_size,
        0);
    if (FAILED(buffer_lock_result))
        return;

    int16 *source_sample = game_sound_buffer->Samples;

    DWORD region1_samples = region1_size / sound_output->BytesPerSample;
    int16 *destination_sample = (int16 *)region1;
    for (DWORD sample_index = 0; sample_index < region1_samples; ++sample_index)
    {
        *destination_sample++ = *source_sample++;
        *destination_sample++ = *source_sample++;

        ++sound_output->RunningSampleIndex;
    }

    DWORD region2_samples = region2_size / sound_output->BytesPerSample;
    destination_sample = (int16 *)region2;
    for (DWORD sample_index = 0; sample_index < region2_samples; ++sample_index)
    {
        *destination_sample++ = *source_sample++;
        *destination_sample++ = *source_sample++;

        ++sound_output->RunningSampleIndex;
    }

    SOUND_BUFFER->Unlock(region1, region1_size, region2, region2_size);
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

    if (!game_memory.PermanentStorage || !game_memory.TransientStorage) return 0;

    GameInput inputs[2] = {};
    GameInput* new_input = &inputs[0];
    GameInput* old_input = &inputs[1];

    LARGE_INTEGER counter_stamp_frame_start = GetCounterStamp();
    LARGE_INTEGER counter_stamp_frame_flip  = GetCounterStamp();
    uint64 cpu_clock_cycles_frame_start = __rdtsc();

    int time_marker_index = 0;
    int time_markers_size = game_update_hz / 2;
    /* TODO: Find way to do it dynamically; Probably like this: ?
    TimeMarker* time_markers = (TimeMarker*)VirtualAlloc(0, time_markers_size,
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0; i < time_markers_size; ++i)
        time_markers[i] = {0};
     */
    // TODO: With size 15, the game crashes
    TimeMarker time_markers[30] =  {{0}, {0}};
    DWORD audio_latency_bytes = 0;
    real32 audio_latency_seconds = 0;
    bool is_sound_valid = false;

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
        game_buffer.Memory = BACK_BUFFER.Memory;
        game_buffer.Height = BACK_BUFFER.Height;
        game_buffer.Width  = BACK_BUFFER.Width;
        game_buffer.Pitch  = BACK_BUFFER.Pitch;
        UpdateAndRender(&game_memory, new_input, &game_buffer);

        LARGE_INTEGER counter_stamp_audio_start = GetCounterStamp();
        real32 seconds_elapsed_before_audio = GetSecondsElapsed(
            counter_stamp_frame_flip, counter_stamp_audio_start);

        DWORD play_cursor;
        DWORD write_cursor;
        if (SOUND_BUFFER->GetCurrentPosition(&play_cursor, &write_cursor) == DS_OK)
        {
            LAST_PLAY_CURSOR = play_cursor;
            if (!is_sound_valid)
            {
                sound_output.RunningSampleIndex = write_cursor / sound_output.BytesPerSample;
                is_sound_valid = true;
            }

            DWORD byte_to_lock = (sound_output.RunningSampleIndex
                * sound_output.BytesPerSample) % sound_output.BufferSize;
            DWORD expected_sound_bytes_per_frame = (sound_output.SamplesPerSecond
                * sound_output.BytesPerSample) / game_update_hz;
            real32 seconds_left_until_flip = target_seconds_per_frame
                - seconds_elapsed_before_audio;
            DWORD expected_bytes_until_flip = (DWORD)((seconds_left_until_flip
                / target_seconds_per_frame) * (expected_sound_bytes_per_frame));
            DWORD expected_frame_boundary_byte = play_cursor
                + expected_sound_bytes_per_frame;

            DWORD safe_write_cursor = write_cursor;
            if (safe_write_cursor < play_cursor)
                safe_write_cursor += sound_output.BufferSize;

            Assert(safe_write_cursor >= play_cursor);
            safe_write_cursor += sound_output.SafetyBytes;

            bool32 audio_card_is_low_latency = (safe_write_cursor
                < expected_frame_boundary_byte);

            DWORD target_cursor = 0;
            if (audio_card_is_low_latency)
            {
                target_cursor = expected_frame_boundary_byte
                    + expected_sound_bytes_per_frame;
            }
            else
            {
                target_cursor = write_cursor + expected_sound_bytes_per_frame
                    + sound_output.SafetyBytes;
            }

            target_cursor = target_cursor % sound_output.BufferSize;
            DWORD bytes_to_write = 0;
            if (byte_to_lock > target_cursor)
            {
                bytes_to_write = (sound_output.BufferSize - byte_to_lock);
                bytes_to_write += target_cursor;
            }
            else
            {
                bytes_to_write = target_cursor - byte_to_lock;
            }

            GameSoundBuffer sound_buffer = {};
            sound_buffer.SamplesPerSecond = sound_output.SamplesPerSecond;
            sound_buffer.SamplesCount = bytes_to_write / sound_output.BytesPerSample;
            sound_buffer.Samples = samples;

            GetSoundSamples(&game_memory, &sound_buffer);

#if WIN32_DEBUG

            TimeMarker* marker = &time_markers[time_marker_index];
            marker->OutputPlayCursor = play_cursor;
            marker->OutputWriteCursor = write_cursor;
            marker->OutputLocation = byte_to_lock;
            marker->OutputByteCount = bytes_to_write;
            marker->OutputPlayCursor = expected_frame_boundary_byte;

            DWORD unwrapped_cursor = write_cursor;
            if (unwrapped_cursor < play_cursor)
                unwrapped_cursor += sound_output.BufferSize;

            audio_latency_bytes = unwrapped_cursor - play_cursor;
            audio_latency_seconds = ((real32)audio_latency_bytes
                / (real32)sound_output.BytesPerSample)
                / sound_output.SamplesPerSecond;

            char text_buffer[256];
            _snprintf_s(
                text_buffer,
                sizeof(text_buffer),
                "LPC: %u BTL: %u TC: %u BTW: %u - PC: %u WC: %u DELTA: %u (%fs)\n",
                LAST_PLAY_CURSOR, byte_to_lock, target_cursor, bytes_to_write,
                play_cursor, write_cursor, audio_latency_bytes,
                audio_latency_seconds);
            OutputDebugString(text_buffer);

#endif

            FillSoundBuffer(&sound_output, byte_to_lock, bytes_to_write, &sound_buffer);
        }
        else
        {
            is_sound_valid = false;
        }

        LARGE_INTEGER counter_stamp_work_end = GetCounterStamp();
        real32 work_seconds_elapsed = GetSecondsElapsed(
            counter_stamp_frame_start,
            counter_stamp_work_end);

        real32 seconds_elapsed_for_frame = work_seconds_elapsed;
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
                counter_stamp_frame_start, GetCounterStamp());
            Assert(test_seconds_elapsed_for_frame < target_seconds_per_frame);

            while (seconds_elapsed_for_frame < target_seconds_per_frame)
                seconds_elapsed_for_frame = GetSecondsElapsed(
                    counter_stamp_frame_start, GetCounterStamp());
        }
        else
        {
            // TODO: Log error; Missed frame rate;
        }

        LARGE_INTEGER counter_stamp_frame_end = GetCounterStamp();
        real32 ms_per_frame = 1000.0f * GetSecondsElapsed(counter_stamp_frame_start, counter_stamp_frame_end);
        counter_stamp_frame_start = counter_stamp_frame_end;

        WindowDimension dimension = GetWindowDimension(window);

#if WIN32_DEBUG

        DebugSyncDisplay(&BACK_BUFFER, ArrayCount(time_markers),
            time_marker_index - 1, time_markers, &sound_output,
            target_seconds_per_frame);

#endif

        DisplayBufferInWindow(
            &BACK_BUFFER,
            device_context,
            dimension.Width,
            dimension.Height);
        counter_stamp_frame_flip = GetCounterStamp();

#if WIN32_DEBUG

        // DWORD play_cursor;
        // DWORD write_cursor;
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

        uint64 cpu_cycles_frame_end = __rdtsc();
        uint64 cycles_elapsed = cpu_cycles_frame_end - cpu_clock_cycles_frame_start;
        cpu_clock_cycles_frame_start = cpu_cycles_frame_end;

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
