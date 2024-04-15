#include "data-stream.h"

Internal void RefillStreamIfNecessary(Stream *stream)
{
    if ((stream->Size != 0) || (!stream->First))
        return;

    StreamChunk* current = stream->First;
    stream->Size = current->Size;
    stream->Content = current->Content;
    stream->First = current->Next;
}

Internal void* ConsumeStreamSize(Stream *stream, uint32 size)
{
    void *result = 0;

    RefillStreamIfNecessary(stream);

    if (stream->Size >= size)
    {
        result = stream->Content;
        stream->Content = (uint8*)stream->Content + size;
        stream->Size -= size;
    }
    else
    {
        fprintf(stderr, "ERROR: File underflow\n");
        stream->Size = 0;
        stream->Underflowed = true;
    }

    Assert(!stream->Underflowed);

    return result;
}

Internal uint32 PeekStreamBits(Stream* buffer, uint32 bit_count)
{
    Assert(bit_count <= 32);

    uint32 result = 0;

    while ((buffer->BitCount < bit_count) && (!buffer->Underflowed))
    {
        uint32 byte = *(uint8*)ConsumeStreamSize(buffer, sizeof(uint8));
        buffer->BitBuffer |= (byte << buffer->BitCount);
        buffer->BitCount += 8;
    }

    result = buffer->BitBuffer & ((1 << bit_count) - 1);

    return result;
}

Internal void DiscardStreamBits(Stream* buffer, uint32 bit_count)
{
    buffer->BitCount -= bit_count;
    buffer->BitBuffer >>= bit_count;
}

Internal uint32 ConsumeStreamBits(Stream* buffer, uint32 bit_count)
{
    uint32 result = PeekStreamBits(buffer, bit_count);
    DiscardStreamBits(buffer, bit_count);

    return result;
}

Internal void FlushStreamByte(Stream* buffer)
{
    uint32 count = (buffer->BitCount % 8);
    ConsumeStreamBits(buffer, count);
}

Internal Stream OnDemandMemoryStream()
{
    Stream result = {};

    return result;
}
