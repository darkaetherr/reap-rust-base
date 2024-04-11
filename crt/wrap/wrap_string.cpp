#include <crt.hpp>

#if !defined(__clang__)
    // #pragma function(wcsncat)
    #pragma function(wcslen)
    #pragma function(strlen)
    #pragma function(wcscpy)
    #pragma function(strcpy)
    #pragma function(strcmp)
    #pragma function(wcscmp)
// #pragma function(isdigit)
#endif

extern "C" {

    // char* strcat_s(char* dest, unsigned int len, const char* src) {
    //     return crt::tcscat_s(dest, len, src);
    // }

    // wchar_t* wcscat_s(wchar_t* dest, unsigned int len, const wchar_t* src) {
    //     return crt::tcscat_s(dest, len, src);
    // }

    // char* strncat(char* dest, const char* src, unsigned int len) {
    //     return crt::tcsncat(dest, src, len);
    // }

    int isdigit(int c) {
        return (c >= '0' && c <= '9');
    }

    wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, size_t len) {
        return crt::tcsncat(dest, src, static_cast<unsigned int>(len));
    }

    char const* strchr(const char* str, int ch) {
        return crt::tcschr(str, (char)ch);
    }

    const wchar_t* wcschr(const wchar_t* str, wchar_t ch) {
        return crt::tcschr(str, ch);
    }

    // char* strrchr(const char* str, char ch) {
    //     return crt::tcsrchr(str, ch);
    // }

    const wchar_t* wcsrchr(const wchar_t* str, wchar_t ch) {
        return crt::tcsrchr(str, ch);
    }

    const char* strstr(const char* str, const char* search) {
        return crt::tcsstr(str, search);
    }

    const wchar_t* wcsstr(const wchar_t* str, const wchar_t* search) {
        return crt::tcsstr(str, search);
    }

    char* strupr(char* str) {
        return crt::tcsupr(str);
    }

    wchar_t* wcsupr(wchar_t* str) {
        return crt::tcsupr(str);
    }

    char* strlwr(char* str) {
        return crt::tcslwr(str);
    }

    wchar_t* wcslwr(wchar_t* str) {
        return crt::tcslwr(str);
    }

    // char* strtok_s(char* str, char* match, char** context) {
    //     return crt::tcstok_s(str, match, context);
    // }

    wchar_t* wcstok_s(wchar_t* str, wchar_t const* match, wchar_t** context) {
        return nullptr; // crt::tcstok_s(str, match, context);
    }

    // char* strtok_context = nullptr;
    // char* strtok(char* str, char* match) {
    //     return crt::tcstok_s(str, match, &strtok_context);
    // }

    wchar_t* wcstok_context = nullptr;
    wchar_t* wcstok(wchar_t* str, wchar_t const* match, wchar_t** context) {
        return nullptr; // crt::tcstok_s(str, match, &wcstok_context);
    }

    // int strspn(char* str, char* chars) {
    //     return crt::tcsspn(str, chars);
    // }

    size_t wcsspn(const wchar_t* str, const wchar_t* chars) {
        return crt::tcsspn(str, chars);
    }

    // int strcspn(char* str, char* match) {
    //     return crt::tcscspn(str, match);
    // }

    size_t wcscspn(const wchar_t* str, const wchar_t* match) {
        return crt::tcscspn(str, match);
    }

    char* strncpy(char* dst, const char* src, size_t n) {
        return crt::tcsncpy(dst, src, n);
    }

    wchar_t* wcsncpy(wchar_t* dst, const wchar_t* src, size_t n) {
        return crt::tcsncpy(dst, src, n);
    }

    int strncmp(const char* s1, const char* s2, size_t n) {
        return crt::tcsncmp(s1, s2, n);
    }

    int wcsncmp(const wchar_t* s1, const wchar_t* s2, size_t n) {
        return crt::tcsncmp(s1, s2, n);
    }

    char* strcpy(char* dst, const char* src) {
        return crt::tcsncpy(dst, src, strlen(src));
    }

    wchar_t* wcscpy(wchar_t* dst, const wchar_t* src) {
        return crt::tcsncpy(dst, src, wcslen(src));
    }

    errno_t strcpy_s(char* dst, rsize_t dst_size, const char* src) {
        if (dst_size < strlen(src))
            return -1;

        crt::tcsncpy(dst, src, dst_size);

        return 0;
    }

    errno_t wcscpy_s(wchar_t* dst, rsize_t dst_size, const wchar_t* src) {
        if (dst_size < wcslen(src))
            return -1;

        crt::tcsncpy(dst, src, dst_size);

        return 0;
    }

    int strcmp(const char* s1, const char* s2) {
        return crt::tcscmp(s1, s2);
    }

    int wcscmp(const wchar_t* s1, const wchar_t* s2) {
        return crt::tcscmp(s1, s2);
    }

    size_t strlen(const char* string) {
        return crt::tcslen(string);
    }

    size_t wcslen(const wchar_t* string) {
        return crt::tcslen(string);
    }

    int islower(int value) {
        return crt::tcislower(value);
    }

    int isupper(int value) {
        return crt::tcisupper(value);
    }

    int toupper(int value) {
        return crt::tctoupper(value);
    }

    int tolower(int value) {
        return crt::tctolower(value);
    }

    int isspace(int value) {
        return crt::tcisspace(value);
    }

    int isalpha(int value) {
        return crt::tcisalpha(value);
    }

    double atof(const char* str) {
        return crt::tctof(str);
    }

    int atoi(const char* str) {
        return crt::atoi(str);
    }

    unsigned long strtoul(const char* ptr, char** end_ptr, int base) {
        return crt::strtoul(ptr, end_ptr, base);
    }

    long strtol(const char* ptr, char** end_ptr, int base) {
        return crt::strtol(ptr, end_ptr, base);
    }

    unsigned long long strtoull(const char* str, char** endptr, int base) {
        return crt::strtoull(str, endptr, base);
    }

    long long strtoll(const char* str, char** endptr, int base) {
        return crt::strtoll(str, endptr, base);
    }

    double strtod(const char* str, char** endptr) {
        return crt::strtod(str, endptr);
    }
}
