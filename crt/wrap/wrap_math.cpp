#include <crt.hpp>

#if !defined(__clang__)
    #pragma function(sin)
    #pragma function(cos)
    #pragma function(cosf)
    #pragma function(sinf)
    #pragma function(acosf)
    #pragma function(asinf)
    #pragma function(sqrtf)
    #pragma function(tan)
    #pragma function(_dtest)
    #pragma function(tanf)
    #pragma function(atanf)
    #pragma function(floor)
    #pragma function(ceil)
    #pragma function(floorf)
    #pragma function(ceilf)
    #pragma function(fmodf)
    #pragma function(atan2f)
    #pragma function(logf)
    #pragma function(expf)
    #pragma function(powf)
    #pragma function(pow)
    #pragma function(fabs)
#endif

extern "C" {
    double fabs(double x) {
        return (x < 0.0) ? -x : x;
    }

    double sin(double x) {
        return crt::math::sin(x);
    }

    double cos(double x) {
        return crt::math::cos(x);
    }

    float cosf(float x) {
        return crt::math::cosf(x);
    }

    float sinf(float x) {
        return crt::math::sinf(x);
    }

    float acosf(float x) {
        return crt::math::acosf(x);
    }

    float asinf(float x) {
        return crt::math::asinf(x);
    }

    float sqrtf(float x) {
        return crt::math::sqrt(x);
    }

    double tan(double x) {
        return crt::math::tan(x);
    }

    float tanf(float x) {
        return crt::math::tanf(x);
    }

    float atanf(float x) {
        return crt::math::atanf(x);
    }

    double round(double x) {
        return crt::math::round(x);
    }

    double floor(double x) {
        return crt::math::floor(x);
    }

    double ceil(double x) {
        return crt::math::ceil(x);
    }

    double trunc(double x) {
        return crt::math::trunc(x);
    }

    float roundf(float x) {
        return crt::math::round(x);
    }

    float floorf(float x) {
        return crt::math::floor(x);
    }

    float ceilf(float x) {
        return crt::math::ceil(x);
    }

    float truncf(float x) {
        return crt::math::trunc(x);
    }

    float fmodf(float x, float y) {
        return crt::math::modf(x, y);
    }

    float atan2f(float a, float b) {
        return crt::math::atan2f(a, b);
    }

    float logf(float x) {
        return crt::math::logf(x);
    }

    float expf(float x) {
        return crt::math::expf(x);
    }

    float exp2f(float x) {
        return crt::math::exp2f(x);
    }

    float powf(float a, float b) {
        return crt::math::powf(a, b);
    }

    double pow(double a, double b) {
        return crt::math::pow(a, b);
    }
}
