#ifndef TANKS

#define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

struct ButtonState
{
    int HalfTransitions;
    bool32 EndedDown;
};

struct ControllerState
{
    bool32 IsAnalog;

    real32 StartX;
    real32 StartY;

    real32 MinX;
    real32 MinY;

    real32 MaxX;
    real32 MaxY;

    real32 EndX;
    real32 EndY;

    union
    {
        ButtonState Buttons[12];
        struct
        {
            ButtonState ActionUp;
            ButtonState ActionDown;
            ButtonState ActionLeft;
            ButtonState ActionRight;

            ButtonState Up;
            ButtonState Down;
            ButtonState Left;
            ButtonState Right;

            ButtonState ShoulderLeft;
            ButtonState ShoulderRight;

            ButtonState Back;
            ButtonState Start;
        };
    };
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

Internal void UpdateAndRender(GameInput *input, GameBackBuffer *display_buffer,
                              GameSoundBuffer *sound_buffer);

#define TANKS
#endif
