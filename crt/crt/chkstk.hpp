#pragma once

namespace crt {
    __forceinline unsigned __int64 chkstk() {
#if defined(__clang__)
        __asm__ __volatile__("push   %rcx;"
                             "push   %rax;"
                             "cmp    $0x1000,%rax;"
                             "lea    24(%rsp),%rcx;"
                             "jb     1f;"
                             "2:"
                             "sub    $0x1000,%rcx;"
                             "test   %rcx,(%rcx);"
                             "sub    $0x1000,%rax;"
                             "cmp    $0x1000,%rax;"
                             "ja     2b;"
                             "1:"
                             "sub    %rax,%rcx;"
                             "test   %rcx,(%rcx);"
                             "pop    %rax;"
                             "pop    %rcx;"
                             "ret;");
#else
    // todo
#endif
    }
} // namespace crt::chkstk