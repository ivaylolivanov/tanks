#include <windows.h>

#include "win-32.h"
#include "xinput.h"

GlobalVariable bool IS_RUNNING = false;

{


{
}


{


}

Internal void ProcessPendingKeyPresses()
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
                bool was_down = ((message.lParam & (1 << 30)) != 0);
                bool is_down = ((message.lParam & (1 << 31)) == 0);

                bool alt_was_down = (message.lParam & (1 << 29));
                if (was_down == is_down) continue;

                switch (vk_code)
                {
                    case 'W':
                    {
                        OutputDebugStringA("You have pressed W/w.\n");
                    } break;

                    case 'A':
                    {
                        OutputDebugStringA("You have pressed A/a.\n");
                    } break;

                    case 'S':
                    {
                        OutputDebugStringA("You have pressed S/s.\n");
                    } break;

                    case 'D':
                    {
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

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            IS_RUNNING = false;
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT paint_struct;
            HDC device_context = BeginPaint(window, &paint_struct);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(device_context, &paint_struct.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint( window, &paint_struct);
        }
        return 0;

    }
    return DefWindowProc(window, message, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int command_line_characters_count)
{
    IS_RUNNING = false;
    LoadXInput();

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS window_class = { };

    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = instance;
    window_class.lpszClassName = CLASS_NAME;

    RegisterClass(&window_class);

    // Create the window.
    HWND window = CreateWindowEx(
        0,                   // Optional window styles.
        CLASS_NAME,          // Window class
        L"TanksWindows",     // Window text
        WS_OVERLAPPEDWINDOW, // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,      // Parent window
        NULL,      // Menu
        instance,  // Instance handle
        NULL       // Additional application data
    );

    if (window == NULL) return 0;

    ShowWindow(window, command_line_characters_count);


    IS_RUNNING = true;

    while (IS_RUNNING)
    {
        ProcessPendingKeyPresses();
        for (DWORD controllerIndex = 0; controllerIndex < XUSER_MAX_COUNT; ++controllerIndex)
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
    }

    return 0;
}
