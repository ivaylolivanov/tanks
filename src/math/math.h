#if !defined MATH
#include <cmath>

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

inline int32 CeilReal32ToInt32(real32 value)
{
    int32 result = 0;

    result = (int32)ceilf(value);

    return result;
}

#define MATH
#endif
