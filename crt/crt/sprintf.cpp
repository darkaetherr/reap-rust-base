#define STB_SPRINTF_IMPLEMENTATION
#include "detail/stb_sprintf.hpp"

#include "sprintf.hpp"

namespace crt {
    int vsprintf(char* buf, char const* fmt, va_list va) {
        return stbsp_vsprintf(buf, fmt, va);
    }

    int sprintf(char* buf, const char* fmt, ...) {
        va_list list{};
        va_start(list, fmt);
        auto result = stbsp_vsprintf(buf, fmt, list);
        va_end(list);

        return result;
    }
} // namespace crt