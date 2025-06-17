#include "colors.h"

U16 convertToRGB565(U32 color)
{
    return (((color >> 16) & 0xFF >> 3) << 11) | (((color >> 8) & 0xFF >> 2) << 5) | (color & 0xFF >> 3);
}