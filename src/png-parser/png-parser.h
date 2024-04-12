#include <cstdio>
#include <cstdlib>
#include <stdio.h>

#ifndef PNG_HEADER
#include "../platform.h"

GlobalVariable const uint8 PNG_HEADER_BYTES = 8;
GlobalVariable const uint8 PNG_HUFFMAN_MAX_BIT_COUNT = 16;
GlobalVariable const uint8 PNG_SIGNATURE[] = { 137, 80, 78, 71, 13, 10, 26, 10 };
GlobalVariable const uint8 MAX_REVERSE_BITS_COUNT = 13;
GlobalVariable uint16 REVERSED_BITS[1 << MAX_REVERSE_BITS_COUNT];

#pragma pack(push, 1)

struct PngHeader
{
    uint8 Signature[8];
};

struct PngChunkHeader
{
    uint32 Length;
    union
    {
        uint32 TypeUint32;
        char Type[4];
    };
};

struct PngChunkFooter
{
    uint32 CRC;
};

struct PngIhdr
{
    uint32 Width;
    uint32 Height;
    uint8 BitDepth;
    uint8 ColorType;
    uint8 CompressionMethod;
    uint8 FilterMethod;
    uint8 InterlaceMethod;
};

struct PngIdatHeader
{
    uint8 ZlibMethodFlags;
    uint8 AdditionalFlags;
};

struct PngIdatFooter
{
    uint32 CheckValue;
};

struct BitmapHeader
{
    uint16 FileType;
    uint32 FileSize;
    uint16 Reserved1;
    uint16 Reserved2;
    uint32 BitmapOffset;
    uint32 Size;
    int32 Width;
    int32 Height;
    uint16 Planes;
    uint16 BitsPerPixel;
    uint32 Compression;
    uint32 SizeOfBitmap;
    int32 HorzResolution;
    int32 VertResolution;
    uint32 ColorsUsed;
    uint32 ColorsImportant;
};

#pragma pack(pop)

struct StreamingChunk
{
    uint32 Size;
    void* Content;

    StreamingChunk* Next;
};

struct StreamingBuffer
{
    uint32 Size;
    void* Content;

    uint32 BitCount;
    uint32 BitBuffer;

    bool32 Underflowed;

    StreamingChunk* First;
    StreamingChunk* Last;
};

struct PngHuffmanEntry
{
    uint16 Symbol;
    uint16 BitsUsed;
};

struct PngHuffman
{
    uint32 BitsCountLimit;
    uint32 EntryCount;
    PngHuffmanEntry* Entries;
};

struct Image
{
    uint32 Width;
    uint32 Height;
    uint32* Pixels;
};

GlobalVariable PngHuffmanEntry PNG_LENGTH_EXTRA[] =
{
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {7, 0},
    {8, 0},
    {9, 0},
    {10, 0},
    {11, 1},
    {13, 1},
    {15, 1},
    {17, 1},
    {19, 2},
    {23, 2},
    {27, 2},
    {31, 2},
    {35, 3},
    {43, 3},
    {51, 3},
    {59, 3},
    {67, 4},
    {83, 4},
    {99, 4},
    {115, 4},
    {131, 5},
    {163, 5},
    {195, 5},
    {227, 5},
    {258, 0},
};

GlobalVariable PngHuffmanEntry PNG_DIST_EXTRA[] =
{
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 1},
    {7, 1},
    {9, 2},
    {13, 2},
    {17, 3},
    {25, 3},
    {33, 4},
    {49, 4},
    {65, 5},
    {97, 5},
    {129, 6},
    {193, 6},
    {257, 7},
    {385, 7},
    {513, 8},
    {769, 8},
    {1025, 9},
    {1537, 9},
    {2049, 10},
    {3073, 10},
    {4097, 11},
    {6145, 11},
    {8193, 12},
    {12289, 12},
    {16385, 13},
    {24577, 13},
};

#define PNG_HEADER
#endif
