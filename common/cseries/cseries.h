#pragma once

#include <cassert>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstdarg>

#define COMBINE1(x,y) x##y
#define COMBINE(x,y) COMBINE1(x,y)
#define CONCAT(x, y) x##y
#define STRINGIFY(s) __STRINGIFY(s)
#define __STRINGIFY(s) #s

#define UNIQUE_ID(PREFIX) COMBINE(PREFIX,COMBINE(__LINE__,__COUNTER__))
#define LINE_ID(PREFIX) COMBINE(PREFIX,COMBINE(__LINE__))

// use explicit
//#define DELETE_MOVE_CONSTRUCTOR(_class) _class(const _class&) = delete
//#define DELETE_COPY_CONSTRUCTOR(_class) _class& operator=(const _class&) = delete 
//#define DELETE_DEFAULT_CONSTRUCTOR(_class) _class() = delete

extern int(__cdecl* csmemcmp)(void const* _Buf1, void const* _Buf2, size_t _Size);
extern void* (__cdecl* csmemcpy)(void* _Dst, void const* _Src, size_t _Size);
extern void* (__cdecl* csmemset)(void* _Dst, int _Val, size_t _Size);

extern long csstricmp(char const* s1, char const* s2);
//extern long csstrnicmp(char const* s1, char const* s2, dword size);
//extern char* csstristr(char const* s1, char const* s2);
extern char* csstrnzcpy(char* s1, char const* s2, size_t size);
extern char* csstrnzcat(char* s1, char const* s2, size_t size);
extern size_t csstrnlen(char const* s, size_t size);
extern char* csstrnupr(char* s, size_t size);
extern char* csstrnlwr(char* s, size_t size);
extern char const* csstrstr(char const* s1, char const* s2);
//extern char* csstrtok(char*, char const*, bool, struct csstrtok_data* data);
extern long cvsnzprintf(char* buffer, size_t size, char const* format, va_list list);
extern char* csnzprintf(char* buffer, size_t size, char const* format, ...);
extern char* csnzappendf(char* buffer, size_t size, char const* format, ...);


