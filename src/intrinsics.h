#include <cmath>
#if !defined INTRINSICS

#if !defined(COMPILER_CL)
#define COMPILER_CL 0
#endif

#if !defined(COMPILER_LLVM)
#define COMPILER_LLVM 0
#endif

#if !COMPILER_CL && !COMPILER_LLVM
#if _MSC_VER
#undef COMPILER_CL
#define COMPILER_CL 1
#else
#undef COMPILER_LLVM
#define COMPILER_LLVM 1
#endif
#endif

#if COMPILER_CL
#include <intrin.h>
#elif COMPILER_LLVM
#include <x86intrin.h>
#else
#error SEE/NEON No intrinsics implementations for this compiler!
#endif

inline int32 RoundReal32ToInt32(real32 real)
{
    int32 result = _mm_cvtss_si32(_mm_set_ss(real));
    return result;
}

inline int32 FloorReal32ToInt32(real32 real)
{
    int32 result = _mm_cvtss_si32(
        _mm_floor_ss(_mm_setzero_ps(), _mm_set_ss(real)));
    return result;
}

inline uint32 RoundReal32ToUInt32(real32 real)
{
    int32 result = (uint32)_mm_cvtss_si32(_mm_set_ss(real));;
    return result;
}

inline int32 TruncateReal32ToInt32(real32 real)
{
    int32 result = (int32)real;
    return result;
}

inline real32 Sin(real32 angle)
{
    real32 result = sinf(angle);
    return result;
}

inline real32 Cos(real32 angle)
{
    real32 result = cosf(angle);
    return result;
}

inline real32 ATan2(real32 y, real32 x)
{
    real32 result = atan2(y, x);
    return result;
}

#define INTRINSICS
#endif
