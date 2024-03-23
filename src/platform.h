#if !defined PLATFORM

#include <math.h>
#include <cinttypes>

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

struct ThreadContext
{
    int PlaceHolder;
};

struct ReadFileResult
{
    uint32 Size;
    void* Content;
};

ReadFileResult ReadFileStub(ThreadContext *thread, char* filename)
{
    ReadFileResult result = {};

    result.Size = 0;
    result.Content = 0;

    return result;
}
typedef ReadFileResult FPtrReadFile(ThreadContext *thread, char* filename);

bool32 WriteFileStub(ThreadContext *thread, char* filename, uint32  memory_size,
    void* memory)
{
    return 0;
}
typedef bool32 FPtrWriteFile(ThreadContext *thread, char* filename,
    uint32 memory_size, void* memory);

void FreeFileMemoryStub(ThreadContext *thread, void *memory) {}
typedef void FPtrFreeFileMemory(ThreadContext *thread, void* memory);

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
    ButtonState MouseButtons[5];
    int32 MouseX, MouseY, MouseZ;

    real32 DeltaTime;

    ControllerState Controllers[4];
};

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

typedef void FPtrUpdateAndRender(ThreadContext* thread, GameMemory *memory, GameInput *input,
    GameBackBuffer *display_buffer);

typedef void FPtrGetSoundSamples(ThreadContext* thread, GameMemory *memory,
    GameSoundBuffer *sound_buffer);

#define PLATFORM
#endif
