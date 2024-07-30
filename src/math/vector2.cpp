#include "vector2.h"

inline void Normalize(V2i& vector)
{
    int32 lenght = (int32)sqrt(vector.X * vector.X + vector.Y * vector.Y);
    vector.X /= lenght;
    vector.Y /= lenght;
}

inline int32 DotProduct(V2i a, V2i b)
{
    int32 result = a.X * b.X + a.Y & b.Y;
    return result;
}

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
    result.X = (int32)(a.X * b);
    result.Y = (int32)(a.Y * b);

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

inline bool32 operator!=(V2i a, V2i b)
{
    bool32 result = false;

    result = (a.X != b.X) && (a.Y != b.Y);

    return result;
}

inline bool32 operator==(V2i a, V2i b)
{
    bool32 result = false;

    result = (a.X == b.X) && (a.Y == b.Y);

    return result;
}

inline void Normalize(V2r& vector)
{
    real32 lenght = (real32) sqrt(vector.X * vector.X + vector.Y * vector.Y);
    vector.X /= lenght;
    vector.Y /= lenght;
}

inline real32 DotProduct(V2r a, V2r b)
{
    real32 result = a.X * b.X + a.Y * b.Y;
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
    a = a - b;
    return a;
}

inline V2r operator*(V2r a, real32 b)
{
    V2r result;
    result.X = a.X * b;
    result.Y = a.Y * b;

    return result;
}

inline V2r &operator*=(V2r &a, real32 b)
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

inline bool32 operator!=(V2r a, V2r b)
{
    bool32 result = false;

    result = (a.X != b.X) && (a.Y != b.Y);

    return result;
}

inline bool32 operator==(V2r a, V2r b)
{
    bool32 result = false;

    real32 epsilon = 0.001f;

    result = (abs(a.X - b.X) <= epsilon)
        && (abs(a.Y - b.Y) <= epsilon);

    return result;
}
