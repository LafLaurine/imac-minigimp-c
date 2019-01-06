#ifndef LUT_H
#define LUT_H

#include <stdint.h>
#include <stdbool.h>
#include "pixel.h"

typedef struct LUT LUT;
struct LUT {
	int size;
    Pixel *rvb;
    LUT *previous, *next;
};

void init(LUT* lut, Pixel* pxl, int height, int width);
LUT* copy(LUT* lut);
LUT* invert(LUT *lut);
LUT* addLum(LUT *lut, int param);
LUT* dimLum(LUT *lut, int param);
LUT* addCon(LUT *lut, int param);
LUT* dimCon(LUT *lut, int param);
LUT* augmentationR(LUT *lut, int param);
LUT* augmentationV(LUT *lut, int param);
LUT* augmentationB(LUT *lut, int param);
LUT* seuil(LUT *lut);
LUT* sepia(LUT *lut);
LUT *saveLUT(LUT* lut);
#endif /* LUT_H */