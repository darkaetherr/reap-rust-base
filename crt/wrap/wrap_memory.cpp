#include <crt.hpp>
#include <obfy/lazy_importer.hpp>
    #if !defined(__clang__)
        #pragma function(memchr)
        #pragma function(memcpy)
        #pragma function(memmove)
        #pragma function(memcmp)
        #pragma function(memset)
    #endif

typedef struct _MALLOC_HEADER {
    unsigned int Magic;
    unsigned int _Resv0;
    unsigned long long Size;
} MALLOC_HEADER, *PMALLOC_HEADER;

#define GET_MALLOC_ADDRESS(header) (void*)((unsigned char*)header + sizeof(MALLOC_HEADER))
#define GET_MALLOC_HEADER(ptr) ((MALLOC_HEADER*)((unsigned char*)ptr - sizeof(MALLOC_HEADER)))
#define GET_MALLOC_SIZE(ptr) GET_MALLOC_HEADER(ptr)->Size
#define MALLOC_MAGIC 'MIGC'
#define M_GETPEB __readgsqword(0x60)
#define M_PROCESSHEAP *reinterpret_cast<void**>(__readgsqword(0x60) + 0x30)

#define EXCEPTION_MAXIMUM_PARAMETERS 15 // maximum number of exception parameters

//
// Exception record definition.
//

typedef struct _EXCEPTION_RECORD {
    unsigned long ExceptionCode;
    unsigned long ExceptionFlags;
    struct _EXCEPTION_RECORD* ExceptionRecord;
    void* ExceptionAddress;
    unsigned long NumberParameters;
    unsigned long long ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD;

typedef EXCEPTION_RECORD* PEXCEPTION_RECORD;

const void* memchr(const void* src, int chr, size_t len) {
    return crt::memchr(src, chr, len);
}

void* memcpy(void* dst, const void* src, size_t len) {
    return crt::memcpy(dst, src, len);
}

void* memmove(void* dst, const void* src, size_t len) {
    return crt::memmove(dst, src, len);
}

int memcmp(const void* buf1, const void* buf2, size_t len) {
    return crt::memcmp(buf1, buf2, len);
}

void* memset(void* dst, int val, size_t len) {
    return crt::memset(dst, val, len);
}

void* __stdcall RtlAllocateHeap(void*, unsigned long, size_t);
void* __stdcall RtlFreeHeap(void*, unsigned long, void*);
void __stdcall RtlRaiseException(PEXCEPTION_RECORD);

void* malloc(size_t size) {
    PMALLOC_HEADER mhdr = NULL;
    const size_t new_size = size + sizeof(MALLOC_HEADER);

    mhdr = (PMALLOC_HEADER)LI_FN(RtlAllocateHeap).nt_cached()(M_PROCESSHEAP, 0x00000008, new_size);
    if (mhdr)
    {
        mhdr->Magic = MALLOC_MAGIC;
        mhdr->Size = size;
        return GET_MALLOC_ADDRESS(mhdr);
    }
    return nullptr;
}

void* realloc(void* block, size_t size) {
    if (!block)
        return malloc(size);
    else if (size == 0) {
        free(block);
        return nullptr;
    }
    else
    {
        size_t old_size = GET_MALLOC_SIZE(block);
        if (size <= old_size)
            return block;
        else
        {
            void* new_ptr = malloc(size);
            if (new_ptr)
            {
                memcpy(new_ptr, block, old_size);
                free(block);
                return new_ptr;
            }
        }
    }
    return nullptr;
}

void free(void* block) {
    LI_FN(RtlFreeHeap).nt_cached()(M_PROCESSHEAP, 0, GET_MALLOC_HEADER(block));
}

void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept {
    free(ptr);
}
