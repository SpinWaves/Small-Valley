#include "maths.h"

bool rand_probability(double proba)
{
    if(proba < 1)
        return ((double)rand() / (double)RAND_MAX < proba);
    else if(proba >= 1)
        return true;
    return false;
}

float rsqrt(float number)
{
    long i = 0;
    float x2 = 0.0f;
    float y = 0;
    const float threehalfs = 1.5f;   // Quake III algorithm

    x2 = number * 0.5f;
    y = number;
    i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));
    #ifdef MATHS_EXTRA_PRECISION
        y = y * (threehalfs - (x2 * y * y));
    #endif

    return y;
}

double __cos(double x) noexcept
{
    constexpr double tp = 1./(2.*M_PI);
    x *= tp;
    x -= double(.25) + std::floor(x + double(.25));
    x *= double(16.) * (std::abs(x) - double(.5));
    
    #ifdef MATHS_EXTRA_PRECISION
        x += double(.225) * x * (std::abs(x) - double(1.));
    #endif
    
    return x;
}
