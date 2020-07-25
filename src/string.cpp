#include "../include/string.h"

#include <cstdlib>
#include <cstring>

namespace Rw
{
inline UInt32 GetStringSize(const Char *string)
{
    return ((((strlen(string) + 1) * sizeof(Char)) + 3) & ~3);
}

String::~String()
{
    free(string);
}

void String::Read(Chunk *chunk, ChunkHeader *header, Stream *stream)
{
    String *str = (String *)chunk;
    UInt32 length = header->length;

    str->string = (Char *)malloc(length * sizeof(Char));

    char multiByteString[64];
    Char *baseString = str->string;

    while (length > 0)
    {
        UInt32 bytesToRead = (length > 64) ? 64 : length;

        stream->Read(multiByteString, bytesToRead);

        length -= bytesToRead;

        for (UInt32 i = 0; i < bytesToRead; i++)
        {
            baseString[i] = (Char)multiByteString[i];
        }

        baseString += bytesToRead;
    }
}

void String::Write(Chunk *chunk, Stream *stream)
{
    String *str = (String *)chunk;

    const Char *string = (str->string) ? str->string : "";
    UInt32 length = GetStringSize(string);

    stream->Write(string, length);
}

UnicodeString::~UnicodeString()
{
    free(string);
}

void UnicodeString::Read(Chunk *chunk, ChunkHeader *header, Stream *stream)
{
    UnicodeString *str = (UnicodeString *)chunk;
    UInt32 length = header->length;

    str->string = (Char *)malloc(length);

    unsigned short unicodeString[64];
    Char *baseString = str->string;

    while (length > 0)
    {
        UInt32 bytesToRead = (length > 128) ? 128 : length;
        UInt32 charCount = bytesToRead >> 1;

        stream->Read(unicodeString, bytesToRead);

        length -= bytesToRead;

        for (UInt32 i = 0; i < charCount; i++)
        {
            baseString[i] = (Char)unicodeString[i];
        }

        baseString += charCount;
    }
}

void UnicodeString::Write(Chunk *chunk, Stream *stream)
{
    UnicodeString *str = (UnicodeString *)chunk;

    const Char *string = (str->string) ? str->string : "";
    UInt32 length = GetStringSize(string);

    stream->Write(string, length);
}
}