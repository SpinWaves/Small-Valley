#include "vec4.h"

template <class T>
Vec4<T>::Vec4()
{
    X = 0;
    Y = 0;
    Z = 0;
    W = 0;
}
template <class T>
Vec4<T>::Vec4(T x, T y, T z, T w)
{
    X = x;
    Y = y;
    Z = z;
    W = w;
}
template <class T>
Vec4<T>::Vec4(const Vec4<T> & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
}
template <class T>
Vec4<T>::Vec4(const Vec4 & from, const Vec4<T> & to)
{
    X = to.X - from.X;
    Y = to.Y - from.Y;
    Z = to.Z - from.Z;
    W = to.W - from.W;
}
template <class T>
Vec4<T>::Vec4(std::initializer_list<T> args)
{
    if(args.size() < 5)
    {
        switch(args.size())
        {
            case 1:
                X = *std::move(args.begin());
                Y = 0;
                Z = 0;
                W = 0;
            break;

            case 2:		
                X = *std::move(args.begin());
                Y = *std::move(args.begin() + 1);
                Z = 0;
                W = 0;
            break;

            case 3:
                X = *std::move(args.begin());
                Y = *std::move(args.begin() + 1);
                Z = *std::move(args.begin() + 2);
                W = 0;
            break;

            case 4:
                X = *std::move(args.begin());
                Y = *std::move(args.begin() + 1);
                Z = *std::move(args.begin() + 2);
                W = *std::move(args.begin() + 3);
            break;

            default: break;
        }
    }
    else
        std::cout << "Vec4 initializer contains too much arguments" << std::endl;
}

template <class T>
Vec4<T> & Vec4<T>::operator= (const Vec4<T> & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    W = v.W;
    return *this;
}
template <class T>
bool Vec4<T>::operator== (const Vec4<T> & v)
{
    if(X == v.X && Y == v.Y && Z == v.Z && W == v.W)
        return true;
    return false;
}
template <class T>
bool Vec4<T>::operator!= (const Vec4<T> & v)
{
    if(X != v.X && Y != v.Y && Z != v.Z && W != v.W)
        return true;
    return false;
}


template <class T>
bool Vec4<T>::operator== (const T valeur)
{
    if(X == valeur && Y == valeur && Z == valeur && W == valeur)
        return true;
    return false;
}
template <class T>
bool Vec4<T>::operator!= (const T valeur)
{
    if(X != valeur && Y != valeur && Z != valeur && W != valeur)
        return true;
    return false;
}
template <class T>
Vec4<T> & Vec4<T>::operator+= (const Vec4<T> & v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    W += v.W;
    return *this;
}
template <class T>
Vec4<T> Vec4<T>::operator+ (const Vec4<T> & v) const
{
    Vec4 t = *this;
    t += v;
    return t;
}
template <class T>
Vec4<T> Vec4<T>::operator+ (const T valeur)
{
    X += valeur;
    Y += valeur;
    Z += valeur;
    W += valeur;
    return *this;
}
template <class T>
Vec4<T> & Vec4<T>::operator-= (const Vec4<T> & v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    W -= v.W;
    return *this;
}
template <class T>
Vec4<T> Vec4<T>::operator- (const Vec4<T> & v) const
{
    Vec4 t = *this;
    t -= v;
    return t;
}
template <class T>
Vec4<T> Vec4<T>::operator- (const T valeur)
{
    X -= valeur;
    Y -= valeur;
    Z -= valeur;
    W -= valeur;
    return *this;
}
template <class T>
Vec4<T> & Vec4<T>::operator*= (const T a)
{
    X *= a;
    Y *= a;
    Z *= a;
    W *= a;
    return *this;
}
template <class T>
Vec4<T> Vec4<T>::operator* (const T a)const
{
    Vec4 t = *this;
    t *= a;
    return t;
}
template <class T>
Vec4<T> & Vec4<T>::operator* (const Vec4<T> &v)
{
    X *= v.X;
    Y *= v.Y;
    Z *= v.Z;
    W *= v.W;
    return *this;
}
template <class T>
Vec4<T> & Vec4<T>::operator/= (const T a)
{
    X /= a;
    Y /= a;
    Z /= a;
    W /= a;
    return *this;
}
template <class T>
Vec4<T> Vec4<T>::operator/ (const T a)const
{
    Vec4 t = *this;
    t /= a;
    return t;
}
template <class T>
bool Vec4<T>::operator< (const Vec4<T> &v)
{
    if(X < v.X && Y < v.Y && Z < v.Z && W < v.W)
        return true;
    return false;
}
template <class T>
bool Vec4<T>::operator< (const T valeur)
{
    if(X < valeur && Y < valeur && Z < valeur && W < valeur)
        return true;
    return false;
}



template <class T>
bool Vec4<T>::operator> (const Vec4<T> &v)
{
    if(X > v.X && Y > v.Y && Z > v.Z && W > v.W)
        return true;
    return false;
}
template <class T>
bool Vec4<T>::operator> (const T valeur)
{
    if(X > valeur && Y > valeur && Z > valeur && W > valeur)
        return true;
    return false;
}



template <class T>
bool Vec4<T>::operator<= (const Vec4<T> &v)
{
    if(X <= v.X && Y <= v.Y && Z <= v.Z && W <= v.W)
        return true;
    return false;
}
template <class T>
bool Vec4<T>::operator<= (const T valeur)
{
    if(X <= valeur && Y <= valeur && Z <= valeur && W <= valeur)
        return true;
    return false;
}



template <class T>
bool Vec4<T>::operator>= (const Vec4<T> &v)
{
    if(X >= v.X && Y >= v.Y && Z >= v.Z && W >= v.W)
        return true;
    return false;
}
template <class T>
bool Vec4<T>::operator>= (const T valeur)
{
    if(X >= valeur && Y >= valeur && Z >= valeur && W >= valeur)
        return true;
    return false;
}


template <class T>
Vec4<T> Vec4<T>::crossProduct(const Vec4<T> & v)const
{
    Vec4<T> t;
    t.X = Y*v.Z - Z*v.Y;
    t.Y = Z*v.X - X*v.Z;
    t.Z = X*v.Y - Y*v.X;
    t.W = 1;
    return t;
}
template <class T>
double Vec4<T>::length()const
{
    return sqrt(X*X + Y*Y + Z*Z + W*W);
}
template <class T>
Vec4<T> & Vec4<T>::normalize()
{
    (*this) /= length();
    return (*this);
}
template <class T>
Vec4<T> Vec4<T>::COPY(const Vec4 &v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    W = v.W;
    return *this;
}
template <class T>
Vec4<T> Vec4<T>::DirectCopy()
{
    Vec4<T> cop;
    cop.X = X;
    cop.Y = Y;
    cop.Z = Z;
    cop.W = W;
    return cop;
}
template <class T>
Vec4<T> Vec4<T>::SET(T x, T y, T z, T w)
{
    X = x;
    Y = y;
    Z = z;
    W = w;
    return *this;
}
template <class T>
Vec4<T> Vec4<T>::NEGATE()
{
    X = -X;
    Y = -Y;
    Z = -Z;
    W = -W;
    return *this;
}
template <class T>
Vec4<T> Vec4<T>::NEGATEprecisely(bool x, bool y, bool z, bool w)
{
    if(x) X = -X;
    if(y) Y = -Y;
    if(z) Z = -Z;
    if(w) W = -W;
    return *this;
}
template <class T>
double Vec4<T>::dot(Vec4<T> v)
{
    return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
}
