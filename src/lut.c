#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "lut.h"

//functions that will allow us to do better operations
#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))

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


//Init LUT
void init(LUT *lut)
{
    for(int i =0 ; i<256; i++) 
    {
        lut->table[i] = 0;
    }
}

//INit 3D LUT
void init3D(LUT3D *lut3D)
{
    for(int i =0 ; i<256; i++) 
    {
        lut3D->r[i] = 0;
        lut3D->v[i] = 0;
        lut3D->b[i] = 0;
    }
}

//lut invert
void invert_table(LUT *lut)
{
    for(int i=0; i<256; i++)
    {
        lut->table[i] = 255-i;
    }
}

//sepia
void sepia(LUT3D *lut3D) {
    for(int i =0 ; i<256; i++) 
    {
        int tr, tv, tb;
        //sepia coef
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

        lut3D->r[i] = tr;
        lut3D->v[i] = tv;
        lut3D->b[i] = tb;
    }
}

//seuil
void seuil(LUT3D *lut3D, int param)
{
    //if pxl are under some int, they're put to 0. Else to 255. Allow us to have a great stamp effect
    for(int i=0; i<256; i++) {
        if (i <= param)
        {
            lut3D->r[i] = 0;
            lut3D->v[i] = 0;
            lut3D->b[i] = 0;

        }

        else
        {
           lut3D->r[i] = 255;
           lut3D->v[i] = 255;
           lut3D->b[i] = 255;
        }
       
    }
}

//addPixel
void addPixel(LUT3D *lut3D, int param, unsigned char pixel)
{
    for(int i=0; i<256; i++) {  
        if(pixel == 'r')
        {
            lut3D->r[i] = min(255, param+i);
        }

        else if(pixel == 'v')
        {
            lut3D->v[i] = min(255, param+i);
        }

        else if(pixel == 'b')
        {
            lut3D->b[i] = min(255, param+i);
        }
    }
}

//tint. To do : make it works
void tint(LUT3D *lut3D, int kelvin)
{
    static double tmp;
    static double tmp2;
    //convert kelvin to degree
    if(kelvin < 1000)
    {
        kelvin = 1000;
    }

    if(kelvin > 40000)
    {
        kelvin = 40000;
    }

    kelvin = kelvin / 100;

    for(int i=0; i<256; i++) 
    {  
        if(kelvin <=66)
        {
            lut3D->r[i] = 255;
            tmp = kelvin;
            tmp = 99.470825861 * (log(tmp) - 161.1195681661);
            lut3D->v[i] = tmp;

            if (lut3D->v[i] < 0 )
            {
                lut3D->v[i] = 0;
            }

            if(lut3D->v[i] > 255)
            {
                lut3D->v[i] = 255;
            }
        }

        if(kelvin>=66)
        {
              lut3D->b[i] = 255;
        }

        else if(kelvin<=19)
        {
              lut3D->b[i] = 0;
        }

        else
        {
            tmp = kelvin - 60;
            tmp = 329.698727446 * pow(tmp,-0.1332047592);
            lut3D->r[i] = tmp;

            if(lut3D->r[i] < 0 )
            {
                lut3D->r[i] = 0;
            }

            if(lut3D->r[i]>255)
            {
                lut3D->r[i] = 255;
            }

            tmp2 = kelvin-10;
            tmp2 = 138.5177312231 * (log(tmp2) - 305.0447927307);
            lut3D->b[i] = tmp2;

            if(lut3D->b[i]<0)
            {
                lut3D->b[i] = 0;
            }

            if(lut3D->b[i]>255)
            {
                lut3D->b[i] = 255;
            }
        }
    }   
}


//Kinda doesn't work now
void blacknwh(LUT3D *lut3D)
{
    for(int i=0; i<256; i++) 
    {
        int avg = (lut3D->r[i] + lut3D->v[i] + lut3D->b[i]) / 3;
        lut3D->r[i] = avg;
        lut3D->v[i] = avg;
        lut3D->b[i] = avg;

    }
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

//Add luminosity
void addLum(LUT *lut, int param) {
    for (int i = 0; i < 256; i++) 
    {
        lut->table[i] = min(255, param + i);
    }
}

//Remove luminosity
void dimLum(LUT *lut, int param) {
    for(int i=0; i < 256 ; i++) 
    {
        lut->table[i] = max(0, i - param);
    }
}

//Add contrast
void addCon(LUT *lut, int param) {
    for (int i = 0 ; i < 256 ; i++){
        lut->table[i] = min(255, max(0, (float)param*(i - 128.) + 128.));          
    }
}

//Remove contrast
void dimCon(LUT *lut,int param) {
    double brightness = 0;
    double contrastFactor = (259.0 * ((-param) + 255.0)) / (255.0 * ( 259.0 - (-param)));
    for (int i = 0; i < 256 ; i++) {
        brightness = contrastFactor * (lut->table[i] - 128) + 128;
        if (brightness > 255) { brightness = 255; }
        if (brightness < 0) { brightness = 0; }
        lut->table[i] = (unsigned char) brightness;
    }
}

//Luminosity logarithm
void ln(LUT *lut, int param) {
    for(int i=0; i<256; i++) {
        lut->table[i] = min(255, log(i)*(255-param)/5.0 +param);
    }
}

