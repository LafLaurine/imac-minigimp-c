#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "image.h"


void errorMsg(char *message)
{
	fprintf(stderr, "PPM : %s\n", message);
	exit(1);
}


void readPPMHeader(FILE* fp, int *w, int *h)
{
	char ch;
	int maxval;

	if(fscanf(fp, "P%c\n",&ch)!=1 || ch!='6')
	{
		errorMsg("Not PPM raw format");
	}

	/* comments */
	ch = getc(fp);
	while(ch=='#')
	{
		do
		{
			ch=getc(fp);
		}while(ch!='\n');
		ch = getc(fp);
	}

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
	//rvb pointeur sur struct pixel
	newImg->rvb = malloc(width*height * sizeof(Pixel));
	newImg->greyScale = malloc(sizeof(unsigned char) * width * height);

	if(!newImg->rvb)
	{
		errorMsg("Pas assez place");
		return EXIT_FAILURE;
	}

	newImg->width = width;
	newImg->height = height;



	return EXIT_SUCCESS;
}

void clear(PPMImage *img)
{
	if (img!=NULL)
	{
		if(img->rvb!=NULL)
		{
			free((void *) img->rvb);
			img->rvb = NULL;
		}
		img->width = 0;
		img->height = 0;
	}
	
}

void greyScale(PPMImage *image)
{
	for(int i = 0; i<image->width*image->height; i++)
	{
		image->greyScale[i] = 0.299*image->rvb[i].r + 0.587*image->rvb[i].v + 0.114 * image->rvb[i].b;

	}
}



int imageRead(PPMImage *image, char *filename)
{
	int width, height, size;
	FILE  *fp    = fopen(filename, "rb");
	if (!fp)    errorMsg("cannot open file for reading");
	readPPMHeader(fp, &width, &height);
	size = width * height * 3;

	allocate(image,width,height);
  	fread(image->rvb, sizeof(unsigned char), (size_t) size, fp);
  	if (!image->rvb) errorMsg("cannot allocate memory for new image");

  	
 	fclose(fp);
 	return EXIT_SUCCESS;
}

//expoter img
int ImageSave(PPMImage *image, char *filename)
{
  int size = image->width * image->height * 3;

  FILE *fp = fopen(filename, "wt");

  if (!fp) errorMsg("cannot open file for writing");

  fprintf(fp, "P6\n%d %d\n%d\n", image->width, image->height, 255);

  fwrite(image->rvb, sizeof(unsigned char),size, fp);

  fclose(fp);

  return EXIT_SUCCESS;
}  
