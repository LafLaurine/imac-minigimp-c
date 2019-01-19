#include <stdlib.h>
#include <stdio.h>
#include "conversion.h"

//Read through an image to apply a simple LUT
void appliquerLUT(PPMImage *img, LUT *lut) {
    for(int i = 0 ; i< img->width*img->height; i++) {
        img->rvb[i].r = lut->table[img->rvb[i].r];
        img->rvb[i].v = lut->table[img->rvb[i].v];
        img->rvb[i].b = lut->table[img->rvb[i].b];
    }
}

//Read through an image to apply a LUT that needs to check independant channel
void appliquerLUTChannel(PPMImage *img, LUT3D *lut3D, unsigned char pixel) {
    for(int i = 0 ; i< img->width*img->height; i++) 
    {
        if(pixel == 'r')
        {
            img->rvb[i].r = lut3D->r[img->rvb[i].r];

        }

        else if(pixel == 'v')
        {
            img->rvb[i].v = lut3D->v[img->rvb[i].v];

        }

        else if(pixel == 'b')
        {
            img->rvb[i].b = lut3D->b[img->rvb[i].b];

        }

    }
}


//Apply 3D LUT
void appliquerLUT3D(PPMImage *img, LUT3D *lut3D) {
    for(int i = 0 ; i< img->width*img->height; i++) {
        int avg = 0.3 * img->rvb[i].r + 0.59 * img->rvb[i].v + 0.11 * img->rvb[i].b;
        img->rvb[i].r = lut3D->r[avg];
        img->rvb[i].v = lut3D->v[avg];
        img->rvb[i].b = lut3D->b[avg];
    }
}

//COnvert greyScaleale to RGB
void greyScaleToRGB (LUT* lut, PPMImage *image)
{
    for(int i =0; i<image->width*image->height; i++)
    {
        //test if rvb > lut to avoid negative values
        if(lut->table[image->greyScale[i]] > image->rvb[i].r)
        {
            image->rvb[i].r = lut->table[image->greyScale[i]] - image->rvb[i].r;   
        }

        else
        {
            image->rvb[i].r = image->rvb[i].r - lut->table[image->greyScale[i]];
        }

        if(lut->table[image->greyScale[i]] > image->rvb[i].v)
        {
            image->rvb[i].v = lut->table[image->greyScale[i]] - image->rvb[i].v;   
        }

        else
        {
            image->rvb[i].v = image->rvb[i].v - lut->table[image->greyScale[i]];
        }

        if(lut->table[image->greyScale[i]] > image->rvb[i].b)
        {
            image->rvb[i].b = lut->table[image->greyScale[i]] - image->rvb[i].b;   
        }

        else
        {
            image->rvb[i].b = image->rvb[i].b - lut->table[image->greyScale[i]];
        }
    }
}