#include <windows.h>

#include "win-32.h"
#include "xinput.h"

GlobalVariable bool IS_RUNNING = false;

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

struct WindowDimension
{
    int Width;
    int Height;
};

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

Internal void Render(BackBuffer *buffer, int offset_blue, int offset_green)
{
    uint8* row = (uint8 *) buffer->Memory;
    for (int y = 0; y < buffer->Height; ++y)
    {
        uint32 *pixel = (uint32 *)row;
        for (int x = 0; x < buffer->Width; ++x)
        {
            uint8 blue  = x + offset_blue;
            uint8 green = y + offset_green;

            *pixel++ = (green << 8) | blue;
        }

        row += buffer->Pitch;
    }
}

{


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

Internal void ProcessPendingKeyPresses(int& x, int& y)
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

                bool alt_was_down = (message.lParam & (1 << 29));
                bool was_down     = ((message.lParam & (1 << 30)) != 0);
                bool is_down      = ((message.lParam & (1 << 31)) == 0);

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
            result = DefWindowProc(window, message, w_param, l_param);
        } break;
    }

    return result;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int command_line_characters_count)
{
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

    while (IS_RUNNING)
    {
        for (DWORD controllerIndex = 0; controllerIndex < XUSER_MAX_COUNT; ++controllerIndex)
        ProcessPendingKeyPresses(offset_x, offset_y);
        Render(&BACK_BUFFER, offset_x, offset_y);
        {
            XINPUT_STATE controllerState;
            bool isUnplugged = XInputGetState(controllerIndex, &controllerState)
                != ERROR_SUCCESS;
            if (isUnplugged) continue;

            XINPUT_GAMEPAD *gamepad = &controllerState.Gamepad;

            bool up      = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
            bool down    = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
            bool left    = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
            bool right   = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
            bool start   = (gamepad->wButtons & XINPUT_GAMEPAD_START);
            bool back    = (gamepad->wButtons & XINPUT_GAMEPAD_BACK);
            bool l1      = (gamepad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
            bool r1      = (gamepad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
            bool buttonA = (gamepad->wButtons & XINPUT_GAMEPAD_A);
            bool buttonB = (gamepad->wButtons & XINPUT_GAMEPAD_B);
            bool buttonX = (gamepad->wButtons & XINPUT_GAMEPAD_X);
            bool buttonY = (gamepad->wButtons & XINPUT_GAMEPAD_Y);

            int16 lStickX = gamepad->sThumbLX;
            int16 lStickY = gamepad->sThumbLY;

            if (up)    OutputDebugStringA("Gamepad up");
            if (down)  OutputDebugStringA("Gamepad down");
            if (left)  OutputDebugStringA("Gamepad left");
            if (right) OutputDebugStringA("Gamepad right");
        }
        WindowDimension dimension = GetWindowDimension(window);
        DisplayBufferInWindow(
            &BACK_BUFFER,
            device_context,
            dimension.Width,
            dimension.Height);
    }

    return 0;
}
