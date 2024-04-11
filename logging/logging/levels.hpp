#pragma once
#include <cstdint>

namespace logging {
    enum e_logging_level : std::uint8_t {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        CRITICAL = 4
    };
} // namespace logging
