#ifndef __MATHS__
#define __MATHS__

#include <pch.h>

inline int randint(int a, int b) { return rand() % (b - a) + a; }
bool rand_probability(double proba);
float rsqrt(float number);

// Better implementation of abs function
inline int __abs(int a) noexcept
{
    int mask = (a >> (sizeof(int) * CHAR_BIT - 1));
    return (a + mask) ^ mask;
}

double __cos(double x) noexcept;

#endif // __MATHS__
