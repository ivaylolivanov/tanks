#include <dsound.h>

LPDIRECTSOUNDBUFFER SOUND_BUFFER;

HRESULT WINAPI DirectSoundCreateStub(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
{
    return 0;
}

typedef HRESULT WINAPI FPtrDirectSoundCreate
(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter);
#define DirectSoundCreate FPtrDirectSoundCreate

Internal void InitDirectSound(HWND window, int32 samples_per_second, int32 buffer_size)
{
    HMODULE direct_sound_library = LoadLibrary("dsound.dll");
    if (!direct_sound_library) return;

    DirectSoundCreate *direct_sound_create = (DirectSoundCreate *)
        GetProcAddress(direct_sound_library, "DirectSoundCreate");

    LPDIRECTSOUND direct_sound;
    if (!direct_sound_create
        || FAILED(direct_sound_create(0, &direct_sound, 0)))
        return;

    WAVEFORMATEX wave_format = {};
    wave_format.wFormatTag = WAVE_FORMAT_PCM;
    wave_format.nChannels = 2;
    wave_format.nSamplesPerSec = samples_per_second;
    wave_format.wBitsPerSample = 16;
    wave_format.nBlockAlign = (wave_format.nChannels * wave_format.wBitsPerSample) / 8;
    wave_format.nAvgBytesPerSec = wave_format.nSamplesPerSec * wave_format.nBlockAlign;
    wave_format.cbSize = 0;

    if (FAILED(direct_sound->SetCooperativeLevel(window, DSSCL_PRIORITY)))
        return;

    DSBUFFERDESC buffer_description = {};
    buffer_description.dwSize = sizeof(buffer_description);
    buffer_description.dwFlags = DSBCAPS_PRIMARYBUFFER;

    LPDIRECTSOUNDBUFFER primary_buffer;
    if (FAILED(
            direct_sound->CreateSoundBuffer(
                &buffer_description, &primary_buffer, 0)))
        return;

    HRESULT set_format_status = primary_buffer->SetFormat(&wave_format);
    if (SUCCEEDED(set_format_status))
        OutputDebugStringA("Primary buffer format was set.\n");

    DSBUFFERDESC secondary_buffer_description = {};
    secondary_buffer_description.dwSize = sizeof(secondary_buffer_description);
    secondary_buffer_description.dwFlags = 0;
    secondary_buffer_description.dwBufferBytes = buffer_size;
    secondary_buffer_description.lpwfxFormat = &wave_format;

    set_format_status = direct_sound->CreateSoundBuffer(
        &secondary_buffer_description, &SOUND_BUFFER, 0);
    if (SUCCEEDED(set_format_status))
        OutputDebugStringA("Secondary buffer format was set.\n");
}
