#include "tanks.h"

#define TILEMAP_WIDTH 33
#define TILEMAP_HEIGHT 18

uint32 TILES[4][TILEMAP_HEIGHT * TILEMAP_WIDTH] =
{

{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
},

{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
},

{
    1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
},

{
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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
    int32 offset = FloorReal32ToInt32(*relative / tilemap->TileSideGameUnits);
    *tile += offset;
    *relative -= offset * tilemap->TileSideGameUnits;

    Assert(*relative >= 0);
    Assert(*relative <= tilemap->TileSideGameUnits);
}

inline Position NormalizePosition(Tilemap* tilemap, Position position)
{
    Position result = position;

    NormalizeCoordinate(tilemap, &result.Tile.X, &result.Offset.X);
    NormalizeCoordinate(tilemap, &result.Tile.Y, &result.Offset.Y);

    return result;
}

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
    main_camera->Position.Offset = { 0, 0 };
    main_camera->Size = V2r { 20, 15 };
}

Internal void InitializePlayer(GameState* game_state, uint32 index)
{
    Entity* player = GetEntity(game_state, index);
    player->Enabled = true;
    player->Position.Tile = { 10, 10 };
    player->Position.Offset = { 5.0f, 5.0f };

    real32 tank_height = 1.4f;
    real32 tank_width = 0.65f * tank_height;
    player->Size = V2r{ tank_width, tank_height };

    if (!game_state->EntityIndexCameraTarget)
        game_state->EntityIndexCameraTarget = index;
}

Internal void MoveEntity(GameState* game_state, Entity* entity,
    real32 delta_time, V2r direction)
{
    if (direction != V2rZero())
        Normalize(direction);

    real32 friction_coeficient = 3;
    real32 default_speed = 16;
    Tilemap* tilemap = &game_state->World->Tilemaps[
        game_state->World->TilemapIndex];

    V2r friction = friction_coeficient * entity->Velocity;
    V2r velocity = direction * default_speed - friction;

    Position next_position = entity->Position;
    V2r step = entity->Velocity * delta_time
        + (0.5f * velocity * (delta_time * delta_time));
    next_position.Offset += step;
    entity->Velocity += velocity * delta_time;

    next_position = NormalizePosition(tilemap, next_position);

    Position bottom_left = next_position;
    bottom_left.Offset.X -= 0.5f * entity->Size.Width;
    bottom_left.Offset.Y += 0.5f * entity->Size.Height;
    bottom_left = NormalizePosition(tilemap, bottom_left);

    Position bottom_right = next_position;
    bottom_right.Offset += 0.5f * entity->Size;
    bottom_right = NormalizePosition(tilemap, bottom_right);

    Position top_left = next_position;
    top_left.Offset -= 0.5f * entity->Size;
    top_left = NormalizePosition(tilemap, top_left);

    Position top_right = next_position;
    top_right.Offset.X += 0.5f * entity->Size.Width;
    top_right.Offset.Y -= 0.5f * entity->Size.Height;
    top_right = NormalizePosition(tilemap, top_right);

    bool32 is_empty_bottom_left   = IsTileEmpty(tilemap, bottom_left);
    bool32 is_empty_bottom_right  = IsTileEmpty(tilemap, bottom_right);
    bool32 is_empty_top_left      = IsTileEmpty(tilemap, top_left);
    bool32 is_empty_top_right     = IsTileEmpty(tilemap, top_right);

    bool32 collided = (!is_empty_bottom_left)
        || (!is_empty_bottom_right)
        || (!is_empty_top_left)
        || (!is_empty_top_right);
    Position collision_position = {};
    if (!is_empty_bottom_left)
        collision_position = bottom_left;

    if (!is_empty_bottom_right)
        collision_position = bottom_right;

    if (!is_empty_top_left)
        collision_position = top_left;

    if (!is_empty_top_right)
        collision_position = top_right;

    if (collided)
    {
        V2r reflection = { 0, 0 };
        if (collision_position.Tile.X < entity->Position.Tile.X)
            reflection.X = 1;
        if (collision_position.Tile.X > entity->Position.Tile.X)
            reflection.X = -1;
        if (collision_position.Tile.Y < entity->Position.Tile.Y)
            reflection.Y = 1;
        if (collision_position.Tile.Y > entity->Position.Tile.Y)
            reflection.Y = -1;

        Normalize(reflection);
        entity->Velocity -= 1.5f * reflection
            * DotProduct(entity->Velocity, reflection);
    }
    else
    {
        entity->Position = next_position;
    }
}

extern "C" void UpdateAndRender(ThreadContext* thread, GameMemory *memory, GameInput *input,
    GameBackBuffer *display_buffer)
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
            tilemap->TileSidePixels = 60;
            tilemap->TileSideGameUnits = 1.4f;
            tilemap->GameUnits2Pixels = (real32)tilemap->TileSidePixels
                / (real32)tilemap->TileSideGameUnits;

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
    real32 tile_side_pixels = game_state->World->Tilemaps[
        game_state->World->TilemapIndex].TileSidePixels;

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

            V2r min = game_state->World->Origin + tile * tile_side_pixels;
            V2r max = min + V2rOne() * tile_side_pixels;
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
                InitializePlayer(game_state, player_index);
                game_state->EntityIndexPlayers[controller_index] = player_index;
            }
        }
    }

    Entity* player1 = GetEntity(game_state, game_state->EntityIndexCameraTarget);
    if (player1)
    {
        real32 game_units2pixels = game_state->World->Tilemaps[
            game_state->World->TilemapIndex].GameUnits2Pixels;
        V2r player_half_size = player1->Size * 0.5f * game_units2pixels;
        V2r player_position = game_state->World->Origin
            + player1->Position.Tile * tile_side_pixels
            + player1->Position.Offset * game_units2pixels;
        V2r player_left_top = player_position - player_half_size;
        V2r player_right_bottom = player_position + player_half_size;

        DrawPngImage(display_buffer, &game_state->TankImage, player_left_top,
            player1->Size * game_units2pixels);

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
