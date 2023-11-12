#include <cinttypes>

// Better send the intetion of the static keyword to the other developers
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

typedef float  real32;
typedef double real64;

struct BackBuffer
{
    // Pixel is 32-bit
    // Memory order BB GG RR XX
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
};

struct WindowDimension
{
    int Width;
    int Height;
};

struct SoundOutput
{
    int32  SamplesPerSecond;
    uint32 RunningSampleIndex;
    int32  BytesPerSample;
    int32  BufferSize;
    real32 SineCurrent;
    int32  LatencySampleCount;
};

struct FileData
{
    uint32 Size;
    void *Content;
};

Internal void FreeFileMemory(void* memory);
Internal FileData ReadFile(char* filename);
Internal bool32 WriteFile(char* filename, void *memory, uint32 size);
