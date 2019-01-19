#include <stdlib.h>
#include <stdio.h>
#include "histogram.h"

//Greyscale histogram of the average of red, green and blue
int init_histo(PPMImage* img, PPMImage* histogramme) {
    //need to declare a tab that can take 255 values
	unsigned int greyscale[256] = { 0 };
	unsigned int pixelAvgBrightness = 0;
    //max height of the histogramm
    unsigned int maxPixels = 0;
    //Read through the images in order to get pixels
    for (unsigned int x = 0; x < img->width; x++) {
        for (unsigned int y = 0; y < img->height; y++) {
            //average of all colors
            pixelAvgBrightness += img->rvb[x].r + img->rvb[x].v + img->rvb[x].b + img->rvb[y].r + img->rvb[y].v + img->rvb[y].b;
            //we have 3 components so we divide by 3
            pixelAvgBrightness = pixelAvgBrightness/3;
            greyscale[(unsigned char) pixelAvgBrightness] += 1;
            
            if (greyscale[(unsigned char) pixelAvgBrightness] > maxPixels) 
            {
                maxPixels = greyscale[(unsigned char) pixelAvgBrightness];
            }

            pixelAvgBrightness = 0;

            }
            
        }
            //display histogram
            printHistogram(histogramme, greyscale, maxPixels, 200);

    
    return EXIT_SUCCESS;
}

//Function to display the histogram
void printHistogram(PPMImage* histogram, unsigned int* histogramData, unsigned int maxData, unsigned char printColor) {
  
    if (histogram->width != 256) {
        printf("Not enough width");
        exit(EXIT_FAILURE);
    }

    //Read through the histogramm to display data into it
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


