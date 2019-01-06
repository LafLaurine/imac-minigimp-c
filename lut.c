#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "lut.h"
#include "pixel.h"



void init(LUT* lut, Pixel* pxl, int height, int width)
{
    lut->rvb = pxl;
    lut->size = width * height;
    lut->next = NULL;
    lut->previous = NULL;
}


/*
void ListeLUTs_retirerDerniere(ListeLUTs *liste) {
    if(!liste->derniere)
        return;
    LUT *prec = liste->derniere->precedente;
    free(liste->derniere);
    liste->derniere = prec;
    if(liste->derniere)
        liste->derniere->suivante = NULL;
    else
        liste->derniere = liste->premiere = NULL;
}*/

//function copy pointer A copie dans B soit function renvoie pointer 

LUT* copy(LUT* lut)
{
    LUT *copy = malloc(sizeof(LUT));
    //malloc copy par rapport taille lut
    copy->rvb = lut->rvb;
    memcpy(copy,lut,sizeof(LUT));
    //memcpy lut vers copy

    return copy;
}

LUT* invert(LUT *lut) {
    LUT* copied = copy(lut);
    for(int i=0;i<copied->size;i++)
    {
            copied->rvb[i].r = 255-copied->rvb[i].r;
            copied->rvb[i].v = 255-copied->rvb[i].v;
            copied->rvb[i].b = 255-copied->rvb[i].b;
    }
    return copied;
}


/* La mission des fonctions suivantes : 
 Remplir les pixels  en fonction de param.*/
#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))


LUT* addLum(LUT *lut, int param) {
    LUT* copied = copy(lut);
    for(int i=0; i<copied->size; i++) {
        copied->rvb[i].r = min(255, (int)(copied->rvb[i].r+param));
        copied->rvb[i].v = min(255, (int)(copied->rvb[i].v+param));
        copied->rvb[i].b = min(255, (int)(copied->rvb[i].b+param));
    }
    return copied;
}

//NOP
LUT* dimLum(LUT *lut, int param) {
    LUT* copied = copy(lut);
     for(int i=0; i<copied->size; i++) {
        copied->rvb[i].r = max(0, (int)(copied->rvb[i].r-param));
        copied->rvb[i].v = max(0, (int)(copied->rvb[i].v-param));
        copied->rvb[i].b = max(0, (int)(copied->rvb[i].b-param));
    }
    return copied;
}

// Change la valeur du contraste
LUT* addCon(LUT *lut, int param) {
    LUT* copied = copy(lut);
    for(int i=0; i<copied->size; i++) {
        copied->rvb[i].r = min(255, max(0, (float)param*(copied->rvb[i].r  - 128.) + 128.));          
        copied->rvb[i].v = min(255, max(0, (float)param*(copied->rvb[i].v - 128.) + 128.));        
        copied->rvb[i].b = min(255, max(0, (float)param*(copied->rvb[i].b - 128.) + 128.));
    }
    return copied;

}

LUT* dimCon(LUT *lut, int param) {
     LUT* copied = copy(lut);
     float a = 1. / param;
    for(int i=0; i<copied->size; i++) {
    
       copied->rvb[i].r = min(255, max(0, (float)a*(copied->rvb[i].r - 128.) + 128.));          
       copied->rvb[i].v = min(255, max(0, (float)a*(copied->rvb[i].v - 128.) + 128.));        
       copied->rvb[i].b = min(255, max(0, (float)a*(copied->rvb[i].b - 128.) + 128.));
    }
    return copied;
}

LUT* augmentationR(LUT *lut, int param) {
    LUT* copied = copy(lut);
    for(int i =0; i<copied->size; i++) {
        copied->rvb[i].r = min(255, param+i);

    }
    return copied;
}

LUT* augmentationV(LUT *lut, int param) {
    LUT* copied = copy(lut);
    for(int i=0; i<copied->size; i++) {
        copied->rvb[i].v = min(255, param+i);
    }
    return copied;
}

LUT* augmentationB(LUT *lut, int param) {
      LUT* copied = copy(lut);
    for(int i=0; i<copied->size; i++) {
        copied->rvb[i].b = min(255, param+i);
    }
    return copied;
}

LUT* seuil(LUT *lut)
{
    LUT* copied = copy(lut);
    for(int i=0; i<copied->size; i++) {
        if (copied->rvb[i].r <= 127 || copied->rvb[i].v <= 127 || copied->rvb[i].b <=127)
        {
            copied->rvb[i].r = 0;
            copied->rvb[i].v = 0;
            copied->rvb[i].b = 0;

        }

        else
        {
            copied->rvb[i].r = 255;
            copied->rvb[i].v = 255;
            copied->rvb[i].b = 255;
        }
       
    }
    return copied;
}

LUT* sepia(LUT *lut) {
    //try to see why blue is cramed af
    LUT* copied = copy(lut);
    // if we want to change transparency int alpha = 255;
    for(int i =0 ; i<copied->size; i++) {
        int tr, tv, tb;
        tr = 0.393*(copied->rvb[i].r) + 0.769*(copied->rvb[i].v) + 0.189*(copied->rvb[i].b);
        tv = 0.349*(copied->rvb[i].r) + 0.686*(copied->rvb[i].v) + 0.168*(copied->rvb[i].b);
        tb = 0.272*(copied->rvb[i].r) + 0.534*(copied->rvb[i].v) + 0.131*(copied->rvb[i].b);
        copied->rvb[i].r = tr;
        copied->rvb[i].v = tv;
        copied->rvb[i].b = tb;
    }
    return copied;
}

LUT *saveLUT(LUT* lut) {
    LUT* copied = copy(lut);
    printf("in: ");
    for (int i = 0; i <= copied->size; i++) {
        printf("%d ", i);
    }
    printf("\n");

    printf("to: ");
    for (int i = 0; i <= copied->size; i++) {
        printf("%d %d %d", copied->rvb[i].r, copied->rvb[i].v, copied->rvb[i].b);
    }
    printf("\n");

    return copied;
}