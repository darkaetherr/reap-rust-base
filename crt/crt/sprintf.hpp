#pragma once
#include <stdarg.h>

namespace crt {
    int vsprintf(char* buf, char const* fmt, va_list va);
    int sprintf(char* buf, const char* fmt, ...);
} // namespace crt