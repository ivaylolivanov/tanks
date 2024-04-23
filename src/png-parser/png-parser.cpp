#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include "png-parser.h"
#include "data-stream.cpp"

Internal uint32 SwapRedAndBlue(uint32 color)
{
    uint32 blue = (color >> 16) & 0xFF;
    uint32 red  = (color & 0xFF) << 16;
    uint32 result = (color & 0xFF00FF00) | blue | red;

    return result;
}

Internal uint32 ApplyAlpha(uint32 color)
{
    uint32 red   = (color >> 0)  & 0xFF;
    uint32 green = (color >> 8)  & 0xFF;
    uint32 blue  = (color >> 16) & 0xFF;
    uint32 alpha =  color >> 24;

    red   = (((red   * alpha) + 128) >> 8);
    green = (((green * alpha) + 128) >> 8);
    blue  = (((blue  * alpha) + 128) >> 8);

    uint32 result = (alpha << 24)
        | (blue << 16)
        | (green <<  8)
        | (red <<  0);

    return result;
}

Internal void EndianSwap(uint32* value)
{
    uint32 temp = (*value);
    *value = ((temp << 24)
              | ((temp & 0xFF00) << 8)
              | ((temp >> 8) & 0xFF00)
              | (temp >> 24));

    //*value = _byteswap_ulong(temp);
}

Internal void EndianSwap(uint16 *Value)
{
    uint16 temp = (*Value);
    *Value = ((temp << 8) | (temp >> 8));

    //*Value = _byteswap_ushort(temp);
}

Internal void* AllocatePixels(uint32 width, uint32 height,
    uint32 bytes_per_pixels, uint32 extra_bytes = 0)
{
    void* result = malloc(width * height * bytes_per_pixels
        + (extra_bytes * height));

    return result;
}

Internal StreamChunk* AllocateStreamChunk()
{
    StreamChunk* result = (StreamChunk*)malloc(sizeof(StreamChunk));
    return result;
}

Internal PngHuffman AllocateHuffman(uint32 bits_count)
{
    Assert(bits_count <= PNG_HUFFMAN_MAX_BIT_COUNT);
    PngHuffman result = {};

    result.BitsCountLimit = bits_count;
    result.EntryCount = 1 << bits_count;
    result.Entries = (PngHuffmanEntry*)malloc(sizeof(PngHuffmanEntry)
        * result.EntryCount);

    return result;
}

Internal bool32 IsPngFormat(PngHeader* header)
{
    bool32 result = true;

    for (int i = 0; i < PNG_HEADER_BYTES; ++i)
    {
        if (PNG_SIGNATURE[i] == header->Signature[i])
            continue;

        result = false;
        break;
    }

    return result;
}

Internal Stream ReadWholeFile(char* filepath)
{
    Stream result = {};

    FILE* file_stream;
    fopen_s(&file_stream, filepath, "rb");
    if (file_stream)
    {
        fseek(file_stream, 0, SEEK_END);
        result.Size = ftell(file_stream);
        fseek(file_stream, 0, SEEK_SET);

        result.Content = malloc(result.Size);
        fread(result.Content, result.Size, 1, file_stream);
    }
    fclose(file_stream);

    return result;
}

Internal uint32 ReverseBits(uint32 value, uint32 count)
{
    uint32 result = 0;

    for (uint32 i = 0; i <= (count / 2); ++i)
    {
        uint32 inverse = (count - (i + 1));
        result |= ((value >> i) & 0x1) << inverse;
        result |= ((value >> inverse) & 0x1) << i;
    }

    return result;
}

Internal void ComputeHuffman(uint32 symbol_count, uint32 *symbol_code_length,
    PngHuffman *result, uint32 symbol_addend = 0)
{
    uint32 code_length_hist[PNG_HUFFMAN_MAX_BIT_COUNT] = {};
    for (uint32 symbol_index = 0; symbol_index < symbol_count; ++symbol_index)
    {
        uint32 count = symbol_code_length[symbol_index];
        Assert(count <= ArrayCount(code_length_hist));
        ++code_length_hist[count];
    }

    uint32 next_unused_code[PNG_HUFFMAN_MAX_BIT_COUNT];
    next_unused_code[0] = 0;
    code_length_hist[0] = 0;
    for (uint32 bit_index = 1; bit_index < ArrayCount(next_unused_code);
        ++bit_index)
        next_unused_code[bit_index] = ((next_unused_code[bit_index - 1] +
            code_length_hist[bit_index - 1]) << 1);

    for (uint32 symbol_index = 0; symbol_index < symbol_count; ++symbol_index)
    {
        uint32 code_length_in_bits = symbol_code_length[symbol_index];
        if (!code_length_in_bits)
            continue;

        Assert(code_length_in_bits < ArrayCount(next_unused_code));
        uint32 code = next_unused_code[code_length_in_bits]++;

        uint32 arbitrary_bits = result->BitsCountLimit
            - code_length_in_bits;
        uint32 entry_count = (1 << arbitrary_bits);

        for (uint32 entry_index = 0; entry_index < entry_count; ++entry_index)
        {
            uint32 base_index = (code << arbitrary_bits) | entry_index;
            uint32 index = ReverseBits(base_index, result->BitsCountLimit);

            PngHuffmanEntry *entry = result->Entries + index;

            uint32 symbol = (symbol_index + symbol_addend);
            entry->BitsUsed = (uint16)code_length_in_bits;
            entry->Symbol = (uint16)symbol;

            Assert(entry->BitsUsed == code_length_in_bits);
            Assert(entry->Symbol == symbol);
        }
    }
}

Internal uint32 HuffmanDecode(PngHuffman *huffman, Stream *input)
{
    uint32 entry_index = PeekStreamBits(input,
        huffman->BitsCountLimit);
    Assert(entry_index < Huffman->EntryCount);

    PngHuffmanEntry entry = huffman->Entries[entry_index];

    uint32 result = entry.Symbol;
    DiscardStreamBits(input, entry.BitsUsed);
    Assert(entry.BitsUsed);

    return result;
}

Internal uint8 PNGFilter1And2(uint8 *x, uint8 *a, uint32 channel)
{
    uint8 result = (uint8)x[channel] + (uint8)a[channel];
    return result;
}

Internal uint8 PNGFilter3(uint8 *x, uint8 *a, uint8 *b, uint32 channel)
{
    uint32 average = ((uint32)a[channel] + (uint32)b[channel]) / 2;
    uint8 result = (uint8)x[channel] + (uint8)average;
    return result;
}

Internal uint8 PNGFilter4(uint8 *x, uint8 *a_full, uint8 *b_full, uint8 *c_full,
    uint32 channel)
{
    int32 a = (int32)a_full[channel];
    int32 b = (int32)b_full[channel];
    int32 c = (int32)c_full[channel];
    int32 p = a + b - c;

    int32 pa = p - a;
    int32 pb = p - b;
    int32 pc = p - c;

    if (pa < 0) pa = -pa;
    if (pb < 0) pb = -pb;
    if (pc < 0) pc = -pc;

    int32 paeth;
    if      ((pa <= pb) && (pa <= pc)) paeth = a;
    else if (pb <= pc)                 paeth = b;
    else                               paeth = c;

    uint8 result = (uint8)x[channel] + (uint8)paeth;
    return result;
}

Internal void PNGFilterReconstruct(uint32 width, uint32 height,
    uint8 *decompressed_pixels, uint8 *final_pixels)
{
    uint32 zero = 0;
    uint8 *prior_row = (uint8 *)&zero;
    int32 prior_row_advance = 0;
    uint8 *source = decompressed_pixels;
    uint8 *destination = final_pixels;

    for (uint32 y = 0; y < height; ++y)
    {
        uint8 filter = *source++;
        uint8 *current_row = destination;

        switch (filter)
        {
            case 0:
            {
                for (uint32 x = 0; x < width; ++x)
                {
                    *(uint32 *)destination = *(uint32 *)source;

                    destination += 4;
                    source += 4;
                }
            } break;

            case 1:
            {
                uint32 pixel_a = 0;
                for (uint32 x = 0; x < width; ++x)
                {
                    destination[0] = PNGFilter1And2(source, (uint8 *)&pixel_a, 0);
                    destination[1] = PNGFilter1And2(source, (uint8 *)&pixel_a, 1);
                    destination[2] = PNGFilter1And2(source, (uint8 *)&pixel_a, 2);
                    destination[3] = PNGFilter1And2(source, (uint8 *)&pixel_a, 3);

                    pixel_a = *(uint32 *)destination;

                    destination += 4;
                    source += 4;
                }
            } break;

            case 2:
            {
                uint8 *pixel_b = prior_row;
                for (uint32 x = 0; x < width; ++x)
                {
                    destination[0] = PNGFilter1And2(source, pixel_b, 0);
                    destination[1] = PNGFilter1And2(source, pixel_b, 1);
                    destination[2] = PNGFilter1And2(source, pixel_b, 2);
                    destination[3] = PNGFilter1And2(source, pixel_b, 3);

                    pixel_b += prior_row_advance;
                    destination += 4;
                    source += 4;
                }
            } break;

            case 3:
            {
                // TODO: To test!
                uint32 pixel_a = 0;
                uint8 *pixel_b = prior_row;
                for (uint32 x = 0; x < width; ++x)
                {
                    destination[0] = PNGFilter3(source, (uint8 *)&pixel_a,
                        pixel_b, 0);
                    destination[1] = PNGFilter3(source, (uint8 *)&pixel_a,
                        pixel_b, 1);
                    destination[2] = PNGFilter3(source, (uint8 *)&pixel_a,
                        pixel_b, 2);
                    destination[3] = PNGFilter3(source, (uint8 *)&pixel_a,
                        pixel_b, 3);

                    pixel_a = *(uint32 *)destination;
                    pixel_b += prior_row_advance;

                    destination += 4;
                    source += 4;
                }
            } break;

            case 4:
            {
                uint32 pixel_a = 0;
                uint8 *pixel_b = prior_row;
                uint32 pixel_c = 0;
                for (uint32 x = 0; x < width; ++x)
                {
                    destination[0] = PNGFilter4(source, (uint8 *)&pixel_a,
                        pixel_b, (uint8 *)&pixel_c, 0);
                    destination[1] = PNGFilter4(source, (uint8 *)&pixel_a,
                        pixel_b, (uint8 *)&pixel_c, 1);
                    destination[2] = PNGFilter4(source, (uint8 *)&pixel_a,
                        pixel_b, (uint8 *)&pixel_c, 2);
                    destination[3] = PNGFilter4(source, (uint8 *)&pixel_a,
                        pixel_b, (uint8 *)&pixel_c, 3);

                    pixel_c = *(uint32 *)pixel_b;
                    pixel_a = *(uint32 *)destination;

                    pixel_b += prior_row_advance;
                    destination += 4;
                    source += 4;
                }
            } break;

            default:
            {
                fprintf(stderr, "ERROR: Unrecognized row filter %u.\n", filter);
            } break;

        }

        prior_row = current_row;
        prior_row_advance = 4;
    }
}

enum PixelOpcode
{
    PixelOpcode_SwapRedAndBlue = 0x01,
    PixelOpcode_ApplyAlpha     = 0x02,
};

Internal void PNGApplyPixelOperations(uint32 width, uint32 height,
    uint8* final_pixels, uint32 pixel_opcode)
{
    bool32 apply_alpha       = pixel_opcode & PixelOpcode_ApplyAlpha;
    bool32 swap_red_and_blue = pixel_opcode & PixelOpcode_SwapRedAndBlue;

    uint32 mid_point_y = ((height + 1) / 2);
    uint32 *row_above = (uint32 *)final_pixels;
    uint32 *row_below = row_above + ((height - 1) * width);
    for (uint32 y = 0; y < mid_point_y; ++y)
    {
        uint32 *pixel0 = row_above;
        uint32 *pixel1 = row_below;
        for (uint32 x = 0; x < width; ++x)
        {
            uint32 color0 = *pixel0;
            uint32 color1 = *pixel1;
            if (swap_red_and_blue)
            {
                color0 = SwapRedAndBlue(*pixel0);
                color1 = SwapRedAndBlue(*pixel1);
            }

            if (apply_alpha)
            {
                color0 = ApplyAlpha(*pixel0);
                color1 = ApplyAlpha(*pixel1);
            }

            *pixel0++ = color0;
            *pixel1++ = color1;
        }
        row_above += width;
        row_below -= width;
    }
}

Internal Image ParsePNG(Stream file)
{
    Stream *raw = &file;

    bool32 supported = false;
    for (uint16 r_index = 0; r_index < ArrayCount(REVERSED_BITS); ++r_index)
        REVERSED_BITS[r_index] = (uint16)ReverseBits(r_index,
            MAX_REVERSE_BITS_COUNT);

    uint32 width = 0;
    uint32 height = 0;
    uint8 *final_pixels = 0;

    Image result = {};

    PngHeader *png_header = (PngHeader*)ConsumeStreamSize(raw, sizeof(PngHeader));
    if (!png_header)
        return result;

    Stream compact_data = {};
    while (raw->Size > 0)
    {
        PngChunkHeader *chunk_header = (PngChunkHeader*)ConsumeStreamSize(raw,
            sizeof(PngChunkHeader));
        if (chunk_header)
        {
            EndianSwap(&chunk_header->Length);
            EndianSwap(&chunk_header->TypeUint32);

            void *chunk_data = ConsumeStreamSize(raw,
                chunk_header->Length);
            PngChunkFooter *chunk_footer = (PngChunkFooter*)ConsumeStreamSize(
                raw, sizeof(PngChunkFooter));
            EndianSwap(&chunk_footer->CRC);

            if(chunk_header->TypeUint32 == 'IHDR')
            {
                PngIhdr *ihdr = (PngIhdr *)chunk_data;

                EndianSwap(&ihdr->Width);
                EndianSwap(&ihdr->Height);

                supported = (ihdr->BitDepth == 8)
                    && (ihdr->ColorType == 6)
                    && (ihdr->CompressionMethod == 0)
                    && (ihdr->FilterMethod == 0)
                    && (ihdr->InterlaceMethod == 0);
                if (supported)
                {
                    width = ihdr->Width;
                    height = ihdr->Height;
                }
            }
            else if (chunk_header->TypeUint32 == 'IDAT')
            {
                StreamChunk *chunk = AllocateStreamChunk();
                chunk->Size = chunk_header->Length;
                chunk->Content = chunk_data;
                chunk->Next = 0;

                compact_data.Last = ((compact_data.Last ?
                    compact_data.Last->Next : compact_data.First) = chunk);
            }
        }
    }

    if (!supported)
        return result;

    PngIdatHeader* idat_header = (PngIdatHeader*)ConsumeStreamSize(
        &compact_data, sizeof(PngIdatHeader));

    uint8 CM = (idat_header->ZlibMethodFlags & 0xF);
    uint8 CINFO = (idat_header->ZlibMethodFlags >> 4);
    uint8 FCHECK = (idat_header->AdditionalFlags & 0x1F);
    uint8 FDICT = (idat_header->AdditionalFlags >> 5) & 0x1;
    uint8 FLEVEL = (idat_header->AdditionalFlags >> 6);

    supported = ((CM == 8) && (FDICT == 0));

    if (!supported)
        return result;

    final_pixels = (uint8 *)AllocatePixels(width, height, 4);
    uint8 *decompressed_pixels = (uint8 *)AllocatePixels(width, height, 4, 1);
    uint8 *decompressed_pixels_end = decompressed_pixels
        + (height*((width*4) + 1));
    uint8 *dest = decompressed_pixels;
    fprintf(stdout, "Decompressing...\n");

    uint32 bfinal = 0;
    while (bfinal == 0)
    {
        bfinal = ConsumeStreamBits(&compact_data, 1);
        uint32 btype = ConsumeStreamBits(&compact_data, 2);

        if (btype == 0)
        {
            FlushStreamByte(&compact_data);

            uint16 len = *((uint16*)ConsumeStreamSize(&compact_data, sizeof(uint16)));
            uint16 nlen = *((uint16*)ConsumeStreamSize(&compact_data, sizeof(uint16)));

            if ((uint16)len != (uint16)~nlen)
                fprintf(stderr, "ERROR: len/nlen mismatch.\n");

            uint8 *source = (uint8 *)ConsumeStreamSize(&compact_data, len);
            if (!source)
                continue;

            while (len--)
                *dest++ = *source++;
        }
        else if (btype == 3)
        {
            fprintf(stderr, "ERROR: BTYPE of %u encountered.\n", btype);
        }
        else
        {
            uint32 lit_len_dist_table[512];
            PngHuffman lit_len_huffman = AllocateHuffman(15);
            PngHuffman dist_huffman = AllocateHuffman(15);

            uint32 hlit = 0;
            uint32 hdist = 0;
            if (btype == 2)
            {
                hlit         = ConsumeStreamBits(&compact_data, 5);
                hdist        = ConsumeStreamBits(&compact_data, 5);
                uint32 hclen = ConsumeStreamBits(&compact_data, 4);

                hlit += 257;
                hdist += 1;
                hclen += 4;

                uint32 hclen_swizzle[] =
                {
                    16, 17, 18, 0, 8, 7, 9, 6, 10, 5,
                    11, 4, 12, 3, 13, 2, 14, 1, 15,
                };
                Assert(hclen <= ArrayCount(hclen_swizzle));
                uint32 hclen_table[ArrayCount(hclen_swizzle)] = {};

                for(uint32 index = 0; index < hclen; ++index)
                    hclen_table[hclen_swizzle[index]] =
                        ConsumeStreamBits(&compact_data, 3);

                PngHuffman dict_huffman = AllocateHuffman(7);
                ComputeHuffman(ArrayCount(hclen_swizzle), hclen_table,
                    &dict_huffman);

                uint32 lit_len_count = 0;
                uint32 len_count = hlit + hdist;
                Assert(len_count <= ArrayCount(lit_len_dist_table));
                while (lit_len_count < len_count)
                {
                    uint32 rep_count = 1;
                    uint32 rep_val = 0;
                    uint32 encoded_len = HuffmanDecode(&dict_huffman, &compact_data);
                    if (encoded_len <= 15)
                    {
                        rep_val = encoded_len;
                    }
                    else if (encoded_len == 16)
                    {
                        rep_count = 3
                            + ConsumeStreamBits(&compact_data, 2);

                        Assert(LitLenCount > 0);
                        rep_val = lit_len_dist_table[lit_len_count - 1];
                    }
                    else if (encoded_len == 17)
                    {
                        rep_count = 3 + ConsumeStreamBits(&compact_data, 3);
                    }
                    else if(encoded_len == 18)
                    {
                        rep_count = 11 + ConsumeStreamBits(&compact_data, 7);
                    }
                    else
                    {
                        fprintf(stderr,
                            "ERROR: EncodedLen of %u encountered.\n",
                            encoded_len);
                    }

                    while(rep_count--)
                        lit_len_dist_table[lit_len_count++] = rep_val;
                }
                Assert(lit_len_count == len_count);

            }
            else if (btype == 1)
            {
                hlit = 288;
                hdist = 32;
                uint32 bit_counts[][2] =
                {
                    {143, 8},
                    {255, 9},
                    {279, 7},
                    {287, 8},
                    {319, 5},
                };

                uint32 bit_count_index = 0;
                for (uint32 range_index = 0; range_index < ArrayCount(bit_counts);
                    ++range_index)
                {
                    uint32 bit_count  = bit_counts[range_index][1];
                    uint32 last_value = bit_counts[range_index][0];
                    while (bit_count_index <= last_value)
                        lit_len_dist_table[bit_count_index++] = bit_count;

                }
            }
            else
            {
                fprintf(stderr, "ERROR: BTYPE of %u encountered.\n", btype);
            }

            ComputeHuffman(hlit, lit_len_dist_table, &lit_len_huffman);
            ComputeHuffman(hdist, lit_len_dist_table + hlit, &dist_huffman);

            for (;;)
            {
                uint32 lit_len = HuffmanDecode(&lit_len_huffman, &compact_data);
                if(lit_len <= 255)
                {
                    uint32 out = (lit_len & 0xFF);
                    *dest++ = (uint8)out;
                }
                else if(lit_len >= 257)
                {
                    uint32 len_tab_index = (lit_len - 257);
                    PngHuffmanEntry len_tab = PNG_LENGTH_EXTRA[len_tab_index];
                    uint32 len = len_tab.Symbol;
                    if (len_tab.BitsUsed)
                    {
                        uint32 extra_bits = ConsumeStreamBits(&compact_data,
                            len_tab.BitsUsed);
                        len += extra_bits;
                    }

                    uint32 dist_tab_index = HuffmanDecode(
                        &dist_huffman, &compact_data);
                    PngHuffmanEntry dist_tab = PNG_DIST_EXTRA[dist_tab_index];
                    uint32 distance = dist_tab.Symbol;
                    if (dist_tab.BitsUsed)
                    {
                        uint32 extra_bits = ConsumeStreamBits(&compact_data,
                            dist_tab.BitsUsed);
                        distance += extra_bits;
                    }

                    uint8 *source = dest - distance;
                    Assert((source + len) <= decompressed_pixels_end);
                    Assert((dest + len) <= decompressed_pixels_end);
                    Assert(Source >= decompressed_pixels);

                    while (len--)
                        *dest++ = *source++;
                }
                else
                {
                    break;
                }
            }
        }
    }

    Assert(dest == decompressed_pixels_end);
    PNGFilterReconstruct(width, height, decompressed_pixels, final_pixels);
    uint32 pixel_operations = PixelOpcode_SwapRedAndBlue;
    PNGApplyPixelOperations(width, height, final_pixels, pixel_operations);

    fprintf(stdout, "Supported: %s\n", supported ? "TRUE" : "FALSE");

    result.Width = width;
    result.Height = height;
    result.Pixels = (uint32 *)final_pixels;
    return result;
}
