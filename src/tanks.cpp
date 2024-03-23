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

inline WorldPosition GetWorldPosition(World* world, RawPosition position)
{
    WorldPosition result;

    result.TilemapX = position.TilemapX;
    result.TilemapY = position.TilemapY;

    real32 x = position.X - world->UpperLeftX;
    real32 y = position.Y - world->UpperLeftY;
    result.TileX = FloorReal32ToInt32(x / world->TileWidth);
    result.TileY = FloorReal32ToInt32(y / world->TileHeight);

    result.TileRelativeX = x - result.TileX * world->TileWidth;
    result.TileRelativeY = y - result.TileY * world->TileHeight;

    if (result.TileX < 0)
    {
        result.TileX = world->TilemapWidth + result.TileX;
        --result.TilemapX;
    }

    if (result.TileY < 0)
    {
        result.TileY = world->TilemapHeight + result.TileY;
        --result.TilemapY;
    }

    if (result.TileX >= world->TilemapWidth)
    {
        result.TileX = world->TilemapWidth - result.TileX;
        ++result.TilemapX;
    }

    if (result.TileY >= world->TilemapHeight)
    {
        result.TileY = world->TilemapHeight - result.TileY;
        ++result.TilemapY;
    }

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

Internal bool32 IsWorldPointEmpty(World* world, RawPosition position)
{
    bool32 result = false;

    WorldPosition world_position = GetWorldPosition(world, position);
    Tilemap* tilemap = GetTilemap(world, world_position.TilemapX,
        world_position.TilemapY);
    if (!tilemap) return result;

    result = IsTilemapPointEmpty(world, tilemap, world_position.TileX, world_position.TileY);
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
    world.TileWidth = 60;
    world.TileHeight = 60;
    world.Tilemaps = (Tilemap*)tilemaps;

    real32 player_r = 0.45f;
    real32 player_g = 0.15f;
    real32 player_b = 0.65f;
    real32 player_width = 0.65f * world.TileWidth;
    real32 player_height = world.TileHeight;

    GameState* game_state = (GameState *)memory->PermanentStorage;
    if (!memory->IsInitialized)
    {
        game_state->PlayerX = 250;
        game_state->PlayerY = 250;

        game_state->ToneHz = 400;
        memory->IsInitialized = true;
    }
    Tilemap* tilemap = GetTilemap(&world, game_state->PlayerTilemapX,
        game_state->PlayerTilemapY);

    for (int8 controller_index = 0; controller_index < ArrayCount(input->Controllers); ++controller_index)
    {
        ControllerState *controller = GetController(input, controller_index);
        if (controller->IsAnalog)
        {
            game_state->PlayerX += (int)(4.0f * controller->LeftStickAverageX);
            game_state->PlayerY -= (int)(4.0f * controller->LeftStickAverageY);
        }
        else
        {
            real32 x = 0;
            real32 y = 0;
            if (controller->MoveLeft.EndedDown)  x -= 1;
            if (controller->MoveRight.EndedDown) x += 1;
            if (controller->MoveUp.EndedDown)    y -= 1;
            if (controller->MoveDown.EndedDown)  y += 1;

            real32 player_speed = 128.0f;
            x *= player_speed;
            y *= player_speed;

            real32 new_player_x = game_state->PlayerX + x * input->DeltaTime;
            real32 new_player_y = game_state->PlayerY + y * input->DeltaTime;
            RawPosition player_position = {
                game_state->PlayerTilemapX,
                game_state->PlayerTilemapY,
                new_player_x,
                new_player_y };
            RawPosition player_position_bottom_left = player_position;
            player_position_bottom_left.X -= 0.5f * player_width;
            RawPosition player_position_bottom_right = player_position;
            player_position_bottom_right.X += 0.5f * player_width;
            RawPosition player_position_top_left = player_position_bottom_left;
            player_position_top_left.Y -= player_height;
            RawPosition player_position_top_right = player_position_bottom_right;
            player_position_top_right.Y -= player_height;

            bool32 bottom_left_is_empty = IsWorldPointEmpty(&world, player_position_bottom_left);
            bool32 bottom_middle_is_emtpy = IsWorldPointEmpty(&world, player_position);
            bool32 bottom_right_is_empty = IsWorldPointEmpty(&world, player_position_bottom_right);
            bool32 top_left_is_empty = IsWorldPointEmpty(&world, player_position_top_left);
            bool32 top_right_is_empty = IsWorldPointEmpty(&world, player_position_top_right);
            if (bottom_left_is_empty && bottom_middle_is_emtpy && bottom_right_is_empty
                && top_left_is_empty && top_right_is_empty)
            {
                WorldPosition player_position_world = GetWorldPosition(&world,
                    player_position);

                game_state->PlayerTilemapX = player_position_world.TilemapX;
                game_state->PlayerTilemapY = player_position_world.TilemapY;
                game_state->PlayerX = world.UpperLeftX
                    + world.TileWidth * player_position_world.TileX
                    + player_position_world.TileRelativeX;
                game_state->PlayerY = world.UpperLeftY
                    + world.TileHeight * player_position_world.TileY
                    + player_position_world.TileRelativeY;
            }
        }
    }

    for (int row = 0; row < world.TilemapHeight; ++row)
    {
        for (int column = 0; column < world.TilemapWidth; ++column)
        {
            uint32 tile_id = GetTileValue(&world, tilemap, column, row);
            real32 gray = 0.5f;
            if (tile_id == 1)
                gray = 1.0f;

            real32 min_x = world.UpperLeftX + ((real32)column) * world.TileWidth;
            real32 min_y = world.UpperLeftY + ((real32)row) * world.TileHeight;
            real32 max_x = min_x + world.TileWidth;
            real32 max_y = min_y + world.TileHeight;
            DrawRectangle(display_buffer,
            min_x, min_y,
            max_x, max_y,
            gray, gray, gray);
        }
    }

    real32 player_left = game_state->PlayerX - 0.5f * player_width;
    real32 player_top = game_state->PlayerY - player_height;

    DrawRectangle(display_buffer,
        player_left, player_top,
        player_left + player_width, player_top + player_height,
        player_r, player_g, player_b);
}

extern "C" void GetSoundSamples(ThreadContext* thread, GameMemory* memory,
    GameSoundBuffer *sound_buffer)
{
    GameState* game_state = (GameState*)memory->PermanentStorage;

    bool32 is_sound_unmuted = false;
    if (is_sound_unmuted) OutputSound(game_state, sound_buffer);
}
