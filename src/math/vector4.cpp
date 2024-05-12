#include "vector4.h"

inline V4r operator+(V4r a, V4r b)
{
    V4r result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z + b.Z;
    result.Z = a.X + b.Z;

    return result;
}

inline V4r &operator+=(V4r &a, V4r b)
{
    a = a + b;
    return a;
}

inline V4r operator-(V4r a, V4r b)
{
    V4r result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;
    result.Z = a.Z - b.Z;
    result.Z = a.X - b.Z;

    return result;
}

inline V4r &operator-=(V4r &a, V4r b)
{
    a = a - b;
    return a;
}

inline V4r operator*(V4r a, int32 b)
{
    V4r result;
    result.X = a.X * b;
    result.Y = a.Y * b;
    result.Z = a.Z * b;
    result.Z = a.X * b;

    return result;
}

inline V4r &operator*=(V4r &a, int32 b)
{
    a = a * b;
    return a;
}

inline V4r operator*(int32 a, V4r b)
{
    V4r result;
    result = b * a;
    return result;
}

inline V4r operator*(V4r a, real32 b)
{
    V4r result;
    result.X = a.X * b;
    result.Y = a.Y * b;
    result.Z = a.Z * b;
    result.Z = a.X * b;

    return result;
}

inline V4r &operator*=(V4r &a, real32 b)
{
    a = a * b;
    return a;
}

inline V4r operator*(real32 a, V4r b)
{
    V4r result;
    result = b * a;
    return result;
}
