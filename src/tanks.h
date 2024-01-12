#ifndef TANKS

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
};

struct GameInput
{
    ControllerState Controllers[4];
};

struct GameBackBuffer
{
    void* Memory;
    int Width;
    int Height;
    int Pitch;
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
    int OffsetGreen;
    int OffsetBlue;
};

Internal void UpdateAndRender(GameMemory *memory, GameInput *input, GameBackBuffer *display_buffer);
Internal void GetSoundSamples(GameMemory *memory, GameSoundBuffer *sound_buffer);

#define TANKS
#endif
