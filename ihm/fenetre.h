//
// Created by joseph on 16/03/16.
//

#ifndef IHM_FENETRE_H
#define IHM_FENETRE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "dataBuffer.h"

#define FENETRE_HAUTEUR 800
#define FENETRE_LARGEUR 1000

#define COURBE_LONGUEUR TAILLE_BUFFER
#define COURBE_HAUTEUR 150
#define COURBE_OFFSET_Y 50
#define COURBE_OFFSET_X FENETRE_LARGEUR - COURBE_LONGUEUR - COURBE_OFFSET_Y / 2

#define TEXTE_OFFSET_X COURBE_OFFSET_X / 2
#define TEXTE_GAP_Y 20

#define COULEUR_SPO2 255,0,0
#define COULEUR_BPM 0,255,0
#define COULEUR_ACR 0,0,255
#define COULEUR_ACIR 0,0,255
#define COULEUR_FOND_ECRAN 200,200,200
#define COULEUR_FOND_COURBE 50,50,50
#define COULEUR_ZERO_COURBE 200,200,200

#define COEFF_SPO2 0.036
#define COEFF_BPM 0.036
#define COEFF_ACR 0.036
#define COEFF_ACIR 0.036

struct Fenetre
{
	SDL_Surface* screen;
	SDL_Surface* pxSPO2;
	SDL_Surface* pxBPM;
	SDL_Surface* pxACR;
	SDL_Surface* pxACIR;
	SDL_Surface* bgCourbe;
	SDL_Surface* zeroCourbe;
};
typedef struct Fenetre Fenetre;

int initFenetre(Fenetre* fenetre);
void deleteFenetre(Fenetre* fenetre);
void clearFenetre(Fenetre* fenetre);
void drawCourbe(Fenetre* fenetre, int numCourbe, DataBuffer* dataBuffer);

#endif //IHM_FENETRE_H