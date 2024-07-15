#ifndef TANKS

#include "platform.h"
#include "png-parser/png-parser.cpp"
#include "math/math.h"
#include "math/vectors.h"
#include "intrinsics.h"

#define Pi32 3.14159265359f

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

struct WorldPosition
{
    V2i Tilemap;
    V2i Tile;
    V2r TileRelative;
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
    real32 GameUnits2Pixels;

    V2r Origin;

    Tilemap *Tilemaps;
};

struct GameState
{
    Image TankImage;

    int ToneHz;
    real32 SineStep;

    WorldPosition CameraPosition;
    WorldPosition PlayerPosition;
    WorldPosition EnemyPosition;
};

#define TANKS
#endif
