#pragma once
#include "crt/crt.hpp"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    int __cdecl _cinit(void);
    void __cdecl _cexit(void);
    void __cdecl _cinitfs(void);

    typedef void(__cdecl* _PVFV)(void);
    typedef int(__cdecl* _PIFV)(void);

    int __cdecl atexit(_PVFV func);

#ifdef __cplusplus
}
#endif // __cplusplus