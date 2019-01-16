#include <stdlib.h>
#include <stdio.h>
#include "histogram.h"

//histo de la moyenne des 3 composantes
int init_histo(PPMImage* img, PPMImage* histogramme) {
	unsigned int greyscale[256] = { 0 };
	unsigned int pixelAvgBrightness = 0;
    unsigned int maxPixels = 0;
    for (unsigned int x = 0; x < img->width; x++) {
        for (unsigned int y = 0; y < img->height; y++) {
                pixelAvgBrightness += img->rvb[x].r + img->rvb[x].v + img->rvb[x].b + img->rvb[y].r + img->rvb[y].v + img->rvb[y].b;
                pixelAvgBrightness = pixelAvgBrightness/3;
                greyscale[(unsigned char) pixelAvgBrightness] += 1;
            if (greyscale[(unsigned char) pixelAvgBrightness] > maxPixels) {
                maxPixels = greyscale[(unsigned char) pixelAvgBrightness];
            }
            pixelAvgBrightness = 0;

            }
            
        }
            _printHistogram(histogramme, greyscale, maxPixels, 200);

    
    return EXIT_SUCCESS;
}

void _printHistogram(PPMImage* histogram, unsigned int* histogramData, unsigned int maxData, unsigned char printColor) {
  
    if (histogram->width != 256) {
        printf("_printHistogram error: histogram needs to be 256px large");
        exit(EXIT_FAILURE);
    }

    for (unsigned int y = 0; y < histogram->width; y++) {
        long columnHeight = (histogramData[y]*histogram->height)/maxData;
        long columnEnd = histogram->height - columnHeight;
        for (unsigned int x = histogram->height - 1; x > columnEnd; x--) {
                histogram->rvb[y + x * histogram->width].r = printColor;
		        histogram->rvb[y + x * histogram->width].v = printColor;
		        histogram->rvb[y + x * histogram->width].b = printColor;        
		    }
    }
}


