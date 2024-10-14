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

Internal void DrawPngImage(GameBackBuffer* buffer, Image* image, V2r origin,
    V2r size)
{
    V2r opposite = origin + size;
    V2i origin_int = RoundReal32ToInt32(origin);
    V2i opposite_int = RoundReal32ToInt32(opposite);
    V2r scale =
    {
        size.Width / image->Width,
        size.Height / image->Height,
    };

    ClampInt32(origin_int.X, 0, buffer->Width);
    ClampInt32(opposite_int.X, 0, buffer->Width);
    ClampInt32(origin_int.Y, 0, buffer->Height);
    ClampInt32(opposite_int.Y, 0, buffer->Height);

    uint8* row = (uint8*)buffer->Memory
        + origin_int.X * buffer->BytesPerPixel
        + origin_int.Y * buffer->Pitch;
    for (int y = origin_int.Y; y < opposite_int.Y; ++y)
    {
        uint32 y_scaled = (uint32)((y - origin_int.Y) / scale.Y);
        uint32* pixel_buffer = (uint32*)row;
        for (int x = origin_int.X; x < opposite_int.X; ++x)
        {
            uint32 x_scaled = (uint32)((x - origin_int.X) / scale.X);
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

inline void NormalizeCoordinate(Tilemap* tilemap, int32* tile, real32* relative)
{
    int32 offset = FloorReal32ToInt32(*relative / tilemap->TileSide);
    *tile += offset;
    *relative -= offset * tilemap->TileSide;

    Assert(*relative >= 0);
    Assert(*relative <= tilemap->TileSide);
}

// inline void Position2Tile(Tilemap* tilemap, Position* position)
inline V2i Position2Tile(V2r position, real32 tile_side)
{
    // TODO: Validate position;
    V2i result = { 0, 0 };

    result = V2i
    {
        TruncateReal32ToInt32(position.X / tile_side),
        TruncateReal32ToInt32(position.Y / tile_side)
    };

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

Internal void DrawRectangle(GameBackBuffer *buffer, V2r min, V2r max, V3r color)
{
    V2i int_min = RoundReal32ToInt32(min);
    V2i int_max = RoundReal32ToInt32(max);

    ClampInt32(int_min.X, 0, buffer->Width);
    ClampInt32(int_max.X, 0, buffer->Width);
    ClampInt32(int_min.Y, 0, buffer->Height);
    ClampInt32(int_max.Y, 0, buffer->Height);

    uint32 rgb = ((RoundReal32ToInt32(color.R * 255.0f) << 16)
        | (RoundReal32ToInt32(color.G * 255.0f) << 8)
        | (RoundReal32ToInt32(color.B * 255.0f) << 0));

    uint8* row = ((uint8 *) buffer->Memory
        + int_min.X * buffer->BytesPerPixel
        + int_min.Y * buffer->Pitch);
    for (int y = int_min.Y; y < int_max.Y; ++y)
    {
        uint32 *pixel = (uint32 *)row;
        for (int x = int_min.X; x < int_max.X; ++x)
            *pixel++ = rgb;

        row += buffer->Pitch;
    }
}

Internal void DrawWireRectangle(GameBackBuffer *buffer, V2r min, V2r max,
    int32 thickness, V3r color)
{
    V2i int_min = RoundReal32ToInt32(min);
    V2i int_max = RoundReal32ToInt32(max);

    // TODO: Use ClampV2i;
    ClampInt32(int_min.X, 0, buffer->Width);
    ClampInt32(int_max.X, 0, buffer->Width);
    ClampInt32(int_min.Y, 0, buffer->Height);
    ClampInt32(int_max.Y, 0, buffer->Height);

    int32 inner_left   = int_min.X + thickness;
    int32 inner_right  = int_max.X - thickness - 1;
    int32 inner_top    = int_min.Y + thickness;
    int32 inner_bottom = int_max.Y - 1 - thickness;
    int32 hollow_size  = inner_right - inner_left - 1;

    uint32 rgb = ((RoundReal32ToInt32(color.R * 255.0f) << 16)
        | (RoundReal32ToInt32(color.G * 255.0f) << 8)
        | (RoundReal32ToInt32(color.B * 255.0f) << 0));

    uint8* row = ((uint8 *) buffer->Memory
        + int_min.X * buffer->BytesPerPixel
        + int_min.Y * buffer->Pitch);
    for (int y = int_min.Y; y < int_max.Y; ++y)
    {
        uint32 *pixel = (uint32 *)row;

        bool32 is_horizontal = ((y >= int_min.Y) && (y < inner_top))
            || ((y > inner_bottom) && (y < int_max.Y));

        if (is_horizontal)
        {
            for (int x = int_min.X; x < int_max.X; ++x)
                *pixel++ = rgb;
        }
        else
        {
            for (int x = int_min.X; x <= inner_left; ++x)
                *pixel++ = rgb;

            pixel += hollow_size;

            for (int x = inner_right; x < int_max.X; ++x)
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
    main_camera->Position.Absolute = V2r { 0, 0 };
    main_camera->Size = V2r { TILEMAP_WIDTH, TILEMAP_HEIGHT };
}

Internal void InitializePlayer(GameState* game_state, uint32 index, V2r size)
{
    Entity* player = GetEntity(game_state, index);
    player->Enabled = true;
    player->Position.Absolute = { 600.0f, 600.0f };
    Tilemap tilemap = game_state->World->Tilemaps[game_state->World->TilemapIndex];
    player->Position.Tile = Position2Tile(player->Position.Absolute,
        tilemap.TileSide);

    player->Size = size;

    if (!game_state->EntityIndexCameraTarget)
        game_state->EntityIndexCameraTarget = index;
}

Internal bool32 CheckCollision(real32 intersection_limit,
    real32 intersection_relative, real32 projection_relative,
    V2r projection_limit, real32 intersection_step, real32 projection_step, real32 *fraction)
{
    real32 epsilon = 0.001f;
    bool32 has_collided = false;
    if (intersection_step == 0)
        return has_collided;

    real32 intersection = (intersection_limit - intersection_relative) / intersection_step;
    real32 projection = projection_relative + intersection * projection_step;
    if ((intersection >= 0.0f) && (*fraction > intersection))
    {
        if ((projection >= projection_limit.Min) && (projection <= projection_limit.Max))
        {
            *fraction = MAX(0.0f, intersection - epsilon);
            has_collided = true;
        }
    }

    return has_collided;
}

Internal void GetClosestFreePosition(Entity* entity, Position next_position,
    Tilemap* tilemap)
{
    V2r step = next_position.Absolute - entity->Position.Absolute;

    // real32 rebound_force = 3;
    // V2r wall_normal = {};

    real32 t_min_x = 1.0f;
    real32 t_min_y = 1.0f;
    real32 t_min_y_precheck = 1.0f;
    V2r tile_min = V2rZero();
    V2r tile_max = V2rOne() * tilemap->TileSide;

    // V2i oposite_direction = entity->Position.Tile - next_position.Tile;
    V2i tiles_range[] =
    {
        V2i {next_position.Tile.X, entity->Position.Tile.Y},
        V2i {entity->Position.Tile.X, next_position.Tile.Y},
        next_position.Tile
    };

    for (int i = 0; i < ArrayCount(tiles_range); ++i)
    {
        V2i tile_test = tiles_range[i];

        Position position_test;
        position_test.Tile = tile_test;
        position_test.Absolute = V2r
        {
            (real32)position_test.Tile.X * tilemap->TileSide,
            (real32)position_test.Tile.Y * tilemap->TileSide
        };

        if (IsTileEmpty(tilemap, position_test))
            continue;

        V2r position_diff = entity->Position.Absolute - position_test.Absolute;

        // Pre-check the Y axis.
        CheckCollision(tile_min.Y, position_diff.Y,
            position_diff.X, V2r { tile_min.X, tile_max.X }, step.Y, step.X,
            &t_min_y_precheck);
        CheckCollision(tile_max.Y, position_diff.Y,
            position_diff.X, V2r { tile_min.X, tile_max.X }, step.Y, step.X,
            &t_min_y_precheck);

        bool32 has_collided_left = CheckCollision(tile_min.X, position_diff.X,
            position_diff.Y, V2r { tile_min.Y, tile_max.Y }, step.X, step.Y * t_min_y_precheck,
            &t_min_x);
        bool32 has_collided_right = CheckCollision(tile_max.X, position_diff.X,
            position_diff.Y, V2r { tile_min.Y, tile_max.Y }, step.X, step.Y * t_min_y_precheck,
            &t_min_x);
        bool32 has_collided_top = CheckCollision(tile_min.Y, position_diff.Y,
            position_diff.X, V2r { tile_min.X, tile_max.X }, step.Y, step.X * t_min_x,
            &t_min_y);
        bool32 has_collided_bottom = CheckCollision(tile_max.Y, position_diff.Y,
            position_diff.X, V2r { tile_min.X, tile_max.X }, step.Y, step.X * t_min_x,
            &t_min_y);

            // if (has_collided_left)
            //     wall_normal.X = -1;

            // if (has_collided_right)
            //     wall_normal.X = 1;

            // if (has_collided_top)
            //     wall_normal.Y = -1;

            // if (has_collided_bottom)
            //     wall_normal.Y = 1;
        // }
    }

    next_position = entity->Position;
    next_position.Absolute += V2r{ t_min_x * step.X, t_min_y * step.Y };
    next_position.Tile = Position2Tile(next_position.Absolute, tilemap->TileSide);
    if (IsTileEmpty(tilemap, next_position))
        entity->Position = next_position;

    // entity->Velocity -= rebound_force * DotProduct(entity->Velocity, wall_normal) * wall_normal;
    // step -= rebound_force * DotProduct(step, wall_normal) * wall_normal;
}

Internal void MoveEntity(GameState* game_state, Entity* entity,
    real32 delta_time, V2r direction)
{
    real32 direction_length_sqr = DotProduct(direction, direction);
    if (direction_length_sqr > 1)
        Normalize(direction);

    real32 friction_coeficient = 3;
    real32 default_speed = 250;
    Tilemap* tilemap = &game_state->World->Tilemaps[
        game_state->World->TilemapIndex];

    V2r friction = friction_coeficient * entity->Velocity;
    V2r velocity = direction * default_speed - friction;

    Position next_position = entity->Position;
    V2r step = entity->Velocity * delta_time
        + (0.5f * velocity * (delta_time * delta_time));
    next_position.Absolute += step;
    next_position.Tile = Position2Tile(next_position.Absolute, tilemap->TileSide);
    entity->Velocity += velocity * delta_time;

    GetClosestFreePosition(entity, next_position, tilemap);
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
    tilemap->TileSide = (real32)(display_buffer->Width / tilemap->Size.Width);

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

            V2r min = game_state->World->Origin + tile * tilemap->TileSide;
            V2r max = min + V2rOne() * tilemap->TileSide;
            DrawRectangle(display_buffer, min, max, tile_color);

            V3r color = { 0.34f, 0.71f, 0.12f };
            DrawWireRectangle(display_buffer, min, max, 1, color);
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
                player->Position.Absolute = V2r { 600.0f, 600.0f };
                player->Position.Tile = Position2Tile(player->Position.Absolute, tilemap->TileSide);
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

            MoveEntity(game_state, player, input->DeltaTime, direction);
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
        V2r player_half_size = player1->Size * 0.5f;
        V2r player_position = game_state->World->Origin
            + player1->Position.Absolute;
        V2r player_left_top = player_position - player_half_size;
        V2r player_right_bottom = player_position + player_half_size;

        V2r player_tile_absolute = V2r
        {
            player1->Position.Tile.X * tilemap->TileSide,
            player1->Position.Tile.Y * tilemap->TileSide
        };

        DrawRectangle(display_buffer, player_tile_absolute,
            player_tile_absolute + V2rOne() * tilemap->TileSide,
            V3r{ 0.25f, 0.25f, 0.25f});

        DrawPngImage(display_buffer, &game_state->TankImage, player_left_top,
            player1->Size);

        V3r collider_color = { 0, 1, 0 };
        DrawWireRectangle(display_buffer, player_left_top, player_right_bottom,
            collider_visual_width, collider_color);
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
