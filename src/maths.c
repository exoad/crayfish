#include "extras_math.h"

U8 clampU8(U8 value, U8 min, U8 max)
{
    return value > max ? max : value < min ? min : value;
}

F32 clampF32(F32 value, F32 min, F32 max)
{
    return value > max ? max : value < min ? min : value;
}