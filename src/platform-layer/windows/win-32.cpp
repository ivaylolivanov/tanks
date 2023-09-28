#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "win-32.h"
#include "xinput.h"
#include "dsound.h"

#include "..\..\tanks.h"
#include "..\..\tanks.cpp"

GlobalVariable bool32 IS_RUNNING = false;

struct BackBuffer
{
    // Pixel is 32-bit
    // Memory order BB GG RR XX
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
};

GlobalVariable BackBuffer BACK_BUFFER;

struct SoundOutput
{
    int32  SamplesPerSecond;
    int32  ToneHz;
    int16  ToneVolume;
    uint32 RunningSampleIndex;
    int32  WavePeriod;
    int32  BytesPerSample;
    int32  BufferSize;
    real32 SineCurrent;
    int32  LatencySampleCount;
};

struct WindowDimension
{
    int Width;
    int Height;
};

void* LoadFile(char *filename)
{
    return 0;
}

Internal void ResizeBuffer(BackBuffer *buffer, int width, int height)
{
    if (buffer->Memory) VirtualFree(buffer->Memory, 0, MEM_RELEASE);

    buffer->Width = width;
    buffer->Height = height;

    int bytes_per_pixel = 4;

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
                              DWORD bytes_to_write,
                              GameSoundBuffer *game_sound_buffer)
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

Internal bool32 ValidateSoundBuffer(SoundOutput *sound_output, DWORD &byte_to_lock, DWORD &bytes_to_write)
{
    bool32 result = false;

    DWORD play_cursor;
    DWORD write_cursor;
    if (FAILED(SOUND_BUFFER->GetCurrentPosition(&play_cursor, &write_cursor)))
        return result;

    DWORD past_bytes = sound_output->RunningSampleIndex
        * sound_output->BytesPerSample;
    byte_to_lock = past_bytes % sound_output->BufferSize;

    DWORD target_bytes = sound_output->LatencySampleCount
        * sound_output->BytesPerSample;
    DWORD target_cursor = (( play_cursor + target_bytes)
        % sound_output->BufferSize);

    bytes_to_write = target_cursor - byte_to_lock;
    if (byte_to_lock > target_cursor)
    {
        bytes_to_write = (sound_output->BufferSize - byte_to_lock);
        bytes_to_write += target_cursor;
    }

    result = true;
    return result;
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

Internal void ProcessPendingKeyPresses(int& x, int& y, SoundOutput *sound_output)
{
    MSG message;
    while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
    {
        switch (message.message)
        {
            case WM_QUIT:
            {
                IS_RUNNING = false;
            } break;

            case WM_SYSKEYUP:
            case WM_SYSKEYDOWN:
            case WM_KEYUP:
            case WM_KEYDOWN:
            {
                uint32_t vk_code = (uint32_t)message.wParam;

                bool32 alt_was_down = (message.lParam & (1 << 29));
                bool32 was_down     = ((message.lParam & (1 << 30)) != 0);
                bool32 is_down      = ((message.lParam & (1 << 31)) == 0);

                if (was_down == is_down) continue;

                switch (vk_code)
                {
                    case 'W':
                    {
                        --y;
                        OutputDebugStringA("You have pressed W/w.\n");
                    } break;

                    case 'A':
                    {
                        --x;
                        OutputDebugStringA("You have pressed A/a.\n");
                    } break;

                    case 'S':
                    {
                        ++y;
                        OutputDebugStringA("You have pressed S/s.\n");
                    } break;

                    case 'D':
                    {
                        ++x;
                        OutputDebugStringA("You have pressed D/d.\n");
                    } break;

                    case VK_SPACE:
                    {
                        OutputDebugStringA("You have pressed spacebar.\n");
                    } break;

                    case VK_ESCAPE:
                    {
                        OutputDebugStringA("You have pressed ESC key.\n");
                        IS_RUNNING = false;
                    } break;

                    case VK_RETURN:
                    {
                        OutputDebugStringA("You have pressed RETURN key.\n");
                    } break;

                    case VK_F4:
                    {
                        // TODO: Pass too?
                        if (alt_was_down)
                        {
                            IS_RUNNING = false;
                            OutputDebugStringA("You have pressed Alt + F4 key.\n");
                        }
                    } break;
                }
            }
            default:
            {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            } break;
        }

        sound_output->ToneHz = 512 + (int)(256.0f * ((real32)y / 30000.0f));
        sound_output->WavePeriod = sound_output->SamplesPerSecond / sound_output->ToneHz;
    }
}

Internal void ProcessControllersStates()
{
    for (DWORD controllerIndex = 0; controllerIndex < XUSER_MAX_COUNT; ++controllerIndex)
    {
        XINPUT_STATE controllerState;
        bool32 isUnplugged = XInputGetState(controllerIndex, &controllerState)
            != ERROR_SUCCESS;
        if (isUnplugged) continue;

        XINPUT_GAMEPAD *gamepad = &controllerState.Gamepad;

        bool32 up      = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
        bool32 down    = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
        bool32 left    = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
        bool32 right   = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
        bool32 start   = (gamepad->wButtons & XINPUT_GAMEPAD_START);
        bool32 back    = (gamepad->wButtons & XINPUT_GAMEPAD_BACK);
        bool32 l1      = (gamepad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
        bool32 r1      = (gamepad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
        bool32 buttonA = (gamepad->wButtons & XINPUT_GAMEPAD_A);
        bool32 buttonB = (gamepad->wButtons & XINPUT_GAMEPAD_B);
        bool32 buttonX = (gamepad->wButtons & XINPUT_GAMEPAD_X);
        bool32 buttonY = (gamepad->wButtons & XINPUT_GAMEPAD_Y);

        int16 lStickX = gamepad->sThumbLX;
        int16 lStickY = gamepad->sThumbLY;

        if (up)    OutputDebugStringA("Gamepad up");
        if (down)  OutputDebugStringA("Gamepad down");
        if (left)  OutputDebugStringA("Gamepad left");
        if (right) OutputDebugStringA("Gamepad right");
    }
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

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int command_line_characters_count)
{
    LARGE_INTEGER performance_counter_frequency;
    QueryPerformanceFrequency(&performance_counter_frequency);
    int64 frequency = performance_counter_frequency.QuadPart;

    IS_RUNNING = false;
    LoadXInput();

    // Register the window class.
    const char CLASS_NAME[]   = "Tanks";
    const char WINDOW_TITLE[] = "Tanks";

    WNDCLASS window_class = { };

    ResizeBuffer(&BACK_BUFFER, 1280, 720);

    window_class.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc   = WindowProc;
    window_class.hInstance     = instance;
    window_class.lpszClassName = CLASS_NAME;

    RegisterClass(&window_class);

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

    int offset_x = 0;
    int offset_y = 0;

    SoundOutput sound_output = {};
    sound_output.SamplesPerSecond = 48000;
    sound_output.ToneHz = 256;
    sound_output.ToneVolume = 3000;
    sound_output.WavePeriod = sound_output.SamplesPerSecond
        * sound_output.ToneHz;
    sound_output.BytesPerSample = sizeof(int16) * 2;
    sound_output.BufferSize = sound_output.SamplesPerSecond
        * sound_output.BytesPerSample;
    sound_output.LatencySampleCount = sound_output.SamplesPerSecond / 15;
    InitDirectSound(window, sound_output.SamplesPerSecond,
        sound_output.BufferSize);
    ClearSoundBuffer(&sound_output);
    SOUND_BUFFER->Play(0, 0, DSBPLAY_LOOPING);

    IS_RUNNING = true;

    int16 *samples = (int16 *)VirtualAlloc(
        0, sound_output.BufferSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    LARGE_INTEGER counter_previous;
    QueryPerformanceCounter(&counter_previous);
    uint64 cycles_previous = __rdtsc();

    while (IS_RUNNING)
    {
        ProcessPendingKeyPresses(offset_x, offset_y, &sound_output);
        ProcessControllersStates();

        DWORD byte_to_lock;
        DWORD bytes_to_write;
        bool32 is_sound_valid = ValidateSoundBuffer(&sound_output, byte_to_lock, bytes_to_write);

        GameSoundBuffer sound_buffer = {};
        sound_buffer.SamplesPerSecond = sound_output.SamplesPerSecond;
        sound_buffer.SamplesCount = bytes_to_write / sound_output.BytesPerSample;
        sound_buffer.Samples = samples;

        GameBackBuffer game_buffer = {};
        game_buffer.Memory = BACK_BUFFER.Memory;
        game_buffer.Height = BACK_BUFFER.Height;
        game_buffer.Width  = BACK_BUFFER.Width;
        game_buffer.Pitch = BACK_BUFFER.Pitch;
        UpdateAndRender(&game_buffer, offset_x, offset_y, &sound_buffer,
                        sound_output.ToneHz);

        if (is_sound_valid)
            FillSoundBuffer(&sound_output, byte_to_lock, bytes_to_write, &sound_buffer);

        WindowDimension dimension = GetWindowDimension(window);
        DisplayBufferInWindow(
            &BACK_BUFFER,
            device_context,
            dimension.Width,
            dimension.Height);

        uint64 cycles_current = __rdtsc();

        LARGE_INTEGER counter_current;
        QueryPerformanceCounter(&counter_current);

        uint64 cycles_elapsed = cycles_current - cycles_previous;
        int64 counter_elapsed = counter_current.QuadPart - counter_previous.QuadPart;

        real64 ms_per_frame = ((1000.0f * (real64)counter_elapsed) / (real64)frequency);
        real64 fps = (real64)frequency / (real64)counter_elapsed;
        real64 mc_per_frame = (real64)cycles_elapsed / (1000.0f * 1000.0f);

        char dbg_msg_buffer[256];
        sprintf(dbg_msg_buffer, "%.02fms/f,  %.02ff/s,  %.02fmc/f\n", ms_per_frame, fps, mc_per_frame);
        OutputDebugStringA(dbg_msg_buffer);

        counter_previous = counter_current;
        cycles_previous  = cycles_current;
    }

    return 0;
}
