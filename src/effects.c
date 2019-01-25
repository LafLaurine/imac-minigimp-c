#include <stdlib.h>
#include <stdio.h>
#include "effects.h"

void blacknwh(PPMImage *img)
{
    for(int i=0; i<img->width*img->height; i++) 
    {
       int avg = (img->rvb[i].r + img->rvb[i].v + img->rvb[i].b) / 3;
       img->rvb[i].r = img->rvb[i].v = img->rvb[i].b = avg;
    }
}

void bruit(PPMImage *img, int param)
{
    param = (rand()*(param/2 - (-param/2))/RAND_MAX) + (-param/2);
    for(int i=0; i<img->width*img->height; i++)
    {
        img->rvb[i].r = img->rvb[i].r + param;
        img->rvb[i].v = img->rvb[i].v +param;
        img->rvb[i].b = img->rvb[i].b + param;
    }
}

void swap(PPMImage *img)
{
	PPMImage copied;
	allocate(&copied, img->width, img->height);

	for(int i=0; i<img->width*img->height; i++)
    {
        copied.rvb[i].r = img->rvb[i].r;
       	copied.rvb[i].v = img->rvb[i].v;
        copied.rvb[i].b = img->rvb[i].b;
    }

    for(int i=0; i<(img->height); i++)
    {
    	for(int j=0; j<(img->width); j++)
    	{
    		img->rvb[(img->height-1-i)*(img->width)+j].r = copied.rvb[i*(img->width)+j].r;
    		img->rvb[(img->height-1-i)*(img->width)+j].v = copied.rvb[i*(img->width)+j].v;
    		img->rvb[(img->height-1-i)*(img->width)+j].b = copied.rvb[i*(img->width)+j].b;

    	}
    }

}