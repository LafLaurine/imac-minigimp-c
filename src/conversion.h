#ifndef CONVERSION_H
#define CONVERSION_H

#include "image.h"
#include "lut.h"

void appliquerLUT(PPMImage *img, LUT *lut);
void greyScaleToRGB3D (LUT3D* lut3D, PPMImage *image);
void appliquerLUT3D(PPMImage *img, LUT3D *lut3D);
void greyScaleToRGB (LUT* lut, PPMImage *image);
void appliquerLUTChannel(PPMImage *img, LUT3D *lut, unsigned char pixel);
#endif