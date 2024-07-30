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

struct MemorySection
{
    memoryIndex Size;
    uint8* Base;
    memoryIndex Used;
};

Internal void InitializeMemory(MemorySection* section, memoryIndex size,
    uint8 *base)
{
    section->Size = size;
    section->Used = 0;
    section->Base = base;
}

#define AllocateStruct(section, type) (type*)AllocateSize(section, sizeof(type))
#define AllocateArray(section, count, type) (type*)AllocateSize(section, count * sizeof(type))
void* AllocateSize(MemorySection* section, memoryIndex size)
{
    Assert((section->Used + size) <= section->Size);
    void* result = section->Base + section->Used;
    section->Used += size;

    return result;
}

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
    MemorySection GameMemory;
    World* World;

    Image TankImage;

    int ToneHz;
    real32 SineStep;

    WorldPosition CameraPosition;
    WorldPosition PlayerPosition;
    V2r PlayerVelocity;

    WorldPosition EnemyPosition;
};

#define TANKS
#endif
