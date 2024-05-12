#include "vector2.h"

inline V2i operator+(V2i a, V2i b)
{
    V2i result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;

    return result;
}

inline V2i &operator+=(V2i &a, V2i b)
{
    a = a + b;
    return a;
}

inline V2i operator-(V2i a, V2i b)
{
    V2i result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;

    return result;
}

inline V2i &operator-=(V2i &a, V2i b)
{
    a = a - b;
    return a;
}

inline V2i operator*(V2i a, int32 b)
{
    V2i result;
    result.X = a.X * b;
    result.Y = a.Y * b;

    return result;
}

inline V2i &operator*=(V2i &a, int32 b)
{
    a = a * b;
    return a;
}

inline V2i operator*(int32 a, V2i b)
{
    V2i result;
    result.X = b.X * a;
    result.Y = b.Y * a;

    return result;
}

inline V2i operator*(V2i a, real32 b)
{
    V2i result;
    result.X = a.X * (int32)b;
    result.Y = a.Y * (int32)b;

    return result;
}

inline V2i &operator*=(V2i &a, real32 b)
{
    a = a * b;
    return a;
}

inline V2i operator*(real32 a, V2i b)
{
    V2i result;
    result.X = (int32)a * b.X;
    result.Y = (int32)a * b.Y;

    return result;
}

inline V2r operator+(V2r a, V2r b)
{
    V2r result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;

    return result;
}

inline V2r &operator+=(V2r& a, V2r b)
{
    a = a + b;
    return a;
}

inline V2r operator-(V2r a, V2r b)
{
    V2r result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;

    return result;
}

inline V2r &operator-=(V2r& a, V2r b)
{
    a = a + b;
    return a;
}

inline V2r operator*(V2r a, real32 b)
{
    V2r result;
    result.X = a.X * b;
    result.Y = a.Y * b;

    return result;
}

inline V2r &operator*=(V2r a, real32 b)
{
    a = a * b;
    return a;
}

inline V2r operator*(real32 a, V2r b)
{
    V2r result;
    result.X = a * b.X;
    result.Y = a * b.Y;

    return result;
}

inline V2r operator*(V2r a, int32 b)
{
    V2r result;
    result.X = a.X * b;
    result.Y = a.Y * b;

    return result;
}

inline V2r &operator*=(V2r &a, int32 b)
{
    a = a * b;
    return a;
}

inline V2r operator*(int32 a, V2r b)
{
    V2r result;
    result.X = a * b.X;
    result.Y = a * b.Y;

    return result;
}
