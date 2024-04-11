#pragma once
#include "levels.hpp"

#include "obfy/lazy_importer.hpp"
#include "obfy/xorstr.hpp"

#include "crt/memory.hpp"
#include "crt/sprintf.hpp"

#include "stl/string.hpp"
#include <source_location>

#if defined(_LOGGING_LEVEL_DEBUG)
    #define _LOGGING_LEVEL e_logging_level::DEBUG
#else
    #define _LOGGING_LEVEL e_logging_level::INFO
#endif

#define DECL_LOGGING_METHOD(name, level, level_name)                                                            \
    inline void name(const std::string_view message, const char* filename, const std::uint32_t line_num, ...) { \
        if constexpr (_LOGGING_LEVEL <= level) {                                                                \
            char msg_formatted[1024] = {};                                                                      \
            crt::memset(msg_formatted, 0, sizeof(msg_formatted));                                               \
                                                                                                                \
            va_list list{};                                                                                     \
            va_start(list, line_num);                                                                           \
            crt::vsprintf(msg_formatted, message.data(), list);                                                 \
            va_end(list);                                                                                       \
                                                                                                                \
            logging::detail::print(msg_formatted, filename, line_num, xorstr_(level_name));                     \
        }                                                                                                       \
    }

namespace logging {
#if defined(_LOGGING_ENABLED)
    namespace detail {
        __declspec(noinline) inline void print(char* message, const char* filename, const std::uint32_t line_num, const char* level) {
            char msg_with_prefix[2048] = {};
            crt::memset(msg_with_prefix, 0, sizeof(msg_with_prefix));
            crt::sprintf(msg_with_prefix, xorstr_("%s :: %s :: L%d >> %s\n"), level, filename, line_num, message);

            LI_FN_CUSTOM_DEF(OutputDebugStringA, void (*)(char*)).cached()(msg_with_prefix);
        }
    } // namespace detail

    DECL_LOGGING_METHOD(debug, e_logging_level::DEBUG, "DEBUG");
    DECL_LOGGING_METHOD(info, e_logging_level::INFO, "INFO");
    DECL_LOGGING_METHOD(warning, e_logging_level::WARNING, "WARNING");
    DECL_LOGGING_METHOD(error, e_logging_level::ERROR, "ERROR");
    DECL_LOGGING_METHOD(critical, e_logging_level::CRITICAL, "CRITICAL");
#else
    __forceinline void debug(...) { }
    __forceinline void info(...) { }
    __forceinline void warning(...) { }
    __forceinline void error(...) { }
    __forceinline void critical(...) { }
#endif
} // namespace logging

#undef DECL_LOGGING_METHOD
#define LOG_DEBUG(fmt, ...) ::logging::debug(fmt, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_INFO(fmt, ...) ::logging::info(fmt, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_WARN(fmt, ...) ::logging::warning(fmt, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_WARNING(fmt, ...) ::logging::warning(fmt, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_ERROR(fmt, ...) ::logging::error(fmt, __FILE__, __LINE__, __VA_ARGS__);
#define LOG_CRITICAL(fmt, ...) ::logging::critical(fmt, __FILE__, __LINE__, __VA_ARGS__);
