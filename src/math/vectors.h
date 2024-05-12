#if !defined VECTORS

#include "vector2.cpp"
#include "vector3.cpp"
#include "vector4.cpp"

inline V2r V2rZero()
{
    V2r zero = { 0, 0 };
    return zero;
}

inline V2i V2iZero()
{
    V2i zero = { 0, 0 };
    return zero;
}

inline V3r V3rZero()
{
    V3r zero = { 0, 0, 0 };
    return zero;
}

inline V4r V4rZero()
{
    V4r zero = { 0, 0, 0, 0 };
    return zero;
}

inline V2r operator+(V2r a, V2i b)
{
    V2r result;
    result.X = a.X + (real32)b.X;
    result.Y = a.Y + (real32)b.Y;

    return result;
}

inline V2r operator+(V2i a, V2r b)
{
    V2r result;
    result = b + a;
    return result;
}

inline V3r operator+(V3r a, V2r b)
{
    V3r result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z;

    return result;
}

inline V3r operator+(V2r a,V3r b)
{
    V3r result;
    result.X = b.X + a.X;
    result.Y = b.Y + a.Y;
    result.Z = b.Z;

    return result;
}

inline V3r operator+(V3r a, V2i b)
{
    V3r result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z;

    return result;
}

inline V3r operator+(V2i a, V3r b)
{
    V3r result;
    result.X = b.X + a.X;
    result.Y = b.Y + a.Y;
    result.Z = b.Z;

    return result;
}

/* inline V3i operator+(V3r a, V2i b) */
/* { */
/*     V3i result; */
/*     result.X = (int32)(a.X + b.X); */
/*     result.Y = (int32)(a.Y + b.Y); */
/*     result.Z = (int32)a.Z; */

/*     return result; */
/* } */

/* inline V3i operator+(V2i a, V3r b) */
/* { */
/*     V3i result; */
/*     result.X = (int32)(b.X + a.X); */
/*     result.Y = (int32)(b.Y + a.Y); */
/*     result.Z = (int32)b.Z; */

/*     return result; */
/* } */

/* inline V3i operator+(V3i a, V2r b) */
/* { */
/*     V3i result; */
/*     result.X = (int32)(a.X + b.X); */
/*     result.Y = (int32)(a.Y + b.Y); */
/*     result.Z = (int32)a.Z; */

/*     return result; */
/* } */

/* inline V3i operator+(V2r a, V3i b) */
/* { */
/*     V3i result; */
/*     result.X = (int32)(b.X + a.X); */
/*     result.Y = (int32)(b.Y + a.Y); */
/*     result.Z = (int32)b.Z; */

/*     return result; */
/* } */

/* inline V3i operator+(V3i a, V2i b) */
/* { */
/*     V3i result; */
/*     result.X = a.X + b.X; */
/*     result.Y = a.Y + b.Y; */
/*     result.Z = a.Z; */

/*     return result; */
/* } */

/* inline V3i operator+(V2i a, V3i b) */
/* { */
/*     V3i result; */
/*     result.X = b.X + a.X; */
/*     result.Y = b.Y + a.Y; */
/*     result.Z = b.Z; */

/*     return result; */
/* } */

#define VECTORS
#endif
