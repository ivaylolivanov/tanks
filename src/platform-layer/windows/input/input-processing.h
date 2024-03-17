#ifndef INPUT_PROCESSING

Internal void GetInputRecordsFilepath(WindowsState* state, int slot,
    char* destination, int count)
{
    Assert(slot == 1);
    char* input_record_basename = "input-record.ti";
    CatStrings(state->ExeFilepath, state->ExeBasename - state->ExeFilepath,
        input_record_basename, StringLength(input_record_basename),
        destination, sizeof(destination));
}

Internal void InputRecord(WindowsState* state, int index)
{
    state->InputRecordingIndex = index;

    char input_records_filepath[MAX_PATH];
    GetInputRecordsFilepath(state, index, input_records_filepath,
        sizeof(input_records_filepath));

    state->RecordingHandle = CreateFileA(input_records_filepath, GENERIC_WRITE,
        0, 0, CREATE_ALWAYS, 0, 0);
    DWORD bytes_to_write = (DWORD)state->TotalSize;
    Assert(bytes_to_write == state->TotalSize);
    DWORD bytes_written;
    WriteFile(state->RecordingHandle, state->GameMemory, bytes_to_write,
        &bytes_written, 0);
}

Internal void InputRecordEnd(WindowsState* state)
{
    CloseHandle(state->RecordingHandle);
    state->InputRecordingIndex = 0;
}

Internal void InputPlayback(WindowsState* state, int index)
{
    state->InputPlaybackIndex = index;

    char input_records_filepath[MAX_PATH];
    GetInputRecordsFilepath(state, index, input_records_filepath,
        sizeof(input_records_filepath));

    state->PlaybackHandle = CreateFileA(input_records_filepath, GENERIC_READ,
        FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    DWORD bytes_to_read = (DWORD)(state->TotalSize);
    Assert(bytes_to_read == state->TotalSize);
    DWORD bytes_read;
    ReadFile(state->PlaybackHandle, state->GameMemory, bytes_to_read,
        &bytes_read, 0);
}

Internal void InputPlaybackEnd(WindowsState* state)
{
    CloseHandle(state->PlaybackHandle);
    state->InputPlaybackIndex = 0;
}

Internal void InputRecordWrite(WindowsState* state, GameInput* input)
{
    DWORD bytes_written;
    WriteFile(state->RecordingHandle, input, sizeof(*input), &bytes_written, 0);
}

Internal void InputRecordRead(WindowsState* state, GameInput* input)
{
    DWORD bytes_read;
    if (!ReadFile(state->PlaybackHandle, input, sizeof(*input), &bytes_read, 0))
        return;

    if (bytes_read != 0)
        return;

    int index = state->InputPlaybackIndex;
    InputPlaybackEnd(state);
    InputPlayback(state, index);
    ReadFile(state->PlaybackHandle, input, sizeof(*input), &bytes_read, 0);
}

Internal void ProcessKeyboardButton(ButtonState* state, bool32 is_down)
{
    Assert(state->EndedDown != is_down);

    state->EndedDown = is_down;
    ++state->HalfTransitions;
}

Internal void ProcessKeyboard(WindowsState* state, ControllerState *keyboard)
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
                uint32 vk_code = (uint32)message.wParam;

                bool32 alt_was_down = (message.lParam & (1 << 29));
                bool32 was_down     = ((message.lParam & (1 << 30)) != 0);
                bool32 is_down      = ((message.lParam & (1 << 31)) == 0);

                if (was_down == is_down) continue;

                switch (vk_code)
                {
                    case 'W':
                    {
                        ProcessKeyboardButton(&keyboard->MoveUp, is_down);
                        OutputDebugStringA("You have pressed W/w.\n");
                    } break;

                    case 'A':
                    {
                        ProcessKeyboardButton(&keyboard->MoveLeft, is_down);
                        OutputDebugStringA("You have pressed A/a.\n");
                    } break;

                    case 'S':
                    {
                        ProcessKeyboardButton(&keyboard->MoveDown, is_down);
                        OutputDebugStringA("You have pressed S/s.\n");
                    } break;

                    case 'D':
                    {
                        ProcessKeyboardButton(&keyboard->MoveRight, is_down);
                        OutputDebugStringA("You have pressed D/d.\n");
                    } break;

#if WIN32_DEBUG
                    case 'P':
                    {
                        if (is_down) IS_PAUSED = !IS_PAUSED;
                        OutputDebugStringA("You have pressed P/p.\n");
                    } break;
#endif

                    case 'L':
                    {
                        if (is_down)
                        {
                            if (state->InputRecordingIndex == 0)
                            {
                                InputRecord(state, 1);
                            }
                            else
                            {
                                InputRecordEnd(state);
                                InputPlayback(state, 1);
                            }
                        }
                    } break;

                    case VK_SPACE:
                    {
                        OutputDebugStringA("You have pressed spacebar.\n");
                    } break;

                    case VK_ESCAPE:
                    {
                        ProcessKeyboardButton(&keyboard->Start, is_down);
                        OutputDebugStringA("You have pressed ESC key.\n");
                    } break;

                    case VK_BACK:
                    {
                        ProcessKeyboardButton(&keyboard->Back, is_down);
                        OutputDebugStringA("You have pressed backspace.\n");
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

Internal void ProcessGamepadButton(DWORD button_bit, DWORD raw_state,
    ButtonState *old_state, ButtonState *new_state)
{
    new_state->EndedDown = ((raw_state & button_bit) == button_bit);
    new_state->HalfTransitions = (old_state->EndedDown != new_state->EndedDown) ? 1 : 0;
}

Internal real32 ProcessGamepadStick(SHORT value, SHORT deadzone_threshold)
{
    real32 result = 0;

    if (value < -deadzone_threshold)
    {
        result = (real32)((value + deadzone_threshold)
            / (32768.0f - deadzone_threshold));
    }
    else if (value > deadzone_threshold)
    {
        result = (real32)((value - deadzone_threshold)
            / (32768.0f - deadzone_threshold));
    }

    return result;
}

Internal void ProcessGamepadStates(GameInput *input_old, GameInput *input_new)
{
    DWORD max_controllers = XUSER_MAX_COUNT;
    if (max_controllers > (ArrayCount(input_new->Controllers) - 1))
        max_controllers = ArrayCount(input_new->Controllers) - 1;

    for (DWORD controller_index = 0; controller_index < max_controllers;
         ++controller_index)
    {
        DWORD gamepad_index = controller_index + 1;
        ControllerState *state_old = GetController(input_old, gamepad_index);
        ControllerState *state_new = GetController(input_new, gamepad_index);

        XINPUT_STATE controllerState;
        bool32 isUnplugged = XInputGetState(controller_index, &controllerState)
            != ERROR_SUCCESS;
        state_new->IsConnected = !isUnplugged;
        if (isUnplugged) continue;

        XINPUT_GAMEPAD *gamepad = &controllerState.Gamepad;

        bool32 up      = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
        bool32 down    = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
        bool32 left    = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
        bool32 right   = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
        bool32 start   = (gamepad->wButtons & XINPUT_GAMEPAD_START);
        bool32 back    = (gamepad->wButtons & XINPUT_GAMEPAD_BACK);

        int16 lStickX = gamepad->sThumbLX;
        int16 lStickY = gamepad->sThumbLY;

        state_new->LeftStickAverageX = ProcessGamepadStick(gamepad->sThumbLX,
            XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        state_new->LeftStickAverageY = ProcessGamepadStick(gamepad->sThumbLY,
            XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        if ((state_new->LeftStickAverageX != 0)
            || (state_new->LeftStickAverageY != 0))
            state_new->IsAnalog = true;

        if (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_UP)
        {
            state_new->LeftStickAverageY = 1.0f;
            state_new->IsAnalog = false;
        }

        if (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
        {
            state_new->LeftStickAverageY = -1.0f;
            state_new->IsAnalog = false;
        }

        if (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
        {
            state_new->LeftStickAverageX = -1.0f;
            state_new->IsAnalog = false;
        }

        if (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
        {
            state_new->LeftStickAverageY = 1.0f;
            state_new->IsAnalog = false;
        }

        real32 threshold = 0.5f;
        ProcessGamepadButton(1, (state_new->LeftStickAverageX > -threshold) ? 1 : 0,
            &state_old->MoveLeft,
            &state_new->MoveLeft);
        ProcessGamepadButton(1, (state_new->LeftStickAverageX > threshold) ? 1 : 0,
            &state_old->MoveRight,
            &state_new->MoveRight);
        ProcessGamepadButton(1, (state_new->LeftStickAverageY > -threshold) ? 1 : 0,
            &state_old->MoveDown,
            &state_new->MoveDown);
        ProcessGamepadButton(1, (state_new->LeftStickAverageY > threshold) ? 1 : 0,
            &state_old->MoveUp,
            &state_new->MoveUp);

        ProcessGamepadButton(XINPUT_GAMEPAD_A,
            gamepad->wButtons, &state_old->ActionUp, &state_new->ActionUp);
        ProcessGamepadButton(XINPUT_GAMEPAD_B,
            gamepad->wButtons, &state_old->ActionDown, &state_new->ActionDown);
        ProcessGamepadButton(XINPUT_GAMEPAD_X,
            gamepad->wButtons, &state_old->ActionLeft, &state_new->ActionLeft);
        ProcessGamepadButton(XINPUT_GAMEPAD_Y,
            gamepad->wButtons, &state_old->ActionRight, &state_new->ActionRight);
        ProcessGamepadButton(XINPUT_GAMEPAD_LEFT_SHOULDER,
            gamepad->wButtons, &state_old->ShoulderLeft, &state_new->ShoulderLeft);
        ProcessGamepadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER,
            gamepad->wButtons, &state_old->Buttons[5], &state_new->Buttons[5]);
        ProcessGamepadButton(XINPUT_GAMEPAD_START, gamepad->wButtons,
            &state_old->Start, &state_new->Start);
        ProcessGamepadButton(XINPUT_GAMEPAD_BACK, gamepad->wButtons,
            &state_old->Back, &state_new->Back);

#if WIN32_DEBUG

        if (state_new->Start.EndedDown) IS_PAUSED = !IS_PAUSED;

#endif
    }
}

#define INPUT_PROCESSING
#endif
