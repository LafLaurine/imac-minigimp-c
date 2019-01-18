#ifndef LUT_H
#define LUT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct LUT
{
	unsigned char table[256];
	//LUT *previous, *next;
}LUT;


typedef struct LUT3D{
	unsigned char r[256];
	unsigned char v[256];
	unsigned char b[256];
}LUT3D;

int init_LUTs(LUT* lut);
int clear_LUTs(LUT *lut);

LUT3D sepia();
LUT3D seuil(int param);
LUT3D blacknwh();
LUT3D tint(int kelvin);
LUT3D addPixel(int param, unsigned char pixel);
LUT invert_table();
LUT addLum(int param);
LUT dimLum(int param);
LUT addCon(int param);
LUT dimCon(int param);
#endif /* LUT_H */