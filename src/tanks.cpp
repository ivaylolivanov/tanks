#include "tanks.h"

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

Internal void UpdateAndRender(GameMemory *memory, GameInput *input,
    GameBackBuffer *display_buffer, GameSoundBuffer *sound_buffer)
{
    Assert(sizeof(GameState) <= memory->PermanentStorageSize);

    GameState* game_state = (GameState *)memory->PermanentStorage;
    if (!memory->IsInitialized)
    {
	game_state->ToneHz = 256;
	memory->IsInitialized = true;
    }

    ControllerState *input_main = &input->Controllers[0];
    if (input_main->IsAnalog)
    {
        game_state->OffsetBlue += (int)(4.0f * input_main->EndX);
        game_state->OffsetGreen -= (int)(4.0f * input_main->EndY);
    }

    if (input_main->ShoulderLeft.EndedDown)
    {
        game_state->OffsetBlue  = 0 ;
        game_state->OffsetGreen = 0 ;
    }

    if (input_main->ActionUp.EndedDown)
        game_state->ToneHz = 256 + (int)(128.0f * (input_main->EndY));

    OutputSound(sound_buffer, game_state->ToneHz);
    RenderGradient(display_buffer, game_state->OffsetBlue, game_state->OffsetGreen);
}
