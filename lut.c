#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "lut.h"

//allocate memory for LUT list
bool newListLUT(ListeLUT *liste)
{
    liste->first = liste->last = NULL;
    return true;
}

void freeListeLUT(ListeLUT *liste) {
    if(!liste->first)
        return;
    LUT *current;
    for(current=liste->first ; current!=liste->last ; current=current->next)
        free(current);
    free(current);
}

bool addLastLUT(ListeLUT *liste) { 
    LUT *new = calloc(1, sizeof(LUT));
    if(!new) {
        fputs("Can't add LUT", stderr);
        return false;
    }
    if(liste->last) {
        new->before = liste->last;
        liste->last->next = new;
        liste->last = new;
    } else
        liste->first = liste->last = new;

    /*liste->last->fonction = LUT_inversion;
    liste->derniere->param1 = 127;*/
    return true; 
}

void removeLastLUT(ListeLUT *liste) {
    if(!liste->last)
        return;
    LUT *prec = liste->last->before;
    free(liste->last);
    liste->last = prec;
    if(liste->last)
        liste->last->next = NULL;
    else
        liste->last = liste->first = NULL;
}
void removeFirstLUT(ListeLUT *liste) {
    LUT *first = liste->first;
    liste->first = liste->first->next;
    if(!liste->first)
        liste->last = NULL;
    free(first);
}


void LUT_invert(LUT *lut) {
    size_t i, inv;
    for(i=0, inv=255 ; i<256 ; ++i, --inv)
    {
        lut->r[i] = lut->v[i] = lut->b[i] = inv;
    }
       
}

void LUT_sepia(LUT *lut) {
    const unsigned char sepia[3*256];
    size_t i;
    for(i=0 ; i<256 ; ++i) {
        lut->r[i] = sepia[3*i];
        lut->v[i] = sepia[3*i+1];
        lut->b[i] = sepia[3*i+2];
    }
}


/* La mission des fonctions suivantes : 
 * Remplir lut->r, lut->v et lut->b en fonction de lut->param1.*/
#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))


void LUT_addLum(LUT *lut) {
    size_t i;
    for(i=0; i<256; i++) {
        lut->r[i] = min(255, lut->param1+i);
        lut->v[i] = min(255, lut->param1+i);
        lut->b[i] = min(255, lut->param1+i);
    }
}

void LUT_dimLum(LUT *lut) {
    size_t i;
    for(i=0; i<256; i++) {
        lut->r[i] = max(0, (int)(i-lut->param1));
        lut->v[i] = max(0, (int)(i-lut->param1));
        lut->b[i] = max(0, (int)(i-lut->param1));
    }
}

// Change la valeur du contraste
void LUT_addCon(LUT *lut) {
    size_t i;

    for (i = 0 ; i < 256 ; i++){
        lut->r[i] = min(255, max(0, (float)lut->param1*(i - 128.) + 128.));          
        lut->v[i] = min(255, max(0, (float)lut->param1*(i - 128.) + 128.));        
        lut->b[i] = min(255, max(0, (float)lut->param1*(i - 128.) + 128.));
    }

}
void LUT_dimCon(LUT *lut) {
    size_t i;
    float a = 1. / lut->param1;
    for (i = 0 ; i < 256 ; i++){
        lut->r[i] = min(255, max(0, (float)a*(i - 128.) + 128.));          
        lut->v[i] = min(255, max(0, (float)a*(i - 128.) + 128.));        
        lut->b[i] = min(255, max(0, (float)a*(i - 128.) + 128.));
    }
}

/* Celles-ci ne sont pas demandées. */
void LUT_augmentationR(LUT *lut) {
    size_t i;
    for(i=0; i<256; i++) {
        lut->r[i] = min(255, lut->param1+i);
        lut->v[i] = i;
        lut->b[i] = i;
    }
}
void LUT_augmentationV(LUT *lut) {
    size_t i;
    for(i=0; i<256; i++) {
        lut->r[i] = i;
        lut->v[i] = min(255, lut->param1+i);
        lut->b[i] = i;
    }
}
void LUT_augmentationB(LUT *lut) {
    size_t i;
    for(i=0; i<256; i++) {
        lut->r[i] = i;
        lut->v[i] = i;
        lut->b[i] = min(255, lut->param1+i);
    }
}