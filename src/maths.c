#include "extras_math.h"

U8 clampU8(U8 value, U8 min, U8 max)
{
    return value > max ? max : value < min ? min : value;
}