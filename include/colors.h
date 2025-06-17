#ifndef __JM_COLORS_H__
#define __JM_COLORS_H__

// https://rgbcolorpicker.com/565

#define COLOR_BLACK (0x00000000)
#define COLOR_WHITE (0xffff)
#define COLOR_GREEN (0x00ff00ff)
#define COLOR_RED (0xFF0000ff)
#define COLOR_BLUE (0x00ff)

#include "def.h"

U16 convertToRGB565(U32 color);

#endif