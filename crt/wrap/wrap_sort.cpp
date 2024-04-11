#include <crt.hpp>

extern "C" void qsort(void* array, size_t array_size, size_t elem_size, int (*compare)(const void*, const void*)) {
    return crt::qsort(array, array_size, elem_size, compare);
}
