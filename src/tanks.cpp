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

Internal void RenderRectangle(GameBackBuffer *buffer, int min_x, int min_y, int width, int height, uint8 r, uint8 g, uint8 b)
{
    if (min_x < 0)             min_x = 0;
    if (min_x > buffer->Width) min_x = buffer->Width;

    if (min_y < 0)              min_y = 0;
    if (min_y > buffer->Height) min_y = buffer->Height;

    uint8* rectangle_begin = (uint8 *) buffer->Memory
        + player_x * buffer->BytesPerPixel
        + player_y * buffer->Pitch;
    for (int y = min_y; y < (min_y + height); ++y)
    {
        uint32 *pixel = (uint32 *)pixel_player_begin;
        for (int x = min_x; x < (min_x + width); ++x)
        {
            uint8 blue  = (uint8)b;
            uint8 green = (uint8)g;
            uint8 red   = (uint8)r;

            *pixel++ = (red << 16) | (green << 8) | blue;
        }

        rectangle_begin += buffer->Pitch;
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

        game_state->PlayerX = 250;
        game_state->PlayerY = 250;

	game_state->ToneHz = 512;
	memory->IsInitialized = true;
    }

    for (int8 controller_index = 0; controller_index < ArrayCount(input->Controllers); ++controller_index)
    {
        ControllerState *controller = GetController(input, controller_index);
        if (controller->IsAnalog)
        {
            game_state->PlayerX += (int)(4.0f * controller->LeftStickAverageX);
            game_state->PlayerY -= (int)(4.0f * controller->LeftStickAverageY);

            game_state->ToneHz = 512 + (int)(128.0f * controller->LeftStickAverageY);
        }
        else
        {
            int32 x = 0;
            int32 y = 0;
            if (controller->MoveLeft.EndedDown)  x -= 5;
            if (controller->MoveRight.EndedDown) x += 5;
            if (controller->MoveUp.EndedDown)    y -= 5;
            if (controller->MoveDown.EndedDown)  y += 5;

            game_state->PlayerX += x;
            game_state->PlayerY += y;
        }
    }

    RenderRectangle(display_buffer, 0, 0, display_buffer->Width, display_buffer->Height, 0, 0, 0);
    RenderRectangle(display_buffer, game_state->PlayerX, game_state->PlayerY, 30, 30, 214, 13, 200);
}

Internal void GetSoundSamples(GameMemory* memory, GameSoundBuffer *sound_buffer)
{
    GameState* game_state = (GameState*)memory->PermanentStorage;

    bool32 is_sound_unmuted = false;
    if (is_sound_unmuted)
        OutputSound(sound_buffer, game_state->ToneHz);
}
