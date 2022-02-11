// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __VEC2__
#define __VEC2__

#include <pch.h>

template <class T>
struct Vec2;
template<typename T>
std::ostream& operator<<(std::ostream&, const Vec2<T>&);

template <class T>
struct Vec2
{
    T X;
    T Y;

    Vec2();
    Vec2(T x, T y);
    Vec2(const Vec2 & v);
    Vec2(const Vec2 & from, const Vec2 & to);
    Vec2(std::initializer_list<T> args);

    Vec2 & operator= (const Vec2 & v);

    bool operator== (const Vec2 & v);
    bool operator!= (const Vec2 & v);

    bool operator== (const T valeur);
    bool operator!= (const T valeur);

    Vec2 & operator+= (const Vec2 & v);
    Vec2 operator+ (const Vec2 & v) const;
    Vec2 operator+ (const T valeur);

    Vec2 & operator-= (const Vec2 & v);
    Vec2 operator- (const Vec2 & v) const;
    Vec2 operator- (const T valeur);

    Vec2 & operator*= (const T a);
    Vec2 operator* (const T a)const;
    friend Vec2 operator* (const T a, const Vec2 & v) { return Vec2<T>(v.X*a, v.Y*a); }

    Vec2 & operator* (const Vec2 &v);

    Vec2 & operator/= (const T a);
    Vec2 operator/ (const T a)const;

    bool operator< (const Vec2 &v);
    bool operator< (const T valeur);

    bool operator> (const Vec2 &v);
    bool operator> (const T valeur);

    bool operator<= (const Vec2 &v);
    bool operator<= (const T valeur);

    bool operator>= (const Vec2 &v);
    bool operator>= (const T valeur);

    Vec2 crossProduct(const Vec2 & v)const;
    double length()const;
    Vec2 & normalize();

    Vec2 COPY(const Vec2 &v);
    Vec2 DirectCopy();

    Vec2 SET(T x, T y);

    friend std::ostream & operator<<(std::ostream& target, const Vec2& source)
    {
        target << source.X << ", " << source.Y;
        return target;
    }

    Vec2 NEGATE();
    Vec2 NEGATEprecisely(bool x, bool y);

    double dot(Vec2 v);
};

#include "vec2.inl"

#endif // __VEC2__
