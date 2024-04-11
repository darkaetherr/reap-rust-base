#include <crt.hpp>

#include <clocale>
#include <exception>
#include <obfy/lazy_importer.hpp>
#if !defined(__clang__)
    #pragma function(_dtest)
#endif

extern "C" int _fltused = 0;

extern "C" {
#pragma section(".CRT$XIA", long, read)
#pragma section(".CRT$XIZ", long, read)
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)
#pragma section(".CRT$XPA", long, read)
#pragma section(".CRT$XPZ", long, read)
#pragma section(".CRT$XTA", long, read)
#pragma section(".CRT$XTZ", long, read)
#pragma comment(linker, "/merge:.CRT=.rdata")

    typedef void (*_PVFV)(void);
    typedef int (*_PIFV)(void);

    // C initializers
    __declspec(allocate(".CRT$XIA")) _PIFV __xi_a[] = {0};
    __declspec(allocate(".CRT$XIZ")) _PIFV __xi_z[] = {0};

    // C++ initializers
    __declspec(allocate(".CRT$XCA")) _PVFV __xc_a[] = {0};
    __declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[] = {0};

    // C pre-terminators
    __declspec(allocate(".CRT$XPA")) _PVFV __xp_a[] = {0};
    __declspec(allocate(".CRT$XPZ")) _PVFV __xp_z[] = {0};

    // C terminators
    __declspec(allocate(".CRT$XTA")) _PVFV __xt_a[] = {0};
    __declspec(allocate(".CRT$XTZ")) _PVFV __xt_z[] = {0};
}

typedef struct __declspec(align(16)) _SLIST_ENTRY {
    struct _SLIST_ENTRY* Next;
} SLIST_ENTRY, *PSLIST_ENTRY;

typedef union __declspec(align(16)) _SLIST_HEADER {
    struct { // original struct
        unsigned long long Alignment;
        unsigned long long Region;
    } DUMMYSTRUCTNAME;
    struct { // x64 16-byte header
        unsigned long long Depth:16;
        unsigned long long Sequence:48;
        unsigned long long Reserved:4;
        unsigned long long NextEntry:60; // last 4 bits are always 0's
    } HeaderX64;
} SLIST_HEADER, *PSLIST_HEADER;
typedef struct _ON_EXIT_ENTRY {
    SLIST_ENTRY Entry;
    _PVFV func;
} ON_EXIT_ENTRY, *PON_EXIT_ENTRY;

SLIST_HEADER __onexithead;
char _CRT_CWD[260] = {0};

const char* _get_cwd() {
    return _CRT_CWD;
}

void _set_cwd(const char* path) {
    strncpy(_CRT_CWD, path, _countof(_CRT_CWD));
}

bool _init_cwd() {
    _set_cwd("C:\\WINDOWS\\System32");
    return true;
}

void _initterm(_PVFV* pfbegin, _PVFV* pfend) {
    /*
     * walk the table of function pointers from the bottom up, until
     * the end is encountered.  Do not skip the first entry.  The initial
     * value of pfbegin points to the first valid entry.  Do not try to
     * execute what pfend points to.  Only entries before pfend are valid.
     */
    while (pfbegin < pfend) {
        /*
         * if current table entry is non-NULL, call thru it.
         */
        if (*pfbegin != NULL)
            (**pfbegin)();
        ++pfbegin;
    }
}

void __stdcall RtlInitializeSListHead(PSLIST_HEADER);
PSLIST_ENTRY __stdcall RtlInterlockedPushEntrySList(PSLIST_HEADER, PSLIST_ENTRY);
PSLIST_ENTRY __stdcall RtlInterlockedPopEntrySList(PSLIST_HEADER);

void __cdecl _cinitfs(void) {
    _init_cwd();
}

int __cdecl _cinit( void )
{
    _cinitfs();
    LI_FN(RtlInitializeSListHead).nt_cached()(&__onexithead);
    _initterm(__xc_a, __xc_z);

    return 0;
}
_PVFV _onexit(_PVFV lpfn) {
    PON_EXIT_ENTRY _Entry = (PON_EXIT_ENTRY)malloc(sizeof(ON_EXIT_ENTRY));
    if (!_Entry)
        return NULL;

    _Entry->func = lpfn;
    LI_FN(RtlInterlockedPushEntrySList).nt_cached()(&__onexithead, &_Entry->Entry);
    return lpfn;
}

int __cdecl atexit(_PVFV func) {
    return (_onexit(func) == NULL) ? -1 : 0;
}

void doexit(int code, int quick, int retcaller) {
    if (!quick) {
        while (auto _Entry = LI_FN(RtlInterlockedPopEntrySList).nt_cached()(&__onexithead)) {
            PON_EXIT_ENTRY Entry = (PON_EXIT_ENTRY)_Entry;

            Entry->func();
            free(Entry);
        }
    }
}
void __cdecl _cexit(void) {
    doexit(0, 0, 1); /* full term, return to caller */
}
namespace std {
    _Prhand _Raise_handler;

    [[noreturn]] void __cdecl _Xlength_error(char const*) {
        while (true)
            ;
    }
    void __cdecl _Xbad_function_call(void) {
        while (true)
            ;
    }
    [[noreturn]] _CRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _Xout_of_range(_In_z_ const char*) {
        while (true)
            ;
    }
} // namespace std

void __std_exception_copy(const struct __std_exception_data* src, struct __std_exception_data* dst) { }
void __std_exception_destroy(struct __std_exception_data* data) { }

#if defined(__clang__)
extern "C" void __stdcall _CxxThrowException(void* pExceptionObject, class _ThrowInfo* pThrowInfo) { }
#endif

void abort(void) {
    while (true)
        ;
}

extern "C" void __cdecl _invalid_parameter(wchar_t const* const expression, wchar_t const* const function_name, wchar_t const* const file_name,
                                           unsigned int const line_number, uintptr_t const reserved) { }

extern "C" void __cdecl _invalid_parameter_noinfo(void) { }

extern "C" __declspec(noreturn) void __cdecl _invalid_parameter_noinfo_noreturn(void) {
    while (true)
        ;
}

extern "C" __declspec(noreturn) void __cdecl _invoke_watson(wchar_t const* const expression, wchar_t const* const function_name,
                                                            wchar_t const* const file_name, unsigned int const line_number, uintptr_t const reserved) {
    while (true)
        ;
}

extern "C" int __cdecl _purecall() {
    return 0;
}

short _dtest(double* px) {
    auto isinf_ = [](double x) -> bool {
        return std::abs(x) == std::numeric_limits<double>::infinity();
    };

    auto isnan_ = [](float x) -> bool {
        return x != x;
    };

    if (isnan_((float)*px)) {
        return _NANCODE;
    }
    if (isinf_((float)*px)) {
        return _INFCODE;
    }
    if (*px == 0.) {
        return _DENORM;
    }
    return _FINITE;
}

int _dsign(double x) {
    if (x < 0) {
        return -1;
    }
    return 0;
}

lconv* __cdecl localeconv(void) {
    static lconv conv;
    return &conv;
}
