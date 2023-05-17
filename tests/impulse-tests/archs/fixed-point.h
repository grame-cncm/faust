
// Code for -fx mode
#include "ap_fixed.h"

typedef ap_fixed<32, 8, AP_RND_CONV, AP_SAT> fixpoint_t;

// fx version
inline fixpoint_t fabsfx(fixpoint_t x)
{
    return fixpoint_t(std::fabs(float(x)));
}
inline fixpoint_t acosfx(fixpoint_t x)
{
    return fixpoint_t(std::acos(float(x)));
}
inline fixpoint_t asinfx(fixpoint_t x)
{
    return fixpoint_t(std::asin(float(x)));
}
inline fixpoint_t atanfx(fixpoint_t x)
{
    return fixpoint_t(std::atan(float(x)));
}
inline fixpoint_t atan2fx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::atan2(float(x), float(y)));
}
inline fixpoint_t ceilfx(fixpoint_t x)
{
    return fixpoint_t(std::ceil(float(x)));
}
inline fixpoint_t cosfx(fixpoint_t x)
{
    return fixpoint_t(std::cos(float(x)));
}
inline fixpoint_t expfx(fixpoint_t x)
{
    return fixpoint_t(std::exp(float(x)));
}
inline fixpoint_t exp2fx(fixpoint_t x)
{
    return fixpoint_t(std::exp2(float(x)));
}
inline fixpoint_t exp10fx(fixpoint_t x)
{
#ifdef __APPLE__
    return fixpoint_t(__exp10f(float(x)));
#else
    return fixpoint_t(std::exp10(float(x)));
#endif
}
inline fixpoint_t floorfx(fixpoint_t x)
{
    return fixpoint_t(std::floor(float(x)));
}
inline fixpoint_t fmodfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::fmod(float(x), float(y)));
}
inline fixpoint_t logfx(fixpoint_t x)
{
    return fixpoint_t(std::log(float(x)));
}
inline fixpoint_t log2fx(fixpoint_t x)
{
    return fixpoint_t(std::log2(float(x)));
}
inline fixpoint_t log10fx(fixpoint_t x)
{
    return fixpoint_t(std::log10(float(x)));
}
inline fixpoint_t powfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::pow(float(x), float(y)));
}
inline fixpoint_t remainderfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::remainder(float(x), float(y)));
}
inline fixpoint_t rintfx(fixpoint_t x)
{
    return fixpoint_t(std::rint(float(x)));
}
inline fixpoint_t roundfx(fixpoint_t x)
{
    return fixpoint_t(std::round(float(x)));
}
inline fixpoint_t sinfx(fixpoint_t x)
{
    return fixpoint_t(std::sin(float(x)));
}
inline fixpoint_t sqrtfx(fixpoint_t x)
{
    return fixpoint_t(std::sqrt(float(x)));
}
inline fixpoint_t tanfx(fixpoint_t x)
{
    return fixpoint_t(std::tan(float(x)));
}
// min/max
inline fixpoint_t fminfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::min(float(x), float(y)));
}
inline fixpoint_t fmaxfx(fixpoint_t x, fixpoint_t y)
{
    return fixpoint_t(std::max(float(x), float(y)));
}
