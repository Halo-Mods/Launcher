#pragma once

void debug_print(const char* format, ...);

#ifdef _DEBUG
#define DEV(...) debug_print(__VA_ARGS__)
#else
#define DEV(...)
#endif
