
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wchar.h>
#include <cinttypes>

static bool IS_RUNNING = false;

// typedef bool32 uint32_t;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCharactersCount)
{
    IS_RUNNING = false;

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = instance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        instance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, cmdCharactersCount);

    // Run the message loop.

    IS_RUNNING = true;

    wchar_t msg[32];
    swprintf_s(msg, L"Going to the while!");
    OutputDebugString(msg);

    while (IS_RUNNING)
    {
        MSG msg = { };
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                IS_RUNNING = false;
                return 0;
            }

            switch (msg.message)
            {
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                uint32_t vkCode = (uint32_t)msg.wParam;
                bool wasDown = ((msg.lParam & (1 << 30)) != 0);
                bool isDown = ((msg.lParam & (1 << 31)) == 0);

                bool altWasDown = (msg.lParam & (1 << 29));
                if (wasDown != isDown) {
                    switch (vkCode) {
                    case 'W': {
                        OutputDebugStringA("You have pressed W/w.\n");
                    } break;

                    case 'A': {
                        OutputDebugStringA("You have pressed A/a.\n");
                    } break;

                    case 'S': {
                        OutputDebugStringA("You have pressed S/s.\n");
                    } break;

                    case 'D': {
                        OutputDebugStringA("You have pressed D/d.\n");
                    } break;

                    case VK_SPACE: {
                        OutputDebugStringA("You have pressed spacebar.\n");
                    } break;

                    case VK_ESCAPE: {
                        OutputDebugStringA("You have pressed ESC key.\n");
                        IS_RUNNING = false;
                    } break;

                    case VK_RETURN: {
                        OutputDebugStringA("You have pressed RETURN key.\n");

                    } break;

                    case VK_F4: {
                        // TODO: Pass too?
                        if (altWasDown) {
                            OutputDebugStringA("You have pressed Alt + F4 key.\n");
                            IS_RUNNING = false;
                        }
                    } break;
                    }
                }
            } break;
            default: {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            } break;
            } break;
        }
    }

    swprintf_s(msg, L"OUT OF THE WHILE\n");
    OutputDebugString(msg);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        IS_RUNNING = false;
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    // case WM_KEYDOWN :
    // {
    //     wchar_t msg[32];
    //     if (wParam)
    //     {
    //         swprintf_s(msg, L"We have pressed 'A'\n");
    //         OutputDebugString(msg);
    //     }

    // } break;
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
