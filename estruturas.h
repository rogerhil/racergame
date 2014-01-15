#ifndef estruturas_h
#define estruturas_h

#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include <math.h>

typedef struct CARRO{
    int x;	
    int y;	
    int largura;	
    int altura;	
    int angulo;
    BITMAP *spr;
} CARRO;

typedef struct MAPA{   
    int largura; 
    int altura;
    int matriz[24][32];
    BITMAP *spr;
} MAPA;

typedef struct CONSTR_MENU{   
    int objs[32];
} CONSTR_MENU;

#endif
