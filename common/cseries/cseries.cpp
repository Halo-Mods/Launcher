#include "common_private_pch.h"

#include <cstdio>
#include <cstring>
#include <cctype>

int(__cdecl* csmemcmp)(void const* _Buf1, void const* _Buf2, size_t _Size) = memcmp;
void* (__cdecl* csmemcpy)(void* _Dst, void const* _Src, size_t _Size) = memcpy;
void* (__cdecl* csmemset)(void* _Dst, int _Val, size_t _Size) = memset;

#define MAXIMUM_STRING_SIZE 0x100000

long csstricmp(char const* s1, char const* s2)
{
    return _stricmp(s1, s2);
}

//long csstrnicmp(char const* s1, char const* s2, size_t size)
//char* csstristr(char const* s1, char const* s2)

char* csstrnzcpy(char* s1, char const* s2, size_t size)
{
    assert(s1 && s2);
    assert(size > 0 && size <= MAXIMUM_STRING_SIZE);

    strncpy_s(s1, size, s2, size);
    s1[size - 1] = 0;

    size_t s2_size = strlen(s2);
    memset(s1 + s2_size, 0, size - s2_size);

    return s1;
}

char* csstrnzcat(char* s1, char const* s2, size_t size)
{
    assert(s1 && s2);
    assert(size > 0 && size <= MAXIMUM_STRING_SIZE);

    size_t len = csstrnlen(s1, size);
    return csstrnzcpy(s1 + len, s2, size - len);
}

size_t csstrnlen(char const* s, size_t size)
{
    assert(s);
    assert(size > 0 && size <= MAXIMUM_STRING_SIZE);

    return strnlen(s, size);
}

char* csstrnupr(char* s, size_t size)
{
    assert(s);
    assert(size >= 0 && size <= MAXIMUM_STRING_SIZE);

    for (size_t i = 0; i < size; i++)
        s[i] = toupper(s[i]);

    return s;
}

char* csstrnlwr(char* s, size_t size)
{
    assert(s);
    assert(size >= 0 && size <= MAXIMUM_STRING_SIZE);

    for (size_t i = 0; i < size; i++)
        s[i] = tolower(s[i]);

    return s;
}

char const* csstrstr(char const* s1, char const* s2)
{
    return strstr(s1, s2);
}

//char* csstrtok(char*, char const*, bool, struct csstrtok_data* data)

long cvsnzprintf(char* buffer, size_t size, char const* format, va_list list)
{
    assert(buffer);
    assert(format);
    assert(size > 0);

    long result = vsnprintf(buffer, size - 1, format, list);
    buffer[size - 1] = 0;

    size_t buf_size = strlen(buffer);
    memset(buffer + buf_size, 0, size - buf_size);

    return result;
}

char* csnzprintf(char* buffer, size_t size, char const* format, ...)
{
    va_list list;
    va_start(list, format);

    cvsnzprintf(buffer, size, format, list);

    va_end(list);

    return buffer;
}

char* csnzappendf(char* buffer, size_t size, char const* format, ...)
{
    size_t current_length = strlen(buffer);
    assert(current_length >= 0 && current_length < size);

    va_list list;
    va_start(list, format);

    cvsnzprintf(&buffer[current_length], size - current_length, format, list);

    va_end(list);

    return buffer;
}
