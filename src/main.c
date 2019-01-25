#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "lut.h"
#include "effects.h"
#include "histogram.h"
#include "conversion.h"

//Use : minigimp mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]

int main(int argc, char *argv[]) {
  //handle histogram with a boolean in order to handle the before/after
  bool histo = false;
  //handle path of the image bc if the user wants to enter the name of the image himself, we need to check it
  int path = -1;

  //if the user passes something into arguments : if he uses the programm properly
	if (argc > 0) {
    //declaration and init of our structures
    PPMImage img;
    LUT lut;
    init(&lut);
    LUT3D lut3D;
    init3D(&lut3D);
    // init_LUTs(&lut);

    //Read the image before applying LUT to it, the img is always the 1st argument
    imageRead(&img, argv[1]);

    //Handling arguments : LUTS and histogram
    for (int i = 2; i < argc; i++) {
      //histogram
      if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-histo") == 0) {
        //init histo
        PPMImage histogram;
        allocate(&histogram, 256, 256);
        init_histo(&img, &histogram);
        //save histo into an image
        ImageSave(&histogram, "./img/input-histogram.ppm");
        clear(&histogram);
        //boolean become true bc the input one is done
        histo = true;
      }

      //LUT invert
      else if (strcmp(argv[i], "INVERT") == 0) {
        invert_table(&lut);
        greyScaleToRGB(&lut,&img);
      }
    
      //add luminosity
      else if (strcmp(argv[i], "ADDLUM") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        if (param > 255) { param = 255; }
        addLum(&lut,param);
        appliquerLUT(&img,&lut);
      }

      //remove luminosity
      else if (strcmp(argv[i], "DIMLUM") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        if (param > 255) { param = 255; }
        dimLum(&lut,param);
        appliquerLUT(&img,&lut);
      }

      //sepia
      else if (strcmp(argv[i], "SEPIA") == 0)
      {
        sepia(&lut3D);
        appliquerLUT3D(&img,&lut3D);
      }

      //seuil
      else if (strcmp(argv[i], "SEUIL") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        if (param > 255) { param = 255; }
        seuil(&lut3D,param);
        appliquerLUT3D(&img,&lut3D);
      }

      //noise
      else if (strcmp(argv[i], "NOISE") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        if (param > 255) { param = 255; }
        bruit(&img,param);
      }

      //black and white
      else if (strcmp(argv[i], "BLACKNWHITE") == 0)
      {
        blacknwh(&img);
      }

      //add contrast
      else if (strcmp(argv[i], "ADDCON") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        if (param > 255) { param = 255; }
        addCon(&lut,param);
        appliquerLUT(&img,&lut);
      }

      //remove contrast
      else if (strcmp(argv[i], "DIMCON") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        if (param > 255) { param = 255; }
        dimCon(&lut,param);
        greyScaleToRGB(&lut,&img);
      }

      //add some color. Use : ADDPIXEL 'r'/'v'/'b' PARAM
      else if (strcmp(argv[i], "ADDPIXEL") == 0)
      {
        int param;
        unsigned char pixel;
        sscanf(argv[i+2],"%d",&param);
        if (param > 255) { param = 255; }
        sscanf(argv[i+1],"%c",&pixel);
        addPixel(&lut3D,param,pixel);
        appliquerLUTChannel(&img,&lut3D,pixel);
      }

      //remove some color. Use : REMOVEPIXEL 'r'/'v'/'b' PARAM
      else if (strcmp(argv[i], "REMOVEPIXEL") == 0)
      {
        int param;
        unsigned char pixel;
        sscanf(argv[i+2],"%d",&param);
        if (param > 255) { param = 255; }
        sscanf(argv[i+1],"%c",&pixel);
        removePixel(&lut3D,param,pixel);
        appliquerLUTChannel(&img,&lut3D,pixel);
      }

      //Tint but doesn't really work
      else if (strcmp(argv[i], "TINT") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        tint(&lut3D,param);
        appliquerLUT3D(&img,&lut3D);
      }

      else if (strcmp(argv[i], "CYAN") == 0)
      {
        cyan(&lut3D);
        greyScaleToRGB3D(&lut3D,&img);
      }

      //Logarithm luminosity
      else if (strcmp(argv[i], "LOG") == 0)
      {
        int param;
        sscanf(argv[i+1],"%d",&param);
        ln(&lut,param);
        appliquerLUT(&img,&lut);
      }

      else if (strcmp(argv[i], "SWAP") == 0)
      {
        swap(&img);
      }

      else if (strcmp(argv[i], "REMOVE") == 0)
      {
        removeFirst(&lut);
      }

      //Handle image name
      else if(strcmp(argv[i], "-o") == 0)
      {
        path = i + 1;
      }

    }

    //if boolean true : histogram input has been done, we can do the output one
    if(histo)
    {
      PPMImage histogramAfter;
      allocate(&histogramAfter, 256, 256);
      init_histo(&img, &histogramAfter);
      ImageSave(&histogramAfter, "./img/output-histogram.ppm");
      clear(&histogramAfter);
    }

    //if user choose a name for the image
    if(path!=-1)
    {
      ImageSave(&img,argv[path]);
    }

    else
    {
      ImageSave(&img,"img/outpoutImage.ppm");
    }

    //free memory
    clear(&img);
}

//Input none
else
{
  printf("%s\n", "No input");
  return EXIT_FAILURE;
}
	return EXIT_SUCCESS;

}
