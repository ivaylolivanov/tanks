#include "tanks.h"

#define TILEMAP_WIDTH 32
#define TILEMAP_HEIGHT 18

uint32 TILES[4][TILEMAP_HEIGHT * TILEMAP_WIDTH] =
{

{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
},

{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
},

{
    1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
},

{
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
}

};

Internal uint8 BlendColorChannel(uint8 background, uint8 foreground,
    real32 alpha)
{
    uint8 result = 0;
    result = (uint8)(foreground * alpha + background * (1 - alpha));

    return result;
}

Internal uint32 BlendColors(uint32 pixel_background, uint32 pixel_foreground)
{
    uint32 result = pixel_foreground;

    uint8 foreground_alpha = pixel_foreground >> 24;
    if (foreground_alpha == 255)
        return result;

    uint8 background_red   = (pixel_background >> 16) & 0xFF;
    uint8 background_green = (pixel_background >> 8)  & 0xFF;
    uint8 background_blue  =  pixel_background        & 0xFF;

    uint8  foreground_red        = (pixel_foreground >> 16) & 0xFF;
    uint8  foreground_green      = (pixel_foreground >> 8)  & 0xFF;
    uint8  foreground_blue       =  pixel_foreground        & 0xFF;
    real32 foreground_alpha_real = foreground_alpha / 255.0f;

    uint8 result_red = BlendColorChannel(background_red, foreground_red,
        foreground_alpha_real);
    uint8 result_green = BlendColorChannel(background_green, foreground_green,
        foreground_alpha_real);
    uint8 result_blue = BlendColorChannel(background_blue, foreground_blue,
        foreground_alpha_real);

    result = (foreground_alpha << 24)
        | (result_red << 16)
        | (result_green << 8)
        | result_blue;
    return result;
}

Internal void DrawPngImage(GameBackBuffer* buffer, Image* image, V2r center,
    V2r size)
{
    V2r half_size = 0.5f * size;
    V2i corner_up_left    = RoundReal32ToInt32(center - half_size);
    V2i corner_down_right = RoundReal32ToInt32(center + half_size);
    V2r scale =
    {
        size.Width / image->Width,
        size.Height / image->Height,
    };

    ClampInt32(corner_up_left.X,    0, buffer->Width);
    ClampInt32(corner_down_right.X, 0, buffer->Width);
    ClampInt32(corner_up_left.Y,    0, buffer->Height);
    ClampInt32(corner_down_right.Y, 0, buffer->Height);

    uint8* row = (uint8*)buffer->Memory
        + corner_up_left.X * buffer->BytesPerPixel
        + corner_up_left.Y * buffer->Pitch;
    for (int y = corner_up_left.Y; y < corner_down_right.Y; ++y)
    {
        uint32 y_scaled = (uint32)((y - corner_up_left.Y) / scale.Y);
        uint32* pixel_buffer = (uint32*)row;
        for (int x = corner_up_left.X; x < corner_down_right.X; ++x)
        {
            uint32 x_scaled = (uint32)((x - corner_up_left.X) / scale.X);
            uint32* pixel_image = (uint32*)(image->Pixels)
                + (y_scaled * image->Width + x_scaled);

            uint32 blend_color = BlendColors(*pixel_buffer, *pixel_image);
            *pixel_buffer++ = blend_color;
        }

        row += buffer->Pitch;
    }
}

Internal void OutputSound(GameState* game_state, GameSoundBuffer *sound_buffer)
{
    int16 tone_volume = 3000;
    int wave_period = sound_buffer->SamplesPerSecond / game_state->ToneHz;

    int16 *sample_out = sound_buffer->Samples;
    for (int sample_index = 0; sample_index < sound_buffer->SamplesCount; ++sample_index)
    {
        real32 sine_value = sinf(game_state->SineStep);
        int16 sample_value = (int16)(sine_value * tone_volume);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;

        game_state->SineStep += 2.0f * Pi32 * 1.0f / (real32)wave_period;
        if (game_state->SineStep > (2.0f * Pi32))
            game_state->SineStep -= 2.0f * Pi32;
    }
}

inline void NormalizePositionsAxis(int32* tile, real32* offset, real32 tile_side)
{
    // TODO: Verify if adjusting for overflow is needed, what happens if player
    // goes to the last tile and continues.
    int32 tile_displacement = RoundReal32ToInt32(*offset / tile_side);

    *tile += tile_displacement;
    *offset -= tile_displacement * tile_side;
}

inline void NormalizePosition(Position* position, real32 tile_side)
{
    NormalizePositionsAxis(&position->Tile.X, &position->Offset.X, tile_side);
    NormalizePositionsAxis(&position->Tile.Y, &position->Offset.Y, tile_side);
}

inline V2r DiffPositions(Position a, Position b, real32 tile_side)
{
    V2r result = {};

    V2r absolute_a = a.Tile * tile_side + a.Offset;
    V2r absolute_b = b.Tile * tile_side + b.Offset;
    result = absolute_a - absolute_b;

    return result;
}

// TODO: Use V2u instead V2i
Internal uint32 GetTileValue(Tilemap* tilemap, V2i tile)
{
    Assert(tilemap);
    Assert((tile_x >= 0) && (tile_x < world->Size.Width));
    Assert((tile_y >= 0) && (tile_y < world->Size.Height));

    uint32 value = tilemap->Tiles[tilemap->Size.Width * tile.Y + tile.X];
    return value;
}

inline bool32 IsTileEmpty(Tilemap* tilemap, Position position)
{
    bool32 result = false;

    if ((position.Tile.X >= 0) && (position.Tile.X < tilemap->Size.Width)
        && (position.Tile.Y >= 0) && (position.Tile.Y < tilemap->Size.Height))
    {
        uint32 tile_value = GetTileValue(tilemap, position.Tile);
        result = (tile_value == 0);
    }

    return result;
}

Internal void DrawRectangle(GameBackBuffer *buffer, V2r center, V2r size,
    V3r color)
{
    V2r half_size = 0.5f * size;
    V2i corner_up_left    = RoundReal32ToInt32(center - half_size);
    V2i corner_down_right = RoundReal32ToInt32(center + half_size);

    ClampInt32(corner_up_left.X,    0, buffer->Width);
    ClampInt32(corner_down_right.X, 0, buffer->Width);
    ClampInt32(corner_up_left.Y,    0, buffer->Height);
    ClampInt32(corner_down_right.Y, 0, buffer->Height);

    uint32 rgb = ((RoundReal32ToInt32(color.R * 255.0f) << 16)
        | (RoundReal32ToInt32(color.G * 255.0f) << 8)
        | (RoundReal32ToInt32(color.B * 255.0f) << 0));

    uint8* row = ((uint8 *) buffer->Memory
        + corner_up_left.X * buffer->BytesPerPixel
        + corner_up_left.Y * buffer->Pitch);
    for (int y = corner_up_left.Y; y < corner_down_right.Y; ++y)
    {
        uint32 *pixel = (uint32 *)row;
        for (int x = corner_up_left.X; x < corner_down_right.X; ++x)
            *pixel++ = rgb;

        row += buffer->Pitch;
    }
}

Internal void DrawWireRectangle(GameBackBuffer *buffer, V2r center, V2r size,
    int32 thickness, V3r color)
{
    V2r half_size = 0.5f * size;
    V2i corner_up_left    = RoundReal32ToInt32(center - half_size);
    V2i corner_down_right = RoundReal32ToInt32(center + half_size);

    // TODO: Use ClampV2i;
    ClampInt32(corner_up_left.X,    0, buffer->Width);
    ClampInt32(corner_down_right.X, 0, buffer->Width);
    ClampInt32(corner_up_left.Y,    0, buffer->Height);
    ClampInt32(corner_down_right.Y, 0, buffer->Height);

    int32 inner_left   = corner_up_left.X    + thickness;
    int32 inner_right  = corner_down_right.X - thickness - 1;
    int32 inner_top    = corner_up_left.Y    + thickness;
    int32 inner_bottom = corner_down_right.Y - thickness - 1;
    int32 hollow_size  = inner_right - inner_left - 1;

    uint32 rgb = ((RoundReal32ToInt32(color.R * 255.0f) << 16)
        | (RoundReal32ToInt32(color.G * 255.0f) << 8)
        | (RoundReal32ToInt32(color.B * 255.0f) << 0));

    uint8* row = ((uint8 *) buffer->Memory
        + corner_up_left.X * buffer->BytesPerPixel
        + corner_up_left.Y * buffer->Pitch);
    for (int y = corner_up_left.Y; y < corner_down_right.Y; ++y)
    {
        uint32 *pixel = (uint32 *)row;

        bool32 is_horizontal = ((y >= corner_up_left.Y) && (y < inner_top))
            || ((y > inner_bottom) && (y < corner_down_right.Y));

        if (is_horizontal)
        {
            for (int x = corner_up_left.X; x < corner_down_right.X; ++x)
                *pixel++ = rgb;
        }
        else
        {
            for (int x = corner_up_left.X; x <= inner_left; ++x)
                *pixel++ = rgb;

            pixel += hollow_size;

            for (int x = inner_right; x < corner_down_right.X; ++x)
                *pixel++ = rgb;
        }

        row += buffer->Pitch;
    }
}

Internal uint32 AddEntity(GameState* game_state)
{
    uint32 index = game_state->EntitiesCount++;

    Assert(game_state->EntitiesCount < ArrayCount(game_state->Entities));
    Entity* entity = &game_state->Entities[index];
    *entity = {};

    return index;
}

inline Entity* GetEntity(GameState* game_state, uint32 index)
{
    Entity* entity = 0;

    if ((index > 0) && (index < (game_state->EntitiesCount)))
        entity = &game_state->Entities[index];

    return entity;
}

Internal void InitializeMainCamera(GameState* game_state, uint32 index)
{
    Entity* main_camera = GetEntity(game_state, index);
    game_state->EntityIndexMainCamera = index;
    main_camera->Enabled = true;
    main_camera->Position.Tile = V2i { TILEMAP_WIDTH / 2, TILEMAP_HEIGHT / 2 };
    main_camera->Position.Offset = V2r { 0, 0 };
    main_camera->Size = V2r { TILEMAP_WIDTH, TILEMAP_HEIGHT };
}

Internal void InitializePlayer(GameState* game_state, uint32 index, V2r size)
{
    Entity* player = GetEntity(game_state, index);
    player->Enabled = true;
    player->Position.Tile = V2i { 10, 10 };
    player->Position.Offset = V2rZero();
    player->Size = size;

    if (!game_state->EntityIndexCameraTarget)
        game_state->EntityIndexCameraTarget = index;
}

Internal bool32 CheckCollision(real32 intersection_limit,
    real32 intersection_relative, real32 projection_relative,
    V2r projection_limit, real32 intersection_step, real32 projection_step,
    real32 *fraction)
{
    real32 epsilon = 0.001f;
    bool32 has_collided = false;
    if (intersection_step == 0)
        return has_collided;

    real32 intersection = (intersection_limit - intersection_relative)
        / intersection_step;
    real32 projection = projection_relative + intersection * projection_step;
    if ((intersection >= 0.0f) && (*fraction > intersection))
    {
        has_collided = (projection >= projection_limit.Min)
            && (projection <= projection_limit.Max);
        if (has_collided)
            *fraction = MAX(0.0f, intersection - epsilon);
    }

    return has_collided;
}

Internal Position CalculateNextPosition(Position current, V2r velocity_current,
    V2r velocity_new, real32 delta_time)
{
    Position position = current;
    /*
    NOTE: The original equation of displacement S = u * t + 1/2 * a * t ^ 2
    In this case:
    - velocity_current = u * t, where t is 'delta_time'
    - velocity_new     = a * t, where t is 'delta_time'
    In summary: the velocities are already pre-multiplied with the time once.
    */
    V2r step = velocity_current + (0.5f * velocity_new * delta_time);
    position.Offset += step;

    return position;
}

Internal V2r CalculatePossibleStep(Entity* entity, Position position_next,
    Tilemap* tilemap)
{
    // TODO: Move as constant
    real32 rebound_force = 3;

    real32 tile_side = tilemap->TileSide;
    Position position_current = entity->Position;
    V2r entity_size = entity->Size;
    V2i entity_size_tiles = V2i
    {
        CeilReal32ToInt32(entity_size.X / tile_side),
        CeilReal32ToInt32(entity_size.Y / tile_side),
    };

    V2r step = DiffPositions(position_next, position_current, tile_side);

    real32 move_fraction = 1.0f;
    V2r wall_normal = {};

    V2r tile_min = -0.5f * V2rOne() * tilemap->TileSide - 0.5f * entity_size;
    V2r tile_max =  0.5f * V2rOne() * tilemap->TileSide + 0.5f * entity_size;

    V2r limit_x = V2r { tile_min.X, tile_max.X };
    V2r limit_y = V2r { tile_min.Y, tile_max.Y };

    V2i tile_range_x = V2i
    {
        MIN(position_current.Tile.X - entity_size_tiles.X,
            position_next.Tile.X    + entity_size_tiles.X),
        MAX(position_current.Tile.X - entity_size_tiles.X,
            position_next.Tile.X    + entity_size_tiles.X),
    };

    V2i tile_range_y = V2i
    {
        MIN(position_current.Tile.Y - entity_size_tiles.Y,
            position_next.Tile.Y    + entity_size_tiles.Y),
        MAX(position_current.Tile.Y - entity_size_tiles.Y,
            position_next.Tile.Y    + entity_size_tiles.Y),
    };

    for (int32 tile_y = tile_range_y.Min; tile_y <= tile_range_y.Max; ++tile_y)
    {
        for (int32 tile_x = tile_range_x.Min; tile_x <= tile_range_x.Max; ++tile_x)
        {
            V2i tile_test = V2i { tile_x, tile_y };

            Position position_test = {};
            position_test.Tile = tile_test;

            if (IsTileEmpty(tilemap, position_test))
                continue;

            V2r diff = DiffPositions(position_current, position_test, tile_side);
            bool32 has_collided_left = CheckCollision(tile_min.X, diff.X, diff.Y,
                limit_y, step.X, step.Y, &move_fraction);
            bool32 has_collided_right = CheckCollision(tile_max.X, diff.X, diff.Y,
                limit_y, step.X, step.Y, &move_fraction);
            bool32 has_collided_top = CheckCollision(tile_min.Y, diff.Y, diff.X,
                limit_x, step.Y, step.X, &move_fraction);
            bool32 has_collided_bottom = CheckCollision(tile_max.Y, diff.Y, diff.X,
                limit_x, step.Y, step.X, &move_fraction);

            if (has_collided_left)
                wall_normal.X = -1;

            if (has_collided_right)
                wall_normal.X =  1;

            if (has_collided_top)
                wall_normal.Y = -1;

            if (has_collided_bottom)
                wall_normal.Y =  1;
        }
    }

    step = step * move_fraction;
    entity->Velocity -= rebound_force * DotProduct(entity->Velocity, wall_normal)
        * wall_normal;
    step -= rebound_force * DotProduct(step, wall_normal) * wall_normal;

    return step;
}

Internal void MoveEntity(Tilemap* tilemap, Entity* entity,
    real32 delta_time, V2r direction)
{
    // TODO: Move as constants
    real32 friction_coeficient = 3;
    real32 default_speed = 12;

    real32 direction_length_sqr = DotProduct(direction, direction);
    if (direction_length_sqr > 1)
        Normalize(direction);

    V2r friction = friction_coeficient * entity->Velocity;
    V2r velocity = (direction * default_speed - friction) * delta_time;
    entity->Velocity += velocity;

    Position next_position = CalculateNextPosition(entity->Position,
        entity->Velocity, velocity, delta_time);
    NormalizePosition(&next_position, tilemap->TileSide);

    V2r step = CalculatePossibleStep(entity, next_position, tilemap);

    next_position = entity->Position;
    next_position.Offset += step;
    NormalizePosition(&next_position, tilemap->TileSide);

    if (IsTileEmpty(tilemap, next_position))
        entity->Position = next_position;
}

extern "C" void UpdateAndRender(ThreadContext* thread, GameMemory *memory,
    GameInput *input, GameBackBuffer *display_buffer)
{
    Assert((&input->Controller[0].MAX - &input->Controller[0].Buttons[0])
        == ArrayCount(input->Controller[0].Buttons));
    Assert(sizeof(GameState) <= memory->PermanentStorageSize);

    int32 collider_visual_width = 3;

    GameState* game_state = (GameState *)memory->PermanentStorage;
    if (!memory->IsInitialized)
    {
        // First entity is reserved - a null entity;
        AddEntity(game_state);

        InitializeMemory(&game_state->GameMemory,
            memory->PermanentStorageSize - sizeof(GameState),
            (uint8*)memory->PermanentStorage + sizeof(GameState));

        uint32 main_camera_index = AddEntity(game_state);
        InitializeMainCamera(game_state, main_camera_index);

        game_state->World = AllocateStruct(&game_state->GameMemory, World);
        World* world = game_state->World;
        world->Origin = V2rZero();
        world->TilemapIndex = 0;
        world->Tilemaps = AllocateArray(
            &game_state->GameMemory,
            ArrayCount(TILES),
            Tilemap);

        for (int tilemap_index = 0; tilemap_index < ArrayCount(TILES); ++tilemap_index)
        {
            uint32 tiles_count = ArrayCount(TILES[tilemap_index]);
            Tilemap* tilemap = &world->Tilemaps[tilemap_index];
            tilemap->Tiles = AllocateArray(&game_state->GameMemory, tiles_count, uint32);
            tilemap->Size = V2i { TILEMAP_WIDTH, TILEMAP_HEIGHT };
            tilemap->TileSide = (real32)((int32)(display_buffer->Width / tilemap->Size.Width));

            for (int row = 0; row < TILEMAP_HEIGHT; ++row)
            {
                for (int col = 0; col < TILEMAP_WIDTH; ++col)
                {
                    uint32 tile = row * TILEMAP_WIDTH + col;
                    tilemap->Tiles[tile] = TILES[tilemap_index][tile];
                }
            }
        }

        char* tank_png_relative_path = "tank-baw.png";
        ReadFileResult raw_png = memory->ReadFile(thread, tank_png_relative_path);
        Stream raw_png_stream = {};
        raw_png_stream.Size = raw_png.Size;
        raw_png_stream.Content = raw_png.Content;
        game_state->TankImage = ParsePNG(raw_png_stream);

        game_state->ToneHz = 400;
        memory->IsInitialized = true;
    }

    Entity* main_camera = GetEntity(game_state,
        game_state->EntityIndexMainCamera);

    Tilemap* tilemap = &game_state->World->Tilemaps[
        game_state->World->TilemapIndex];
    real32 tile_side = (real32)(display_buffer->Width / tilemap->Size.Width);
    tilemap->TileSide = tile_side;
    game_state->World->Origin = V2rOne() * tile_side * 0.5f;

    for (int relative_row = -(int)main_camera->Size.Height;
         relative_row < (int)main_camera->Size.Height;
         ++relative_row)
    {
        for (int relative_column = -(int)main_camera->Size.Width;
             relative_column < (int)main_camera->Size.Width;
             ++relative_column)
        {
            int row = main_camera->Position.Tile.Y + relative_row;
            int column = main_camera->Position.Tile.X + relative_column;

            V3r tile_color = { 0.5f, 0.5f, 0.5f };
            V2i tile = { column, row };
            uint32 tile_id = GetTileValue(tilemap, tile);
            if (tile_id == 1)
                tile_color = { 1.0f, 1.0f, 1.0f };

            V2r tile_size = V2rOne() * tile_side;
            V2r tile_center = game_state->World->Origin + tile * tile_side;
            DrawRectangle(display_buffer, tile_center, tile_size, tile_color);

            V3r color = { 0.34f, 0.71f, 0.12f };
            DrawWireRectangle(display_buffer, tile_center, tile_size, 1, color);
        }
    }

    for (int8 controller_index = 0;
         controller_index < ArrayCount(input->Controllers);
         ++controller_index)
    {
        ControllerState *controller = GetController(input, controller_index);

        Entity* player = GetEntity(game_state,
            game_state->EntityIndexPlayers[controller_index]);
        if (player)
        {
            if (controller->Start.EndedDown)
            {
                player->Position.Tile = V2i { 10, 10 };
                player->Position.Offset = V2rZero();
            }

            V2r direction = V2rZero();
            if (controller->IsAnalog)
            {
                direction.X += (int)(4.0f * controller->LeftStickAverageX);
                direction.Y -= (int)(4.0f * controller->LeftStickAverageY);
            }
            else
            {
                if (controller->MoveLeft.EndedDown)
                    direction.X -= 1;
                if (controller->MoveRight.EndedDown)
                    direction.X += 1;
                if (controller->MoveUp.EndedDown)
                    direction.Y -= 1;
                if (controller->MoveDown.EndedDown)
                    direction.Y += 1;
            }

            MoveEntity(tilemap, player, input->DeltaTime, direction);
        }
        else
        {
            if (controller->Start.EndedDown)
            {
                uint32 player_index = AddEntity(game_state);
                V2r player_size = V2r { 0.6f, 0.9f } * tilemap->TileSide;
                InitializePlayer(game_state, player_index, player_size);
                game_state->EntityIndexPlayers[controller_index] = player_index;
            }
        }
    }

    Entity* player1 = GetEntity(game_state, game_state->EntityIndexCameraTarget);
    if (player1)
    {
        V2r player_tile_absolute = game_state->World->Origin
            + player1->Position.Tile * tile_side;
        V2r player_position = player_tile_absolute + player1->Position.Offset;

        DrawRectangle(display_buffer, player_tile_absolute,
            V2rOne() * tile_side, V3rOne() * 0.25f);

        DrawPngImage(display_buffer, &game_state->TankImage, player_position,
            player1->Size);

        // V3r collider_color = { 0, 1, 1 };
        // DrawWireRectangle(display_buffer, player_left_top, player_right_bottom,
        //     collider_visual_width, collider_color);

        // V2r collision_points[] =
        // {
        //     player_position - (0.5f * player1->Size),
        //     player_position + (0.5f * player1->Size),
        //     player_position + (0.5f * V2r { -player1->Size.Width, player1->Size.Height }),
        //     player_position + (0.5f * V2r { player1->Size.Width, -player1->Size.Height }),
        // };

        // for (int c = 0; c < 4; ++c)
        // {
        //     V2r point = collision_points[c];
        //     V2r point_rect_min = point + V2rOne() * -3;
        //     V2r point_rect_max = point + V2rOne() *  3;
        //     DrawRectangle(display_buffer,
        //                   point_rect_min,
        //                   point_rect_max,
        //                   V3r{ 1, 0, 0 });
        // }
    }

    // Enemy visualization
    // game_state->EnemyPosition = NormalizeWorldPosition(&world, game_state->EnemyPosition);
    // V2r enemy_left_top = world.Origin
    //     + game_state->EnemyPosition.Tile * world.TileSidePixels
    //     + game_state->EnemyPosition.TileRelative * world.GameUnits2Pixels;
    // V2r enemy_right_bottom = enemy_left_top
    //     + V2r{ tank_width, tank_height } * world.GameUnits2Pixels;
    // DrawWireRectangle(display_buffer, enemy_left_top, enemy_right_bottom,
    //     collider_visual_width, collider_color);
    // DrawPngImage(display_buffer, &game_state->TankImage, enemy_left_top,
    //     V2r{ tank_width, tank_height } * world.GameUnits2Pixels);

    // Camera area visualization
    // V2r camera_position = world.Origin
    //     + game_state->CameraPosition.Tile * world.TileSidePixels
    //     + game_state->CameraPosition.TileRelative * world.GameUnits2Pixels;
    // V3r camera_wire_color = V3r{ 1, 0, 1 };
    // V2r camera_left_top = camera_position
    //     - V2r{ 5, 5 } * world.GameUnits2Pixels;
    // V2r camera_right_bottom = camera_position
    //     + V2r{ 5, 5 } * world.GameUnits2Pixels;
    // DrawWireRectangle(display_buffer, camera_left_top, camera_right_bottom,
    //     collider_visual_width, camera_wire_color);
}

extern "C" void GetSoundSamples(ThreadContext* thread, GameMemory* memory,
    GameSoundBuffer *sound_buffer)
{
    GameState* game_state = (GameState*)memory->PermanentStorage;

    bool32 is_sound_unmuted = false;
    if (is_sound_unmuted)
        OutputSound(game_state, sound_buffer);
}
