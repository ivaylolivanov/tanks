#include <cstdint>
#ifndef TANKS

#include "platform.h"

#define Internal       static
#define LocalPersist   static
#define GlobalVariable static

#define Pi32 3.14159265359f

#define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

#if ASSERT_ENABLED
#define Assert(expression) if (!(expression)) {*(int*)0=0;}
#else
#define Assert(expression)
#endif

#define KILOBYTES(value) ((value)*1024LL)
#define MEGABYTES(value) (KILOBYTES(value)*1024LL)
#define GIGABYTES(value) (MEGABYTES(value)*1024LL)
#define TERABYTES(value) (GIGABYTES(value)*1024LL)

inline uint32 TruncateUInt64(uint64 Value)
{
    Assert(Value <= 0xFFFFFFFF);
    uint32 result = (uint32)Value;
    return(result);
}

inline ControllerState* GetController(GameInput* input, int unsigned controller_index)
{
    Assert(controller_index < ArrayCount(input->Controllers));

    ControllerState* result = &input->Controllers[controller_index];

    return result;
}


struct RawPosition
{
    int32 TilemapX;
    int32 TilemapY;

    real32 X;
    real32 Y;
};

struct WorldPosition
{
    int32 TilemapX;
    int32 TilemapY;

    int32 TileX;
    int32 TileY;

    real32 TileRelativeX;
    real32 TileRelativeY;
};

struct Tilemap
{
    uint32 *Tiles;
};

struct World
{
    int32 WorldWidth;
    int32 WorldHeight;

    int32 TilemapWidth;
    int32 TilemapHeight;

    real32 TileSideGameUnits;
    real32 TileSidePixels;

    real32 UpperLeftX;
    real32 UpperLeftY;

    Tilemap *Tilemaps;
};

struct GameState
{
    int ToneHz;
    real32 SineStep;

    WorldPosition PlayerPosition;
};

#define TANKS
#endif
