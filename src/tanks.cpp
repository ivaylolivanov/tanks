#include "tanks.h"
#include "intrinsics.h"

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

    uint8 result_red   = (uint8)(foreground_red   * foreground_alpha_real + background_red   * (1 - foreground_alpha_real));
    uint8 result_green = (uint8)(foreground_green * foreground_alpha_real + background_green * (1 - foreground_alpha_real));
    uint8 result_blue  = (uint8)(foreground_blue  * foreground_alpha_real + background_blue  * (1 - foreground_alpha_real));

    result = (foreground_alpha << 24)
        | (result_red << 16)
        | (result_green << 8)
        | result_blue;
    return result;
}

Internal void DrawPngImage(GameBackBuffer* buffer, Image* image, real32 originX, real32 originY, real32 scale_x, real32 scale_y)
{
    real32 scaled_real_width  = image->Width * scale_x;
    real32 scaled_real_height = image->Height * scale_y;
    int32 scaled_width  = RoundReal32ToInt32(scaled_real_width);
    int32 scaled_height = RoundReal32ToInt32(scaled_real_height);

    int32 min_x = RoundReal32ToInt32(originX - (scaled_width  / 2));
    int32 min_y = RoundReal32ToInt32(originY - (scaled_height / 2));
    int32 max_x = RoundReal32ToInt32(originX + (scaled_width  / 2));
    int32 max_y = RoundReal32ToInt32(originY + (scaled_height / 2));

    if (min_x < 0)
        min_x = 0;

    if (min_y < 0)
        min_y = 0;

    if (max_x > buffer->Width)
        max_x = buffer->Width;

    if (max_y > buffer->Height)
        max_y = buffer->Height;

    uint8* row_buffer = ((uint8*)buffer->Memory
        + min_x * buffer->BytesPerPixel
        + min_y * buffer->Pitch);

    for (int y = min_y; y < max_y; ++y)
    {
        uint32 unscaled_y = (int32)((y - min_y) / scale_y);

        uint32* pixel_buffer = (uint32*)row_buffer;
        for (int x = min_x; x < max_x; ++x)
        {
            uint32 unscaled_x = (int32)((x - min_x) / scale_x);
            uint32* pixel_image = (uint32*)(image->Pixels)
                + (unscaled_y * image->Width + unscaled_x);

            uint32 blend_color = BlendColors(*pixel_buffer, *pixel_image);
            *pixel_buffer++ = blend_color;
        }

        row_buffer += buffer->Pitch;
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

    NormalizeWorldCoordinates(world, world->TilemapWidth, &result.TilemapX,
        &result.TileX, &result.TileRelativeX);
    NormalizeWorldCoordinates(world, world->TilemapHeight, &result.TilemapY,
        &result.TileY, &result.TileRelativeY);

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

    Tilemap* tilemap = GetTilemap(world, position.TilemapX, position.TilemapY);
    if (!tilemap) return result;

    result = IsTilemapPointEmpty(world, tilemap, position.TileX, position.TileY);
    return result;
}

Internal void DrawRectangle(GameBackBuffer *buffer, real32 real_min_x,
    real32 real_min_y, real32 real_max_x, real32 real_max_y, real32 r, real32 g,
    real32 b)
{
    int32 min_x = RoundReal32ToInt32(real_min_x);
    int32 min_y = RoundReal32ToInt32(real_min_y);
    int32 max_x = RoundReal32ToInt32(real_max_x);
    int32 max_y = RoundReal32ToInt32(real_max_y);

    if (min_x < 0)             min_x = 0;
    if (min_x > buffer->Width) min_x = buffer->Width;

    if (min_y < 0)              min_y = 0;
    if (min_y > buffer->Height) min_y = buffer->Height;

    if (max_x < 0)             max_x = 0;
    if (max_x > buffer->Width) max_x = buffer->Width;

    if (max_y < 0)              max_y = 0;
    if (max_y > buffer->Height) max_y = buffer->Height;

    uint32 color = ((RoundReal32ToInt32(r * 255.0f) << 16)
        | (RoundReal32ToInt32(g * 255.0f) << 8)
        | (RoundReal32ToInt32(b * 255.0f) << 0));

    uint8* row = ((uint8 *) buffer->Memory
        + min_x * buffer->BytesPerPixel
        + min_y * buffer->Pitch);
    for (int y = min_y; y < max_y; ++y)
    {
        uint32 *pixel = (uint32 *)row;
        for (int x = min_x; x < max_x; ++x)
            *pixel++ = color;

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
    world.UpperLeftX = 0;
    world.UpperLeftY = 0;
    world.WorldWidth = 2;
    world.WorldHeight = 2;
    world.TilemapWidth = TILEMAP_WIDTH;
    world.TilemapHeight = TILEMAP_HEIGHT;
    world.TileSideGameUnits = 1.4f;
    world.TileSidePixels = 60;
    world.GameUnits2Pixels = (real32)world.TileSidePixels
        / (real32)world.TileSideGameUnits;
    world.Tilemaps = (Tilemap*)tilemaps;

    real32 player_r = 0.45f;
    real32 player_g = 0.15f;
    real32 player_b = 0.65f;
    real32 player_height = 1.4f;
    real32 player_width = 0.65f * player_height;
    real32 player_speed = 8.0f;

    GameState* game_state = (GameState *)memory->PermanentStorage;
    if (!memory->IsInitialized)
    {
        char* tank_png_relative_path = "tank.png";
        ReadFileResult raw_png = memory->ReadFile(thread, tank_png_relative_path);
        Stream raw_png_stream = {};
        raw_png_stream.Size = raw_png.Size;
        raw_png_stream.Content = raw_png.Content;

        game_state->PlayerImage = ParsePNG(raw_png_stream);

        game_state->PlayerPosition.TilemapX = 0;
        game_state->PlayerPosition.TilemapY = 0;
        game_state->PlayerPosition.TileX = 10;
        game_state->PlayerPosition.TileY = 6;
        game_state->PlayerPosition.TileRelativeX = 5.0f;
        game_state->PlayerPosition.TileRelativeY = 5.0f;

        game_state->ToneHz = 400;
        memory->IsInitialized = true;
    }
    Tilemap* tilemap = GetTilemap(&world, game_state->PlayerPosition.TilemapX,
        game_state->PlayerPosition.TilemapY);

    for (int8 controller_index = 0; controller_index < ArrayCount(input->Controllers); ++controller_index)
    {
        real32 x = 0;
        real32 y = 0;
        ControllerState *controller = GetController(input, controller_index);
        if (controller->IsAnalog)
        {
            x += (int)(4.0f * controller->LeftStickAverageX);
            y -= (int)(4.0f * controller->LeftStickAverageY);
        }
        else
        {
            if (controller->MoveLeft.EndedDown)  x -= 1;
            if (controller->MoveRight.EndedDown) x += 1;
            if (controller->MoveUp.EndedDown)    y -= 1;
            if (controller->MoveDown.EndedDown)  y += 1;
        }

        x *= player_speed * input->DeltaTime;
        y *= player_speed * input->DeltaTime;

        WorldPosition next_player_position = game_state->PlayerPosition;
        next_player_position.TileRelativeX += x;
        next_player_position.TileRelativeY += y;
        next_player_position = NormalizeWorldPosition(&world,
            next_player_position);

        WorldPosition player_position_bottom_left = next_player_position;
        player_position_bottom_left.TileRelativeX -= 0.5f * player_width;
        player_position_bottom_left = NormalizeWorldPosition(&world,
            player_position_bottom_left);
        WorldPosition player_position_bottom_right = next_player_position;
        player_position_bottom_right.TileRelativeX += 0.5f * player_width;
        player_position_bottom_right = NormalizeWorldPosition(&world,
            player_position_bottom_right);
        WorldPosition player_position_top_left = player_position_bottom_left;
        player_position_top_left.TileRelativeY -= player_height;
        player_position_top_left = NormalizeWorldPosition(&world, player_position_top_left);
        WorldPosition player_position_top_right = player_position_bottom_right;
        player_position_top_right.TileRelativeY -= player_height;
        player_position_top_right = NormalizeWorldPosition(&world, player_position_top_right);

        bool32 bottom_left_is_empty = IsWorldPointEmpty(&world, player_position_bottom_left);
        bool32 bottom_middle_is_emtpy = IsWorldPointEmpty(&world, next_player_position);
        bool32 bottom_right_is_empty = IsWorldPointEmpty(&world, player_position_bottom_right);
        bool32 top_left_is_empty = IsWorldPointEmpty(&world, player_position_top_left);
        bool32 top_right_is_empty = IsWorldPointEmpty(&world, player_position_top_right);
        if (bottom_left_is_empty && bottom_middle_is_emtpy && bottom_right_is_empty
            && top_left_is_empty && top_right_is_empty)
            game_state->PlayerPosition = next_player_position;
    }

    for (int row = 0; row < world.TilemapHeight; ++row)
    {
        for (int column = 0; column < world.TilemapWidth; ++column)
        {
            uint32 tile_id = GetTileValue(&world, tilemap, column, row);
            real32 gray = 0.5f;
            if (tile_id == 1)
                gray = 1.0f;

            if (column == game_state->PlayerPosition.TileX
                && row == game_state->PlayerPosition.TileY)
                gray = 0.4f;

            real32 min_x = world.UpperLeftX + ((real32)column) * world.TileSidePixels;
            real32 min_y = world.UpperLeftY + ((real32)row) * world.TileSidePixels;
            real32 max_x = min_x + world.TileSidePixels;
            real32 max_y = min_y + world.TileSidePixels;
            DrawRectangle(display_buffer,
                min_x, min_y,
                max_x, max_y,
                gray, gray, gray);
        }
    }

    real32 player_left = world.UpperLeftX
        + world.TileSidePixels * game_state->PlayerPosition.TileX
        + game_state->PlayerPosition.TileRelativeX * world.GameUnits2Pixels
        - 0.5f * player_width * world.GameUnits2Pixels;
    real32 player_top = world.UpperLeftY
        + world.TileSidePixels * game_state->PlayerPosition.TileY
        + game_state->PlayerPosition.TileRelativeY * world.GameUnits2Pixels
        - player_height * world.GameUnits2Pixels;

    DrawRectangle(display_buffer,
        player_left, player_top,
        player_left + player_width * world.GameUnits2Pixels,
        player_top + player_height * world.GameUnits2Pixels,
        player_r, player_g, player_b);

    real32 player_center_x = player_left
        + (player_width * world.GameUnits2Pixels) / 2;
    real32 player_center_y = player_top
        + (player_height * world.GameUnits2Pixels) / 2;
    DrawPngImage(display_buffer, &game_state->PlayerImage, player_center_x,
        player_center_y, 0.25f, 0.25f);
}

extern "C" void GetSoundSamples(ThreadContext* thread, GameMemory* memory,
    GameSoundBuffer *sound_buffer)
{
    GameState* game_state = (GameState*)memory->PermanentStorage;

    bool32 is_sound_unmuted = false;
    if (is_sound_unmuted)
        OutputSound(game_state, sound_buffer);
}
