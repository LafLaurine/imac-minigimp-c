#ifndef CHARGERIMG_H
#define CHARGERIMG_H
#include<stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct PPMImage {
	int width;
	int height;
	unsigned char *rvb;
} PPMImage;

static unsigned char tab_pixel[3];

static inline unsigned char *pixel_r(const PPMImage *img,size_t x, size_t y)
{
	if (x>=img->width || y>=img->height)
	{
		memset(tab_pixel,0,3);
		return tab_pixel;
	}
	return img->rvb+3*(img->width*y+x);
}

static inline unsigned char *pixel_v(const PPMImage *img,size_t x, size_t y)
{
	return pixel_r(img,x,y)+1;
}


static inline unsigned char *pixel_b(const PPMImage *img,size_t x, size_t y)
{
	return pixel_r(img,x,y)+2;
}

void errorMsg(char *message);
void readPPMHeader(FILE* fp, int *w, int*h);
int allocate(PPMImage *newImg, int width, int height);
void desallocate(PPMImage *img);
PPMImage * ImageRead(char *filename);
void IMG_remplir(PPMImage *img, unsigned char r, unsigned char v, unsigned char b);
void ImageExport(PPMImage *image, char *filename);
int ImageWidth(PPMImage *image);
int ImageHeight(PPMImage *image);
#endif