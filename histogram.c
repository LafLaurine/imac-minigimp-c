#include <stdlib.h>
#include <stdio.h>
#include "histogram.h"
#include "pixel.h"
#include "image.h"

void histogram(Histogram *h)
{
	size_t i;
	for (h->min=sizeof(unsigned int), h->max=0, i=0;i<256;++i)
	{
		if(h->rvb[i]>h->max)
		{
			h->max = h->rvb[i];
		}

		if(h->rvb[i]<h->min)
		{
			h->min = h->rvb[i];
		}
	}
}

Histogram *HistoRVB(PPMImage *img, Histogram *histo)
{
	size_t x,y,somme;
	int i = 0;
	memset(histo,0,sizeof(Histogram));
	for(y= 0; y<img->height; ++y)
	{
		for(x=0; x<img->width;++x)
		{
			i++;
			somme = img->rvb[i].r + img->rvb[i].v + img->rvb[i].b;
			++(histo->rvb[(unsigned int)(somme/3.f)]);
		}
	}
	histogram(histo);
	return histo;
}
