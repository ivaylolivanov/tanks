#include <xinput.h>

// XInputGetState
DWORD WINAPI XInputGetStateStub(DWORD dwUserIndex, XINPUT_STATE *pState)
{
    return ERROR_DEVICE_NOT_CONNECTED;
}

typedef DWORD WINAPI FPtrXInputGetState
(DWORD dwUserIndex, XINPUT_STATE *pState);
GlobalVariable FPtrXInputGetState *X_INPUT_GET_STATE = XInputGetStateStub;
// Replaces the XInput library's function of 'XInputGetState'
#define XInputGetState X_INPUT_GET_STATE

// XInputSetState
DWORD WINAPI XInputSetStateStub(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
{
    return ERROR_DEVICE_NOT_CONNECTED;
}

typedef DWORD WINAPI FPtrXInputSetState
(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration);
GlobalVariable FPtrXInputSetState *X_INPUT_SET_STATE = XInputSetStateStub;
// Replaces the XInput library's function of 'XInputSetState'
#define XInputSetState X_INPUT_SET_STATE

Internal void LoadXInput()
{
    HMODULE XInputLibrary = LoadLibraryA("xinput1_4.dll");
    if (!XInputLibrary)
        XInputLibrary = LoadLibraryA("xinput1_3.dll");

    if (!XInputLibrary)
        return;

    XInputGetState = (FPtrXInputGetState *)GetProcAddress(XInputLibrary, "XInputGetState");
    if (!XInputGetState) { XInputGetState = XInputGetStateStub; }

    XInputSetState = (FPtrXInputSetState *)GetProcAddress(XInputLibrary, "XInputSetState");
    if (!XInputSetState) { XInputSetState = XInputSetStateStub; }
}
