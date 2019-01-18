#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "lut.h"



#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))

//chaque fonction init en o(n) set lut o(1) o qqch ordre grandeur
//lut s'apppliquent sur noir et blanc, modif canaux pas parcours pixels

/*
int init_LUTs(LUT* lut)
{
    lut->table = malloc(256 * sizeof(int));
    if(lut->table == NULL)
    {
        printf("%s\n", "Error, data is null");
        return EXIT_FAILURE;
    }
    for(unsigned int i = 0; i< 256; i++)
    {
        lut->table[i] = (int) i;
    }
    return EXIT_SUCCESS;
}


int clear_LUTs(LUT *lut) {
        free(lut->table);
    
    return EXIT_SUCCESS;
        
}

int LUTs_retirerDerniere(LUT *lut) {
    LUT *prec = lut->previous;
    free(lut->next);
    lut->next = prec;
}*/

LUT invert_table()
{
    LUT lut;
    for(int i=0; i<256; i++)
    {
        lut.table[i] = 255-i;
    }
    return lut;
}

LUT3D sepia() {
    LUT3D lut;
    for(int i =0 ; i<256; i++) {
        int tr, tv, tb;
        tr = (0.393*i) + (0.769*i) + (0.189*i);
        tv = (0.349*i) + (0.686*i) + (0.168*i);
        tb = (0.272*i) + (0.534*i) + (0.131*i);
        if(tr > 255)
        {
            tr = 255;
        }
        if(tv>255)
        {
            tv = 255;
        }
        if(tb>255)
        {
            tb = 255;
        }
        lut.r[i] = tr;
        lut.v[i] = tv;
        lut.b[i] = tb;
    }
    return lut;
}

LUT3D seuil(int param)
{
    LUT3D lut;
    for(int i=0; i<256; i++) {
        if (i <= param)
        {
            lut.r[i] = 0;
            lut.v[i] = 0;
            lut.b[i] = 0;

        }

        else
        {
           lut.r[i] = 255;
           lut.v[i] = 255;
           lut.b[i] = 255;
        }
       
    }
    return lut;
}

LUT3D addPixel(int param, unsigned char pixel)
{
    LUT3D lut;

    for(int i=0; i<256; i++) {  
        if(pixel == 'r')
        {
            lut.r[i] = min(255, param+i);
        }

        else if(pixel == 'v')
        {
            lut.v[i] = min(255, param+i);
        }

        else if(pixel == 'b')
        {
            lut.b[i] = min(255, param+i);
        }
    }
    return lut;
}

LUT3D tint(int kelvin)
{
        LUT3D lut;

    static double tmp;
    static double tmp2;
    //converte kelvin to degree
    if(kelvin < 1000)
    {
        kelvin = 1000;
    }

    if(kelvin > 40000)
    {
        kelvin = 40000;
    }

    kelvin = kelvin / 100;

 for(int i=0; i<256; i++) {  
    if(kelvin <=66)
    {
        lut.r[i] = 255;
        tmp = kelvin;
        tmp = 99.470825861 * (log(tmp) - 161.1195681661);
        lut.v[i] = tmp;
        if (lut.v[i] < 0 )
        {
            lut.v[i] = 0;
        }

        if(lut.v[i] > 255)
        {
            lut.v[i] = 255;
        }
    }

    if(kelvin>=66)
    {
          lut.b[i] = 255;
    }

    else if(kelvin<=19)
    {
          lut.b[i] = 0;
    }

    else
    {
        tmp = kelvin - 60;
        tmp = 329.698727446 * pow(tmp,-0.1332047592);
        lut.r[i] = tmp;

        if(lut.r[i] < 0 )
        {
            lut.r[i] = 0;
        }
        if(lut.r[i]>255)
            {lut.r[i] = 255;
            }
        tmp2 = kelvin-10;
        tmp2 = 138.5177312231 * (log(tmp2) - 305.0447927307);
        lut.b[i] = tmp2;
        if(lut.b[i]<0)
        {
            lut.b[i] = 0;
        }

        if(lut.b[i]>255)
        {
            lut.b[i] = 255;
        }
    }


}
    return lut;
}


LUT3D blacknwh()
{
    LUT3D lut;
    for(int i=0; i<256; i++) {
        int avg = (lut.r[i] + lut.v[i] + lut.b[i]) / 3;
        lut.r[i] = avg;
        lut.v[i] = avg;
        lut.b[i] = avg;

    }
    return lut;
}

/*
LUT bord()
{
    for(int i=0; i<256; i++) {
        int a = lut.table[i+1];
        int b = lut.table[i+2];

    }
    return lut;
}*/



//0% noir, 100% blanc
// contraste = différence entre zone claires et sombres d'une img

LUT addLum(int param) {
    LUT lut;
    for (int i = 0; i < 256; i++) {
        lut.table[i] = min(255, param + i);
    }
    
    return lut;
}

LUT dimLum(int param) {
    LUT lut;
        for(int i=0; i < 256 ; i++) {
        lut.table[i] = max(0, i - param);
    }
    return lut;
}



LUT addCon(int param) {
    LUT lut;
    for (int i = 0 ; i < 256 ; i++){
        lut.table[i] = min(255, max(0, (float)param*(i - 128.) + 128.));          
    }
    return lut;

}

LUT dimCon(int param) {
    LUT lut;
      double brightness = 0;
    double contrastFactor = (259.0 * ((-param) + 255.0)) / (255.0 * ( 259.0 - (-param)));
    for (int i = 0; i < 256 ; i++) {
        brightness = contrastFactor * (lut.table[i] - 128) + 128;
        if (brightness > 255) { brightness = 255; }
        if (brightness < 0) { brightness = 0; }
        lut.table[i] = (unsigned char) brightness;
    }
    return lut;
}

