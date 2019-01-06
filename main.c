#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "lut.h"
#include "histogram.h"

// minigimp mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]


//choix dans menu pour retrouner a avant chgt lut
int main(int argc, char *argv[]) {

	if (argc > 0) {
	PPMImage img;
	//lire image avant initialisation LUT
	imageRead(&img, argv[1]);
	LUT lut;
	//LUT du début identique à img
	init(&lut,img.rvb,img.height,img.width);
	//printf("%d\n", img.width);
	printf("%d\n", img.height);


	for (int i = 2; i < argc; i++) {
		if (strcmp(argv[i], "INVERT") == 0) {
                invert(&lut);
            }
        else if (strcmp(argv[i], "ADDLUM") == 0)
        {

        	  int param;
        	  sscanf(argv[i+1],"%d",&param);
                if (param > 255) { param = 255; }
            addLum(&lut,param);
        }
          else if (strcmp(argv[i], "DIMLUM") == 0)
        {

        	  int param;
        	  sscanf(argv[i+1],"%d",&param);
            dimLum(&lut,param);
        }
           else if (strcmp(argv[i], "AUGR") == 0)
        {
        	   long param;
        	 param = strtol(argv[i+1],NULL,10);
        	  printf("%ld\n", param);
                if (param > 255) { param = 255; }
            augmentationR(&lut,param);
        }
        else if (strcmp(argv[i], "ADDCON") == 0) {
                long param = strtol(argv[i + 1], NULL, 10);
                if (param > 255) { param = 255; }
                addCon(&lut, param);
        }
         else if (strcmp(argv[i], "SEPIA") == 0) {
                sepia(&lut);
        }
          else if (strcmp(argv[i], "SEUIL") == 0) {
                seuil(&lut);
        }
	}

	//print(&lut);
	ImageSave(&img,"img/outpout.ppm");
	clear(&img);

}
	return 0;

}
