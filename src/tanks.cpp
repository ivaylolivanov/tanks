#include "tanks.h"

#define TILEMAP_WIDTH 33
#define TILEMAP_HEIGHT 18

uint32 TILES00[TILEMAP_HEIGHT][TILEMAP_WIDTH] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

uint32 TILES01[TILEMAP_HEIGHT][TILEMAP_WIDTH] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

uint32 TILES10[TILEMAP_HEIGHT][TILEMAP_WIDTH] =
{
    {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,  0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,  1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

uint32 TILES11[TILEMAP_HEIGHT][TILEMAP_WIDTH] =
{
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0,0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0,0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0,0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0,0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
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

inline void NormalizeWorldCoordinates(World* world, int32 tile_count, int32* tilemap,
    int32* tile, real32* tile_relative)
{
    int32 offset = FloorReal32ToInt32(*tile_relative / world->TileSideGameUnits);
    *tile += offset;
    *tile_relative -= offset * world->TileSideGameUnits;

    Assert(*tile_relative >= 0);
    Assert(*tile_relative <= world->TileSideGameUnits);

    if (*tile < 0)
    {
        *tile = tile_count + *tile;
        --*tilemap;
    }

    if (*tile >= tile_count)
    {
        *tile = *tile - tile_count;
        ++*tilemap;
    }
}

inline WorldPosition NormalizeWorldPosition(World* world, WorldPosition position)
{
    WorldPosition result = position;

    NormalizeWorldCoordinates(world, world->TilemapWidth, &result.Tilemap.X,
        &result.Tile.X, &result.TileRelative.X);
    NormalizeWorldCoordinates(world, world->TilemapHeight, &result.Tilemap.Y,
        &result.Tile.Y, &result.TileRelative.Y);

    return result;
}

Internal Tilemap* GetTilemap(World* world, int32 world_x, int32 world_y)
{
    Tilemap* tilemap = 0;

    if ((world_x >= 0) && (world_x < world->TilemapWidth)
        && (world_y >= 0) && (world_y < world->TilemapHeight))
        tilemap = &world->Tilemaps[world_y * world->WorldWidth + world_x];

    return tilemap;
}

Internal uint32 GetTileValue(World* world, Tilemap* tilemap, int32 tile_x, int32 tile_y)
{
    Assert(tilemap);
    Assert((tile_x >= 0) && (tile_x < world->TilemapWidth));
    Assert((tile_y >= 0) && (tile_y < world->TilemapHeight));

    uint32 value = tilemap->Tiles[world->TilemapWidth * tile_y + tile_x];
    return value;
}

inline bool32 IsTilemapPointEmpty(World* world, Tilemap* tilemap, int32 x, int32 y)
{
    bool32 result = false;

    if ((x >= 0) && (x < world->TilemapWidth)
        && (y >= 0) && (y < world->TilemapHeight))
    {
        uint32 tile_value = GetTileValue(world, tilemap, x, y);
        result = (tile_value == 0);
    }

    return result;
}

Internal bool32 IsWorldPointEmpty(World* world, WorldPosition position)
{
    bool32 result = false;

    Tilemap* tilemap = GetTilemap(world, position.Tilemap.X, position.Tilemap.Y);
    if (!tilemap) return result;

    result = IsTilemapPointEmpty(world, tilemap, position.Tile.X, position.Tile.Y);
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

extern "C" void UpdateAndRender(ThreadContext* thread, GameMemory *memory, GameInput *input,
    GameBackBuffer *display_buffer)
{
    Assert((&input->Controller[0].MAX - &input->Controller[0].Buttons[0])
        == ArrayCount(input->Controller[0].Buttons));
    Assert(sizeof(GameState) <= memory->PermanentStorageSize);

    Tilemap tilemaps[2][2];
    tilemaps[0][0].Tiles = (uint32 *) TILES00;
    tilemaps[0][1].Tiles = (uint32 *) TILES01;
    tilemaps[1][0].Tiles = (uint32 *) TILES10;
    tilemaps[1][1].Tiles = (uint32 *) TILES11;

    World world;
    world.Origin = { 0, 0 };
    world.WorldWidth = 2;
    world.WorldHeight = 2;
    world.TilemapWidth = TILEMAP_WIDTH;
    world.TilemapHeight = TILEMAP_HEIGHT;
    world.TileSideGameUnits = 1.4f;
    world.TileSidePixels = 60;
    world.GameUnits2Pixels = (real32)world.TileSidePixels
        / (real32)world.TileSideGameUnits;
    world.Tilemaps = (Tilemap*)tilemaps;

    V3r player_color = { 0.45f, 0.15f, 0.65f };
    real32 tank_height = 1.4f;
    real32 tank_width = 0.65f * tank_height;
    real32 tank_speed = 10.0f;
    int32 collider_visual_width = 3;

    GameState* game_state = (GameState *)memory->PermanentStorage;
    if (!memory->IsInitialized)
    {
        char* tank_png_relative_path = "tank-baw.png";
        ReadFileResult raw_png = memory->ReadFile(thread, tank_png_relative_path);
        Stream raw_png_stream = {};
        raw_png_stream.Size = raw_png.Size;
        raw_png_stream.Content = raw_png.Content;

        game_state->TankImage = ParsePNG(raw_png_stream);

        game_state->CameraPosition.Tilemap = { 0, 0 };
        game_state->CameraPosition.Tile = { 15, 9 };
        game_state->CameraPosition.TileRelative = { 0, 0 };

        game_state->PlayerPosition.Tilemap = { 0, 0 };
        game_state->PlayerPosition.Tile = { 10, 10 };
        game_state->PlayerPosition.TileRelative = { 5.0f, 5.0f };

        game_state->EnemyPosition.Tilemap = { 0, 0 };
        game_state->EnemyPosition.Tile = { 10, 2 };
        game_state->EnemyPosition.TileRelative = { 5.0f, 5.0f };

        game_state->ToneHz = 400;
        memory->IsInitialized = true;
    }

    // The camera follows the player
    game_state->CameraPosition = game_state->PlayerPosition;
    int32 camera_half_height = 10;
    int32 camera_half_width = 16;

    Tilemap* tilemap = GetTilemap(&world, game_state->PlayerPosition.Tilemap.X,
        game_state->PlayerPosition.Tilemap.Y);

    for (int relative_row = -camera_half_height; relative_row < camera_half_height; ++relative_row)
    {
        for (int relative_column = -camera_half_width; relative_column < camera_half_width; ++relative_column)
        {
            int row = game_state->CameraPosition.Tile.Y + relative_row;
            int column = game_state->CameraPosition.Tile.X + relative_column;

            V3r tile_color = { 0.5f, 0.5f, 0.5f };
            uint32 tile_id = GetTileValue(&world, tilemap, column, row);
            if (tile_id == 1)
                tile_color = { 1.0f, 1.0f, 1.0f };

            V2i tile = { column, row };
            if (column == game_state->PlayerPosition.Tile.X
                && row == game_state->PlayerPosition.Tile.Y)
                tile_color = { 0.4f, 0.4f, 0.4f };
            else if (column == game_state->EnemyPosition.Tile.X
                && row == game_state->EnemyPosition.Tile.Y)
                tile_color = { 0.4f, 0.4f, 0.4f };

            V2r min = world.Origin + tile * world.TileSidePixels;
            V2r max = min + V2rOne() * world.TileSidePixels;
            DrawRectangle(display_buffer, min, max, tile_color);
            V3r color = { 0.34f, 0.71f, 0.12f };
            DrawWireRectangle(display_buffer, min, max, 1, color);
        }
    }

    for (int8 controller_index = 0; controller_index < ArrayCount(input->Controllers); ++controller_index)
    {
        V2r direction = V2rZero();
        ControllerState *controller = GetController(input, controller_index);
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

        if (direction != V2rZero())
            Normalize(direction);

        real32 friction_coeficient = 1.75f;
        V2r friction = friction_coeficient * game_state->PlayerVelocity;
        V2r velocity = direction * tank_speed - friction;

        WorldPosition next_player_position = game_state->PlayerPosition;
        V2r step = game_state->PlayerVelocity * input->DeltaTime
            + (0.5f * velocity * (input->DeltaTime * input->DeltaTime));
        next_player_position.TileRelative += step;
        game_state->PlayerVelocity += velocity * input->DeltaTime;

        next_player_position = NormalizeWorldPosition(&world,
            next_player_position);

        WorldPosition player_position_bottom_left = next_player_position;
        player_position_bottom_left.TileRelative.X -= 0.5f * tank_width;
        player_position_bottom_left.TileRelative.Y += 0.5f * tank_height;
        player_position_bottom_left = NormalizeWorldPosition(&world,
            player_position_bottom_left);

        WorldPosition player_position_bottom_right = next_player_position;
        player_position_bottom_right.TileRelative.X += 0.5f * tank_width;
        player_position_bottom_right.TileRelative.Y += 0.5f * tank_height;
        player_position_bottom_right = NormalizeWorldPosition(&world,
            player_position_bottom_right);

        WorldPosition player_position_top_left = next_player_position;
        player_position_top_left.TileRelative.X -= 0.5f * tank_width;
        player_position_top_left.TileRelative.Y -= 0.5f * tank_height;
        player_position_top_left = NormalizeWorldPosition(&world, player_position_top_left);

        WorldPosition player_position_top_right = next_player_position;
        player_position_top_right.TileRelative.X += 0.5f * tank_width;
        player_position_top_right.TileRelative.Y -= 0.5f * tank_height;
        player_position_top_right = NormalizeWorldPosition(&world, player_position_top_right);

        bool32 bottom_left_is_empty = IsWorldPointEmpty(&world, player_position_bottom_left);
        bool32 bottom_middle_is_emtpy = IsWorldPointEmpty(&world, next_player_position);
        bool32 bottom_right_is_empty = IsWorldPointEmpty(&world, player_position_bottom_right);
        bool32 top_left_is_empty = IsWorldPointEmpty(&world, player_position_top_left);
        bool32 top_right_is_empty = IsWorldPointEmpty(&world, player_position_top_right);

        bool32 collided = false;
        WorldPosition collision_position = {};
        if (!bottom_left_is_empty)
        {
            collision_position = player_position_bottom_left;
            collided = true;
        }
        if (!bottom_right_is_empty)
        {
            collision_position = player_position_bottom_right;
            collided = true;
        }
        if (!top_left_is_empty)
        {
            collision_position = player_position_top_left;
            collided = true;
        }
        if (!top_right_is_empty)
        {
            collision_position = player_position_top_right;
            collided = true;
        }


        if (collided && (collision_position.Tilemap.X == game_state->PlayerPosition.Tilemap.X)
            && (collision_position.Tilemap.Y == game_state->PlayerPosition.Tilemap.Y))
        {
            V2r r = { 0, 0 };
            if (collision_position.Tile.X < game_state->PlayerPosition.Tile.X)
                r = V2r { 1, 0 };
            if (collision_position.Tile.X > game_state->PlayerPosition.Tile.X)
                r = V2r { -1, 0 };
            if (collision_position.Tile.Y < game_state->PlayerPosition.Tile.Y)
                r = V2r { 0, 1 };
            if (collision_position.Tile.Y > game_state->PlayerPosition.Tile.Y)
                r = V2r { 0, -1 };

            game_state->PlayerVelocity -= 2 * r
                * DotProduct(game_state->PlayerVelocity, r);
        }

        if (bottom_left_is_empty && bottom_middle_is_emtpy && bottom_right_is_empty
            && top_left_is_empty && top_right_is_empty && !collided)
            game_state->PlayerPosition = next_player_position;
    }

    V2r player_position = world.Origin
        + game_state->PlayerPosition.Tile * world.TileSidePixels
        + game_state->PlayerPosition.TileRelative * world.GameUnits2Pixels;
    V2r player_left_top = player_position
        - (V2r{ tank_width, tank_height } * 0.5f) * world.GameUnits2Pixels;
    V2r player_right_bottom = player_position
        + (V2r{ tank_width, tank_height } * 0.5f) * world.GameUnits2Pixels;

    V3r collider_color = { 0, 1, 0 };
    DrawWireRectangle(display_buffer, player_left_top, player_right_bottom,
        collider_visual_width, collider_color);

    V2r tank_scale = V2rOne() * 0.25f;
    V2r player_center = player_left_top
        + (V2r{ tank_width, tank_height } * world.GameUnits2Pixels * 0.5f);
    DrawPngImage(display_buffer, &game_state->TankImage, player_left_top,
         V2r{ tank_width, tank_height } * world.GameUnits2Pixels);

    game_state->EnemyPosition = NormalizeWorldPosition(&world, game_state->EnemyPosition);
    V2r enemy_left_top = world.Origin
        + game_state->EnemyPosition.Tile * world.TileSidePixels
        + game_state->EnemyPosition.TileRelative * world.GameUnits2Pixels;
    V2r enemy_right_bottom = enemy_left_top
        + V2r{ tank_width, tank_height } * world.GameUnits2Pixels;
    DrawWireRectangle(display_buffer, enemy_left_top, enemy_right_bottom,
        collider_visual_width, collider_color);
    DrawPngImage(display_buffer, &game_state->TankImage, enemy_left_top,
        V2r{ tank_width, tank_height } * world.GameUnits2Pixels);

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
