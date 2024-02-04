#if WIN32_DEBUG_SOUND

Internal void DrawVertical(BackBuffer* buffer, int x, int top, int bottom, uint32 color)
{
    if (top < 0) top = 0;
    if (bottom > buffer->Height) bottom = buffer->Height;

    if (x < 0 || x > buffer->Width) return;

    uint8* pixel = ((uint8*)buffer->Memory +
        x * buffer->BytesPerPixel +
        top * buffer->Pitch);

    for (int y = top; y < bottom; ++y)
    {
        *(uint32 *)pixel = color;
        pixel += buffer->Pitch;
    }
}

inline void DrawSoundBufferMarker(BackBuffer* buffer, SoundOutput* sound_output, real32 c, int pad_x, int top, int bottom, DWORD value, uint32 color)
{
    real32 x_real32 = (c * (real32)value);
    int x = pad_x + (int)x_real32;
    DrawVertical(buffer, x, top, bottom, color);
}

Internal void DebugSyncDisplay(BackBuffer* buffer, int markers_count, int current_marker_index, TimeMarker* markers, SoundOutput* sound_output, real32 target_seconds_per_frame)
{
    int pad_x = 16;
    int pad_y = 16;

    int line_height = 64;

    real32 c = (real32)(buffer->Width - 2 * pad_x) / (real32)sound_output->BufferSize;
    for(int marker_index = 0; marker_index < markers_count; ++marker_index)
    {
        TimeMarker* marker = &markers[marker_index];

        Assert(marker->OutputPlayCursor  < sound_output->BufferSize);
        Assert(marker->OutputWriteCursor < sound_output->BufferSize);
        Assert(marker->OutputLocation    < sound_output->BufferSize);
        Assert(marker->OutputByteCount   < sound_output->BufferSize);
        Assert(marker->FlipPlayCursor    < sound_output->BufferSize);
        Assert(marker->FlipWriteCursor   < sound_output->BufferSize);

        DWORD play_color = 0xFFFFFFFF;
        DWORD write_color = 0xFFFF0000;
        DWORD expected_flip_color = 0xFFFFFF00;
        DWORD play_window_color = 0xFFFF00FF;

        int top = pad_y;
        int bottom = pad_y + line_height;
        if(marker_index == current_marker_index)
        {
            top += line_height + pad_y;
            bottom += line_height + pad_y;

            int first_top = top;

            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputPlayCursor, play_color);
            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputWriteCursor, write_color);

            top += line_height + pad_y;
            bottom += line_height +pad_y;

            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputLocation, play_color);
            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->OutputLocation + marker->OutputByteCount, write_color);

            top += line_height + pad_y;
            bottom += line_height + pad_y;

            DrawSoundBufferMarker(buffer, sound_output, c, pad_x, first_top, bottom, marker->ExpectedFlipPlayCursor, expected_flip_color);
        }

        DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->FlipPlayCursor, play_color);
        DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->FlipPlayCursor + 480 * sound_output->BytesPerSample, play_window_color);
        DrawSoundBufferMarker(buffer, sound_output, c, pad_x, top, bottom, marker->FlipWriteCursor, write_color);
    }
}

#endif

Internal void ClearSoundBuffer(SoundOutput *sound_output)
{
    VOID *region1;
    DWORD region1_size;
    VOID *region2;
    DWORD region2_size;

    HRESULT buffer_lock_result = SOUND_BUFFER->Lock(
        0, sound_output->BufferSize,
        &region1, &region1_size,
        &region2, &region2_size,
        0);
    if (FAILED(buffer_lock_result))
        return;

    uint8 *destination_sample = (uint8 *)region1;
    for (DWORD byte_index = 0; byte_index < region1_size; ++byte_index)
        *destination_sample++ = 0;

    destination_sample = (uint8 *)region2;
    for (DWORD byte_index = 0; byte_index < region2_size; ++byte_index)
        *destination_sample++ = 0;

    SOUND_BUFFER->Unlock(region1, region1_size, region2, region2_size);
}

Internal void FillSoundBuffer(SoundOutput *sound_output, DWORD byte_to_lock,
    DWORD bytes_to_write, GameSoundBuffer *game_sound_buffer)
{
    VOID *region1;
    DWORD region1_size;
    VOID *region2;
    DWORD region2_size;

    HRESULT buffer_lock_result = SOUND_BUFFER->Lock(
        byte_to_lock, bytes_to_write,
        &region1, &region1_size,
        &region2, &region2_size,
        0);
    if (FAILED(buffer_lock_result)) return;

    int16 *source_sample = game_sound_buffer->Samples;

    DWORD region1_samples = region1_size / sound_output->BytesPerSample;
    int16 *destination_sample = (int16 *)region1;
    for (DWORD sample_index = 0; sample_index < region1_samples; ++sample_index)
    {
        *destination_sample++ = *source_sample++;
        *destination_sample++ = *source_sample++;

        ++sound_output->RunningSampleIndex;
    }

    DWORD region2_samples = region2_size / sound_output->BytesPerSample;
    destination_sample = (int16 *)region2;
    for (DWORD sample_index = 0; sample_index < region2_samples; ++sample_index)
    {
        *destination_sample++ = *source_sample++;
        *destination_sample++ = *source_sample++;

        ++sound_output->RunningSampleIndex;
    }

    SOUND_BUFFER->Unlock(region1, region1_size, region2, region2_size);
}

#if WIN32_DEBUG

Internal void PrintSoundDebugInfo(TimeMarker* marker, SoundOutput* sound_output,
    DWORD target_cursor)
{
    LocalPersist DWORD audio_latency_bytes = 0;
    LocalPersist real32 audio_latency_seconds = 0;

    DWORD unwrapped_cursor = marker->OutputWriteCursor;
    if (unwrapped_cursor < marker->OutputPlayCursor)
        unwrapped_cursor += sound_output->BufferSize;

    audio_latency_bytes = unwrapped_cursor - marker->OutputPlayCursor;
    audio_latency_seconds = ((real32)audio_latency_bytes
        / (real32)sound_output->BytesPerSample)
        / sound_output->SamplesPerSecond;

    char text_buffer[256];
    _snprintf_s(
        text_buffer,
        sizeof(text_buffer),
        "LPC: %u BTL: %u TC: %u BTW: %u - PC: %u WC: %u DELTA: %u (%fs)\n",
        LAST_PLAY_CURSOR, marker->OutputLocation, target_cursor,
        marker->OutputByteCount, marker->OutputPlayCursor,
        marker->OutputWriteCursor, audio_latency_bytes,
        audio_latency_seconds);
    OutputDebugString(text_buffer);
}

#endif

Internal void CorrectAndOutputSound(LARGE_INTEGER counter_frame_flip,
    SoundOutput* sound_output, int game_update_hz,
    real32 target_seconds_per_frame, int16* samples, GameMemory* game_memory,
    TimeMarker* time_markers, int time_marker_index)
{
    LARGE_INTEGER counter_audio_start = GetCounterStamp();
    real32 seconds_elapsed_before_audio = GetSecondsElapsed(
        counter_frame_flip, counter_audio_start);

    DWORD play_cursor;
    DWORD write_cursor;
    if (SOUND_BUFFER->GetCurrentPosition(&play_cursor, &write_cursor) != DS_OK)
    {
        /*
          TODO: Handle all errors:

          DSERR_ALLOCATED
          DSERR_INVALIDPARAM
          DSERR_NOAGGREGATION
          DSERR_NODRIVER
          DSERR_OUTOFMEMORY
         */
        SOUND_IS_VALID = false;
        return;
    }

    LAST_PLAY_CURSOR = play_cursor;
    if (!SOUND_IS_VALID)
    {
        sound_output->RunningSampleIndex = write_cursor
            / sound_output->BytesPerSample;
        SOUND_IS_VALID = true;
    }

    DWORD byte_to_lock = (sound_output->RunningSampleIndex
        * sound_output->BytesPerSample) % sound_output->BufferSize;
    DWORD expected_sound_bytes_per_frame = (sound_output->SamplesPerSecond
        * sound_output->BytesPerSample) / game_update_hz;
    real32 seconds_left_until_flip = target_seconds_per_frame
        - seconds_elapsed_before_audio;
    DWORD expected_bytes_until_flip = (DWORD)((seconds_left_until_flip
        / target_seconds_per_frame) * (expected_sound_bytes_per_frame));
    DWORD expected_frame_boundary_byte = play_cursor
        + expected_sound_bytes_per_frame;

    DWORD safe_write_cursor = write_cursor;
    if (safe_write_cursor < play_cursor)
        safe_write_cursor += sound_output->BufferSize;

    Assert(safe_write_cursor >= play_cursor);
    safe_write_cursor += sound_output->SafetyBytes;

    bool32 audio_card_is_low_latency = (safe_write_cursor
        < expected_frame_boundary_byte);

    DWORD target_cursor = 0;
    if (audio_card_is_low_latency)
    {
        target_cursor = expected_frame_boundary_byte
            + expected_sound_bytes_per_frame;
    }
    else
    {
        target_cursor = write_cursor + expected_sound_bytes_per_frame
            + sound_output->SafetyBytes;
    }

    target_cursor = target_cursor % sound_output->BufferSize;
    DWORD bytes_to_write = 0;
    if (byte_to_lock > target_cursor)
    {
        bytes_to_write = (sound_output->BufferSize - byte_to_lock);
        bytes_to_write += target_cursor;
    }
    else
    {
        bytes_to_write = target_cursor - byte_to_lock;
    }

    GameSoundBuffer sound_buffer = {};
    sound_buffer.SamplesPerSecond = sound_output->SamplesPerSecond;
    sound_buffer.SamplesCount = bytes_to_write / sound_output->BytesPerSample;
    sound_buffer.Samples = samples;

    GetSoundSamples(game_memory, &sound_buffer);

#if WIN32_DEBUG

    TimeMarker* marker = &time_markers[time_marker_index];
    marker->OutputPlayCursor = play_cursor;
    marker->OutputWriteCursor = write_cursor;
    marker->OutputLocation = byte_to_lock;
    marker->OutputByteCount = bytes_to_write;
    marker->ExpectedFlipPlayCursor = expected_frame_boundary_byte;

    PrintSoundDebugInfo(marker, sound_output, target_cursor);
#endif

    FillSoundBuffer(sound_output, byte_to_lock, bytes_to_write, &sound_buffer);
}
