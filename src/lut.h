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

/*
int init_LUTs(LUT* lut);
int clear_LUTs(LUT *lut);*/
void init(LUT *lut);
void init3D(LUT3D *lut3D);


void sepia(LUT3D *lut3D);
void seuil(LUT3D *lut3D, int param);
void addPixel(LUT3D *lut3D, int param, unsigned char pixel);
void tint(LUT3D *lut3D, int kelvin);
void blacknwh(LUT3D *lut3D);

void invert_table(LUT *lut);
void addLum(LUT *lut, int param);
void dimLum(LUT *lut, int param);
void addCon(LUT *lut, int param);
void dimCon(LUT *lut,int param);
void ln(LUT *lut, int param);

#endif /* LUT_H */