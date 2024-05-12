#include "vector3.h"

inline V3r operator+(V3r a, V3r b)
{
    V3r result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z + b.Z;

    return result;
}

inline V3r &operator+=(V3r &a, V3r b)
{
    a = a + b;
    return a;
}

inline V3r operator-(V3r a, V3r b)
{
    V3r result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;
    result.Z = a.Z - b.Z;

    return result;
}

inline V3r &operator-=(V3r &a, V3r b)
{
    a = a - b;
    return a;
}

inline V3r operator*(V3r a, int32 b)
{
    V3r result;
    result.X = a.X * b;
    result.Y = a.Y * b;
    result.Z = a.Z * b;

    return result;
}

inline V3r &operator*=(V3r &a, int32 b)
{
    a = a * b;
    return a;
}

inline V3r operator*(int32 a, V3r b)
{
    V3r result;
    result = b * a;
    return result;
}
