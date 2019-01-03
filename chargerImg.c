#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "chargerImg.h"


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
	fscanf(fp, "%d%d%d\n", w,h,&maxval);

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
	newImg->width = width;
	newImg->height = height;
	newImg->rvb = malloc(3*width*height * sizeof(unsigned char));

	if(!newImg->rvb)
	{
		errorMsg("PAs assez place");
	}
	return EXIT_SUCCESS;
}

void desallocate(PPMImage *img)
{
	free((void *) img->rvb);
}

PPMImage * ImageRead(char *filename)
{
  int width, height, num, size;
  PPMImage *image = (PPMImage *) malloc(sizeof(PPMImage));
  FILE  *fp    = fopen(filename, "rb");

  if (!image) errorMsg("cannot allocate memory for new image");
  if (!fp)    errorMsg("cannot open file for reading");

  readPPMHeader(fp, &width, &height);

  size          = width * height * 3;
  image->rvb   = (unsigned char *) malloc(size);
  image->width  = width;
  image->height = height;

  if (!image->rvb) errorMsg("cannot allocate memory for new image");

  num = fread((void *) image->rvb, 1, (size_t) size, fp);

  if (num != size) errorMsg("cannot read image data from file");
  printf("%s\n", "OK");

  return image;
}

void IMG_remplir(PPMImage *img, unsigned char r, unsigned char v, unsigned char b)
{
	size_t x,y;
	for(y=0; y<img->height; ++y)
	{
		for(x=0; x<img->width; ++x)
		{
			*pixel_r(img,x,y) = r;
			*pixel_v(img,x,y) = v;
			*pixel_b(img,x,y) = b;
		}
	}
}

//expoter img
void ImageExport(PPMImage *image, char *filename)
{
  int num;
  int size = image->width * image->height * 3;

  FILE *fp = fopen(filename, "wb");

  if (!fp) errorMsg("cannot open file for writing");

  fprintf(fp, "P6\n%d %d\n%d\n", image->width, image->height, 255);

  num = fwrite((void *) image->rvb, 1, (size_t) size, fp);

  if (num != size) errorMsg("cannot write image data to file");

  fclose(fp);
}  

int ImageWidth(PPMImage *image)
{
  return image->width;
}


int ImageHeight(PPMImage *image)
{
  return image->height;
}