#ifndef LUT_H
#define LUT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct LUT LUT;
typedef void (*FonctionLUT)(LUT *lut);
struct LUT {
    unsigned char r[256];
    unsigned char v[256];
    unsigned char b[256];
    FonctionLUT fonction; /* Sert à deux choses : 
                1) identifier le type de la LUT ;
                2) recalculer les valeurs des tables, d'après param1. */
    unsigned char param1; /* luminosité ou contraste selon le cas. */
    LUT *before, *next;
};
typedef struct ListeLUT ListeLUT;
struct ListeLUT {
    LUT *first, *last;
};

/* Utilisation correcte :
 * ListeLUTs liste;
 * ListeLUTs_allouer(&liste);
 * ListeLUTs_ajouterDerniere(&liste);
 * // Modifier liste->derniere....
 * ListeLUTs_desallouer(&liste);
 */

bool newListLUT(ListeLUT *liste);
void freeListeLUT(ListeLUT *liste);
bool addLastLUT(ListeLUT *liste);
void removeLastLUT(ListeLUT *liste);
void removeFirstLUT(ListeLUT *liste);
void LUT_invert(LUT *lut);
void LUT_sepia(LUT *lut);
void LUT_addLum(LUT *lut);
void LUT_dimLum(LUT *lut);
void LUT_addCon(LUT *lut);
void LUT_dimCon(LUT *lut);
void LUT_augmentationR(LUT *lut);
void LUT_augmentationV(LUT *lut);
void LUT_augmentationB(LUT *lut);

#endif /* LUT_H */