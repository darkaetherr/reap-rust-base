#pragma once

namespace hshr {
#if defined(_M_X64) || defined(__amd64__)
    inline constexpr unsigned long long _FNV_offset_basis = 14695981039346656037ULL;
    inline constexpr unsigned long long _FNV_prime = 1099511628211ULL;
#else // defined(_WIN64)
    inline constexpr unsigned long _FNV_offset_basis = 2166136261U;
    inline constexpr unsigned long _FNV_prime = 16777619U;
#endif // defined(_WIN64)

    inline constexpr unsigned long _FNV_offset_basis32 = 2166136261U;
    inline constexpr unsigned long _FNV_prime32 = 16777619U;

    typedef unsigned long ULONG;

    template <size_t in>
    struct CEVAL {
        constexpr static size_t value = in;
    };
    template <unsigned long in>
    struct CEVAL32 {
        constexpr static ULONG value = in;
    };

    constexpr size_t CompileTimeFnv1aHash(const char* m_szString, size_t m_nValue = _FNV_offset_basis) {
        return (*m_szString ? CompileTimeFnv1aHash(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime) : m_nValue);
    }
    constexpr size_t CompileTimeFnv1aHash(const wchar_t* m_szString, size_t m_nValue = _FNV_offset_basis) {
        return (*m_szString ? CompileTimeFnv1aHash(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime) : m_nValue);
    }
    __forceinline size_t RunTimeFnv1aHash(const char* m_szString, size_t m_nValue = _FNV_offset_basis) {
        return (*m_szString ? RunTimeFnv1aHash(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime) : m_nValue);
    }
    __forceinline size_t RunTimeFnv1aHash(const wchar_t* m_szString, size_t m_nValue = _FNV_offset_basis) {
        return (*m_szString ? RunTimeFnv1aHash(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime) : m_nValue);
    }

    constexpr ULONG CompileTimeFnv1aHash32(const char* m_szString, ULONG m_nValue = _FNV_offset_basis32) {
        return (*m_szString ? CompileTimeFnv1aHash32(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime32) : m_nValue);
    }
    constexpr ULONG CompileTimeFnv1aHash32(const wchar_t* m_szString, ULONG m_nValue = _FNV_offset_basis32) {
        return (*m_szString ? CompileTimeFnv1aHash32(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime32) : m_nValue);
    }
    __forceinline ULONG RunTimeFnv1aHash32(const char* m_szString, ULONG m_nValue = _FNV_offset_basis32) {
        return (*m_szString ? RunTimeFnv1aHash32(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime32) : m_nValue);
    }
    __forceinline ULONG RunTimeFnv1aHash32(const wchar_t* m_szString, ULONG m_nValue = _FNV_offset_basis32) {
        return (*m_szString ? RunTimeFnv1aHash32(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime32) : m_nValue);
    }

    template <class T>
    consteval size_t c_hash( const T* m_szString, size_t m_nValue = _FNV_offset_basis )
    {
        return (*m_szString ? c_hash(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime) : m_nValue);
    }
    template <class T>
    __forceinline size_t hash(const T* m_szString, size_t m_nValue = _FNV_offset_basis) {
        return (*m_szString ? hash(m_szString + 1, (m_nValue ^= *m_szString) * _FNV_prime) : m_nValue);
    }
} // namespace hash