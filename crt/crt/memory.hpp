#pragma once

namespace crt {
    using malloc_t = void* (*)(size_t size);
    using realloc_t = void* (*)(void* block, size_t size);
    using free_t = void (*)(void* block);

    inline void* malloc{};
    inline void* realloc{};
    inline void* free{};

    __forceinline const void* memchr(const void* src, int chr, size_t len) {
        auto _src = static_cast<const unsigned char*>(src);

        while (len-- > 0) {
            if (*_src == chr) {
                return static_cast<const void*>(_src);
            }

            _src++;
        }

        return 0;
    }

    __forceinline void* memcpy(void* dst, const void* src, size_t len) {
        auto _dst = static_cast<char*>(dst);
        auto _src = static_cast<const char*>(src);

        while (len--) {
            *_dst++ = *_src++;
        }

        return dst;
    }

#pragma warning(disable:4244)
    __declspec(noinline) __forceinline void* memset(void* dst, int c, size_t n) {
        volatile unsigned char* d = (unsigned char*)dst; /* avoid optimizations */
        while (n--)
            *d++ = c;
        return dst;
    }
#pragma warning(default:4244)

    __forceinline int memcmp(const void* buf1, const void* buf2, size_t len) {
        auto char_buf1 = static_cast<const unsigned char*>(buf1);
        auto char_buf2 = static_cast<const unsigned char*>(buf2);

        for (size_t i = 0; i < len; i++) {
            if (char_buf1[i] < char_buf2[i]) {
                return -1;
            } else if (char_buf1[i] > char_buf2[i]) {
                return 1;
            }
        }

        return 0;
    }

    __forceinline void* memmove(void* dst, const void* src, size_t len) {
        auto _dst = static_cast<char*>(dst);

        auto _src = const_cast<char*>(static_cast<const char*>(src));

        if (_dst < _src) {
            while (len--) {
                *_dst++ = *_src++;
            }
        } else {
            auto last_src = _src + (len - 1);
            auto last_dst = _dst + (len - 1);

            while (len--) {
                *last_dst-- = *last_src--;
            }
        }

        return dst;
    }

    typedef struct _KSYSTEM_TIME {
        unsigned long LowPart;
        long High1Time;
        long High2Time;
    } KSYSTEM_TIME, *PKSYSTEM_TIME;

    typedef struct _KUSER_SHARED_DATA {
        unsigned long TickCountLowDeprecated;
        unsigned long TickCountMultiplier;

        volatile KSYSTEM_TIME InterruptTime;
        volatile KSYSTEM_TIME SystemTime;
        volatile KSYSTEM_TIME TimeZoneBias;
    } KUSER_SHARED_DATA, *PKUSER_SHARED_DATA;

    typedef union _LARGE_INTEGER {
        struct {
            unsigned long LowPart;
            long HighPart;
        };
        struct {
            unsigned long LowPart;
            long HighPart;
        } u;
        long long QuadPart;
    } LARGE_INTEGER;

    inline float system_time() {
        LARGE_INTEGER systime;
        auto& usrhd_systemtime = ((KUSER_SHARED_DATA*)(0x7ffe0000))->SystemTime;

        do {
            systime.HighPart = usrhd_systemtime.High1Time;
            systime.LowPart = usrhd_systemtime.LowPart;
        } while (systime.HighPart != usrhd_systemtime.High2Time);

        constexpr auto MSPERSEC = 1000ll;
        constexpr auto SECSPERDAY = 86400ll;
        constexpr auto TICKSPERSEC = 10000000ll;
        constexpr auto TICKSPERMSEC = 10000ll;

        auto ms_sincestart = systime.QuadPart / TICKSPERMSEC;
        auto weekly_time = ms_sincestart % (SECSPERDAY * MSPERSEC * 7);
        return weekly_time / 1000.f;
    }
} // namespace crt