#include <cstdint>
#ifndef TANKS

#include <math.h>
#include <cinttypes>

#define Internal       static
#define LocalPersist   static
#define GlobalVariable static

#define Pi32 3.14159265359f

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32   bool32;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef uintptr_t umm;
typedef intptr_t smm;

typedef float  real32;
typedef double real64;

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

struct ReadFileResult
{
    uint32 Size;
    void* Content;
};

ReadFileResult ReadFileStub(char* filename)
{
    ReadFileResult result = {};

    result.Size = 0;
    result.Content = 0;

    return result;
}
typedef ReadFileResult FPtrReadFile(char* filename);

bool32 WriteFileStub(char* filename, uint32  memory_size, void* memory)
{
    return 0;
}
typedef bool32 FPtrWriteFile(char* filename, uint32 memory_size, void* memory);

void FreeFileMemoryStub(void *memory) {}
typedef void FPtrFreeFileMemory(void* memory);

struct ButtonState
{
    int HalfTransitions;
    bool32 EndedDown;
};

struct ControllerState
{
    bool32 IsConnected;
    bool32 IsAnalog;

    real32 LeftStickAverageX;
    real32 LeftStickAverageY;

    union
    {
        ButtonState Buttons[12];
        struct
        {
            ButtonState ActionUp;
            ButtonState ActionDown;
            ButtonState ActionLeft;
            ButtonState ActionRight;

            ButtonState MoveUp;
            ButtonState MoveDown;
            ButtonState MoveLeft;
            ButtonState MoveRight;

            ButtonState ShoulderLeft;
            ButtonState ShoulderRight;

            ButtonState Back;
            ButtonState Start;

            ButtonState MAX;
        };
    };
};

struct GameMemory
{
    bool32 IsInitialized;

    uint64 PermanentStorageSize;
    void*  PermanentStorage;

    uint64 TransientStorageSize;
    void*  TransientStorage;

    FPtrWriteFile      *WriteFile;
    FPtrReadFile       *ReadFile;
    FPtrFreeFileMemory *FreeFileMemory;
};

struct GameInput
{
    ControllerState Controllers[4];
};

inline ControllerState* GetController(GameInput* input, int unsigned controller_index)
{
    Assert(controller_index < ArrayCount(input->Controllers));

    ControllerState* result = &input->Controllers[controller_index];

    return result;
}

struct GameBackBuffer
{
    void* Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
};

struct GameSoundBuffer
{
    int SamplesPerSecond;
    int SamplesCount;
    int16 *Samples;
};

struct GameState
{
    int ToneHz;

    int PlayerX;
    int PlayerY;

    real32 SineStep;
};

typedef void FPtrUpdateAndRender(GameMemory *memory, GameInput *input,
    GameBackBuffer *display_buffer);
void UpdateAndRenderStub(GameMemory *memory, GameInput *input,
    GameBackBuffer *display_buffer) { }

typedef void FPtrGetSoundSamples(GameMemory *memory,
    GameSoundBuffer *sound_buffer);
void GetSoundSamplesStub(GameMemory *memory, GameSoundBuffer *sound_buffer) {}

#define TANKS
#endif
