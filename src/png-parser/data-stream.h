#ifndef DATA_STREAM

struct StreamChunk
{
    char *File;
    uint32 LineNumber;

    uint32 Size;
    void *Content;

    StreamChunk *Next;
};

struct Stream
{
    Stream *Errors;

    uint32 Size;
    void *Content;

    uint32 BitCount;
    uint32 BitBuffer;

    bool32 Underflowed;

    StreamChunk *First;
    StreamChunk *Last;
};

Internal Stream OnDemandMemoryStream();

#define DATA_STREAM
#endif
