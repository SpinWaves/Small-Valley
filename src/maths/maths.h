#ifndef __MATHS__
#define __MATHS__

#include <pch.h>

int randint(int a, int b);
bool rand_probability(double proba);
float rsqrt(float number);

// Better implementation of abs function
template <typename T = double>
T __abs(T a)
{
    T mask = (a >> (sizeof(T) * CHAR_BIT - 1));
    return (a + mask) ^ mask;
}

#endif // __MATHS__
