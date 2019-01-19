#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "image.h"

//Handle error messages
void errorMsg(char *message)
{
	fprintf(stderr, "PPM : %s\n", message);
	exit(1);
}

//Read the header of a PPM file
void readPPMHeader(FILE* fp, int *w, int *h)
{
	char ch;
	int maxval;

	//check the PPM type
	if(fscanf(fp, "P%c\n",&ch)!=1 || ch!='6')
	{
		errorMsg("Not PPM raw format");
	}

	//check if there is comments
	ch = getc(fp);
	while(ch=='#')
	{
		do
		{
			ch=getc(fp);
		}
		while(ch!='\n');
		ch = getc(fp);
	}

	//check if the following elements are digital or not
	if (!isdigit(ch))
	{
		errorMsg("Can't read header");
	}

	ungetc(ch,fp);
	fscanf(fp, "%d%d%d\n",w,h,&maxval);

	if(maxval!=255)
	{
		errorMsg("Not colored image");
	}
}

int allocate(PPMImage *newImg, int width, int height)
{
	if (width<=0 || height <=0)
	{
		errorMsg("Negative size");
	}

	//rvb point to Pixel structure 
	//allocate memory
	newImg->rvb = malloc(width*height * sizeof(Pixel));
	newImg->greyScale = malloc(sizeof(unsigned char) * width * height);

	if(!newImg->rvb)
	{
		errorMsg("Not enough memory");
		return EXIT_FAILURE;
	}

	//Affect values to the structure
	newImg->width = width;
	newImg->height = height;
	return EXIT_SUCCESS;
}

//free memory
void clear(PPMImage *img)
{
	//if the structure is not empty
	if (img!=NULL)
	{
		//if the field is not empty
		if(img->rvb!=NULL)
		{
			free((void *) img->rvb);
			img->rvb = NULL;
		}

		img->width = 0;
		img->height = 0;
	}
	
}

//in order to get the grey level of an image
void greyScale(PPMImage *image)
{
	for(int i = 0; i<image->width*image->height; i++)
	{
		//math formula found in internet : average of red, greenn and blue 
		image->greyScale[i] = 0.299*image->rvb[i].r + 0.587*image->rvb[i].v + 0.114 * image->rvb[i].b;
	}
}

//Read an image
int imageRead(PPMImage *image, char *filename)
{
	int width, height, size;
	FILE  *fp    = fopen(filename, "rb");
	if (!fp)    errorMsg("Cannot open file for reading");
	readPPMHeader(fp, &width, &height);
	size = width * height * 3;

	allocate(image,width,height);
  	fread(image->rvb, sizeof(unsigned char), (size_t) size, fp);
  	if (!image->rvb) errorMsg("Cannot allocate memory for new image");

  	
 	fclose(fp);
 	return EXIT_SUCCESS;
}

//Export image
int ImageSave(PPMImage *image, char *filename)
{
  int size = image->width * image->height * 3;

  //we write a new image
  FILE *fp = fopen(filename, "wt");

  if (!fp) errorMsg("cannot open file for writing");

  fprintf(fp, "P6\n%d %d\n%d\n", image->width, image->height, 255);

  fwrite(image->rvb, sizeof(unsigned char),size, fp);

  fclose(fp);

  return EXIT_SUCCESS;
}  
