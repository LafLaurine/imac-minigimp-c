#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "image.h"
#include "pixel.h"

typedef struct Histogram{
	unsigned int rvb[256], min, max;
}Histogram;

void histogram(Histogram *h);
Histogram *HistoRVB(PPMImage *img, Histogram *histo);
#endif 
