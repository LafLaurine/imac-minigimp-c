#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "lut.h"
#include "histogram.h"
#include "conversion.h"
// minigimp mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]

//choix dans menu pour retrouner a avant chgt lut
int main(int argc, char *argv[]) {

    bool histo = false;
    int path = -1;
	if (argc > 0) {
	PPMImage img;
    LUT lut;
    LUT3D lut3D;
   // init_LUTs(&lut);

	//lire image avant initialisation LUT
	imageRead(&img, argv[1]);



	for (int i = 2; i < argc; i++) {


      if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-histo") == 0) {
                PPMImage histogram;
                allocate(&histogram, 256, 256);
                init_histo(&img, &histogram);
                ImageSave(&histogram, "./img/input-histogram.ppm");
                clear(&histogram);
                histo = true;

            }


		else if (strcmp(argv[i], "INVERT") == 0) {
                lut = invert_table();
                greyScaleToRGB(&lut,&img);
            }
        else if (strcmp(argv[i], "ADDLUM") == 0)
        {

              int param;
              sscanf(argv[i+1],"%d",&param);
                if (param > 255) { param = 255; }
        
            lut = addLum(param);
            appliquerLUT(&img,&lut);
        }

        else if (strcmp(argv[i], "DIMLUM") == 0)
        {

              int param;
              sscanf(argv[i+1],"%d",&param);
                if (param > 255) { param = 255; }
        
            lut = dimLum(param);
            appliquerLUT(&img,&lut);
        }

        else if (strcmp(argv[i], "SEPIA") == 0)
        {
          
        
            lut3D = sepia();
            appliquerLUT3D(&img,&lut3D);
        }


        else if (strcmp(argv[i], "SEUIL") == 0)
        {
               int param;
              sscanf(argv[i+1],"%d",&param);
                if (param > 255) { param = 255; }
            lut3D = seuil(param);
            appliquerLUT3D(&img,&lut3D);
        }

        else if (strcmp(argv[i], "BLACKNWHITE") == 0)
        {
            lut3D = blacknwh();
            appliquerLUT3D(&img,&lut3D);
        }

           else if (strcmp(argv[i], "ADDCON") == 0)
        {
              int param;
              sscanf(argv[i+1],"%d",&param);
                if (param > 255) { param = 255; }

            lut = addCon(param);
            appliquerLUT(&img,&lut);
        }

            else if (strcmp(argv[i], "DIMCON") == 0)
        {
              int param;
              sscanf(argv[i+1],"%d",&param);
                if (param > 255) { param = 255; }

            lut = dimCon(param);
                greyScaleToRGB(&lut,&img);
        }

             else if (strcmp(argv[i], "ADDPIXEL") == 0)
        {
              int param;
              unsigned char pixel;
              sscanf(argv[i+2],"%d",&param);
                if (param > 255) { param = 255; }
             sscanf(argv[i+1],"%c",&pixel);

            lut3D = addPixel(param,pixel);
            appliquerLUTChannel(&img,&lut3D,pixel);
        }


             else if (strcmp(argv[i], "TINT") == 0)
        {
              int param;
              sscanf(argv[i+1],"%d",&param);

            lut3D = tint(param);
            appliquerLUT3D(&img,&lut3D);
        }


        else if(strcmp(argv[i], "-o") == 0)
        {
            path = i + 1;
        }

	}

	//print(&lut);
    if(histo)
    {
        PPMImage histogramAfter;
        allocate(&histogramAfter, 256, 256);
        init_histo(&img, &histogramAfter);
        ImageSave(&histogramAfter, "./img/output-histogram.ppm");
        clear(&histogramAfter);
    }

    if(path!=-1)
    {
        ImageSave(&img,argv[path]);
    }
    else
    {
      ImageSave(&img,"img/outpoutImage.ppm");

    }
	clear(&img);
    //clear_LUTs(&lut);

}

    else
    {
        printf("%s\n", "No input");
        return EXIT_FAILURE;
    }


	return EXIT_SUCCESS;

}
