#include <stdlib.h>
#include "chargerImg.h"


int main() {
	PPMImage *img;
	img = ImageRead("img/Aerial.512.ppm");
	printf("%d\n", img->width);
	printf("%d\n", img->height);

}