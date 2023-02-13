#include "mcclib-private-pch.h"

void debug_print(const char* format, ...)
{
	char message[2048] = {};
	va_list args;

	va_start(args, format);
	vsnprintf(message, sizeof(message), format, args);
	va_end(args);
	message[sizeof(message) - 1] = '\0';

	OutputDebugStringA(message);
}
