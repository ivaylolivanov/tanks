#ifndef TANKS

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

Internal void UpdateAndRender(GameBackBuffer *display_buffer, int offset_blue,
                              int offset_green, GameSoundBuffer *sound_buffer,
                              int tone_hz);

#define TANKS
#endif
