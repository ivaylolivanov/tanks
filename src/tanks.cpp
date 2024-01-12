#include "tanks.h"

Internal ControllerState* GetController(GameInput* input, int unsigned controller_index)
{
    Assert(controller_index < ArrayCount(input->Controllers));

    ControllerState* result = &input->Controllers[controller_index];

    return result;
}

Internal void OutputSound(GameSoundBuffer *sound_buffer, int tone_hz)
{
    LocalPersist real32 sine_step;
    int16 tone_volume = 3000;
    int wave_period = sound_buffer->SamplesPerSecond / tone_hz;

    int16 *sample_out = sound_buffer->Samples;
    for (int sample_index = 0; sample_index < sound_buffer->SamplesCount; ++sample_index)
    {
        real32 sine_value = sinf(sine_step);
        int16 sample_value = (int16)(sine_value * tone_volume);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;

        sine_step += 2.0f * Pi32 * 1.0f / (real32)wave_period;
        if (sine_step > (2.0f * Pi32))
            sine_step -= 2.0f * Pi32;
    }
}

Internal void RenderGradient(GameBackBuffer *buffer, int offset_blue, int offset_green)
{
    uint8* row = (uint8 *) buffer->Memory;
    for (int y = 0; y < buffer->Height; ++y)
    {
        uint32 *pixel = (uint32 *)row;
        for (int x = 0; x < buffer->Width; ++x)
        {
            uint8 blue  = (uint8)(x + offset_blue);
            uint8 green = (uint8)(y + offset_green);

            *pixel++ = (green << 8) | blue;
        }

        row += buffer->Pitch;
    }
}

Internal void UpdateAndRender(GameMemory *memory, GameInput *input, GameBackBuffer *display_buffer)
{
    Assert((&input->Controller[0].MAX - &input->Controller[0].Buttons[0])
        == ArrayCount(input->Controller[0].Buttons));
    Assert(sizeof(GameState) <= memory->PermanentStorageSize);

    GameState* game_state = (GameState *)memory->PermanentStorage;
    if (!memory->IsInitialized)
    {
        char* filepath = __FILE__;

        FileData file = ReadFile(filepath);
        if (file.Content)
        {
            WriteFile("testing.out", file.Content, file.Size);
            FreeFileMemory(file.Content);
        }

	game_state->ToneHz = 512;
	memory->IsInitialized = true;
    }

    for (int8 controller_index = 0; controller_index < ArrayCount(input->Controllers); ++controller_index)
    {
        ControllerState *controller = GetController(input, controller_index);
        if (controller->IsAnalog)
        {
            game_state->OffsetBlue  += (int)(4.0f * controller->LeftStickAverageX);
            game_state->OffsetGreen -= (int)(4.0f * controller->LeftStickAverageY);

            game_state->ToneHz = 512 + (int)(128.0f * controller->LeftStickAverageY);
        }
        else
        {
            if (controller->MoveLeft.EndedDown)  game_state->OffsetBlue  -= 4;
            if (controller->MoveRight.EndedDown) game_state->OffsetBlue  += 4;
            if (controller->MoveUp.EndedDown)    game_state->OffsetGreen -= 4;
            if (controller->MoveDown.EndedDown)  game_state->OffsetGreen += 4;

            if (controller->ShoulderLeft.EndedDown)
            {
                game_state->OffsetBlue  = 0 ;
                game_state->OffsetGreen = 0 ;
            }
        }
    }

    RenderGradient(display_buffer, game_state->OffsetBlue, game_state->OffsetGreen);
}

Internal void GetSoundSamples(GameMemory* memory, GameSoundBuffer *sound_buffer)
{
    GameState* game_state = (GameState*)memory->PermanentStorage;
    OutputSound(sound_buffer, game_state->ToneHz);
}
