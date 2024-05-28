#if !defined MATH

inline void ClampInt32(int32& value, int32 min, int32 max)
{
    if (value < min)
        value = min;
    if (value > max)
        value = max;
}

inline void ClampUInt32(uint32& value, uint32 min, uint32 max)
{
    if (value < min)
        value = min;
    if (value > max)
        value = max;
}

inline void ClampReal32(real32& value, real32 min, real32 max)
{
    if (value < min)
        value = min;
    if (value > max)
        value = max;
}

#define MATH
#endif
