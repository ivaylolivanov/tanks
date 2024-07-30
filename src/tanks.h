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

struct Position
{
    V2i Tile;
    V2r Offset;
};

struct Tilemap
{
    V2i Size;
    uint32 *Tiles;

    real32 TileSidePixels;
    real32 TileSideGameUnits;
    real32 GameUnits2Pixels;
};

struct World
{
    V2r Origin;

    Tilemap* Tilemaps;
    uint32 TilemapIndex;
};

struct Entity
{
    bool32 Enabled;
    Position Position;
    V2r Velocity;
    V2r Size;
    // TODO: Add rotaition ?
};

struct GameState
{
    MemorySection GameMemory;
    World* World;

    uint32 EntityIndexMainCamera;
    uint32 EntityIndexCameraTarget;
    // TODO: tanks.h::GameState.EntityIndicesPlayers size HAS TO BE
    // the same as platform.h::GameInput.Controllers. Expose
    // visibility? (Global constant?)
    uint32 EntityIndexPlayers[4];

    uint32 EntitiesCount;
    Entity Entities[256];

    Image TankImage;

    int ToneHz;
    real32 SineStep;
};

#define TANKS
#endif
