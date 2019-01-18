#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "image.h"

int init_histo(PPMImage* img, PPMImage* histogramme);
void printHistogram(PPMImage* histogram, unsigned int* histogramData, unsigned int maxData, unsigned char printColor);

#endif 
