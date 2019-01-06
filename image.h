#ifndef CHARGERIMG_H
#define CHARGERIMG_H
#include<stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include "pixel.h"
#include <ctype.h>

typedef struct PPMImage {
	int width;
	int height;
	Pixel *rvb;
} PPMImage;


void errorMsg(char *message);
void readPPMHeader(FILE* fp, int *w, int*h);
int allocate(PPMImage *newImg, int width, int height);
void clear(PPMImage *img);
int imageRead(PPMImage *image, char *filename);
int ImageSave(PPMImage *image, char *filename);
#endif