#ifndef WIN_PLATFORM

struct BackBuffer
{
    // Pixel is 32-bit
    // Memory order BB GG RR XX
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
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
    DWORD  BufferSize;
    DWORD  SafetyBytes;
    real32 SineCurrent;
    int32  LatencySampleCount;
};

struct TimeMarker
{
    DWORD OutputPlayCursor;
    DWORD OutputWriteCursor;
    DWORD OutputLocation;
    DWORD OutputByteCount;
    DWORD ExpectedFlipPlayCursor;

    DWORD FlipPlayCursor;
    DWORD FlipWriteCursor;
};

struct FileData
{
    uint32 Size;
    void *Content;
};

void FreeFileMemory(void* memory);
ReadFileResult ReadFile(char* filename);
bool32 WriteFile(char* filename, void *memory, uint32 size);

struct GameCode
{
    HMODULE Dll;
    FILETIME DllLastEditTime;

    FPtrUpdateAndRender *UpdateAndRender;
    FPtrGetSoundSamples *GetSoundSamples;

    bool32 IsValid;
};

struct WindowsState
{
    uint64 TotalSize;
    void* GameMemory;

    char  ExeFilepath[MAX_PATH];
    char* ExeBasename;

    HANDLE RecordingHandle;
    int InputRecordingIndex;

    HANDLE PlaybackHandle;
    int InputPlaybackIndex;
};

#define WIN_PLATFORM
#endif
