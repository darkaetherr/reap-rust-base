#include <crt.hpp>

int __cdecl __stdio_common_vsprintf(_In_ unsigned __int64 _Options, _Out_writes_opt_z_(_BufferCount) char* _Buffer, _In_ size_t _BufferCount,
                                    _In_z_ _Printf_format_string_params_(2) char const* _Format, _In_opt_ _locale_t _Locale, va_list _ArgList) {
    return crt::vsprintf(_Buffer, _Format, _ArgList);
}

_Success_(return >= 0) int __cdecl __stdio_common_vsprintf_s(_In_ unsigned __int64 _Options, _Out_writes_z_(_BufferCount) char* _Buffer,
                                                             _In_ size_t _BufferCount, _In_z_ _Printf_format_string_params_(2) char const* _Format,
                                                             _In_opt_ _locale_t _Locale, va_list _ArgList) {
    return crt::vsprintf(_Buffer, _Format, _ArgList);
}

_Success_(return >= 0) int __cdecl __stdio_common_vsnprintf_s(_In_ unsigned __int64 _Options, _Out_writes_opt_z_(_BufferCount) char* _Buffer,
                                                              _In_ size_t _BufferCount, _In_ size_t _MaxCount,
                                                              _In_z_ _Printf_format_string_params_(2) char const* _Format, _In_opt_ _locale_t _Locale,
                                                              va_list _ArgList) {
    return crt::vsprintf(_Buffer, _Format, _ArgList);
}

_Success_(return >= 0) int __cdecl __stdio_common_vsprintf_p(_In_ unsigned __int64 _Options, _Out_writes_z_(_BufferCount) char* _Buffer,
                                                             _In_ size_t _BufferCount, _In_z_ _Printf_format_string_params_(2) char const* _Format,
                                                             _In_opt_ _locale_t _Locale, va_list _ArgList) {
    return crt::vsprintf(_Buffer, _Format, _ArgList);
}

int __cdecl __stdio_common_vsscanf(_In_ unsigned __int64 _Options, _In_reads_(_BufferCount) _Pre_z_ char const* _Buffer, _In_ size_t _BufferCount,
                                   _In_z_ _Scanf_format_string_params_(2) char const* _Format, _In_opt_ _locale_t _Locale, va_list _ArgList) {
    return 0;
}
