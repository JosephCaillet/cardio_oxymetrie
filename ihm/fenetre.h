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

#define POINT_HAUTEUR 1
#define POINT_LARGEUR 1

#define TEXTE_OFFSET_X (COURBE_OFFSET_X) / 2
#define TEXTE_GAP_Y 50

#define COULEUR_SPO2_R 255
#define COULEUR_SPO2_V 0
#define COULEUR_SPO2_B 0
#define COULEUR_SPO2 COULEUR_SPO2_R, COULEUR_SPO2_V, COULEUR_SPO2_B

#define COULEUR_BPM_R 0
#define COULEUR_BPM_V 255
#define COULEUR_BPM_B 0
#define COULEUR_BPM COULEUR_BPM_R, COULEUR_BPM_V, COULEUR_BPM_B

#define COULEUR_ACR_R 0
#define COULEUR_ACR_V 0
#define COULEUR_ACR_B 255
#define COULEUR_ACR COULEUR_ACR_R, COULEUR_ACR_V, COULEUR_ACR_B

#define COULEUR_ACIR_R 0
#define COULEUR_ACIR_V 0
#define COULEUR_ACIR_B 255
#define COULEUR_ACIR COULEUR_ACIR_R, COULEUR_ACIR_V, COULEUR_ACIR_B

#define COULEUR_FOND_ECRAN_R 150
#define COULEUR_FOND_ECRAN_V 150
#define COULEUR_FOND_ECRAN_B 150
#define COULEUR_FOND_ECRAN COULEUR_FOND_ECRAN_R, COULEUR_FOND_ECRAN_V, COULEUR_FOND_ECRAN_B

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

	TTF_Font* font;
	SDL_Surface* txtSpo2;
	SDL_Surface* txtBpm;
	SDL_Surface* txtAcr;
	SDL_Surface* txtAcir;

	SDL_Color colorSpo2;
	SDL_Color colorBpm;
	SDL_Color colorAcr;
	SDL_Color colorAcir;
	SDL_Color colorFondEcran;
};
typedef struct Fenetre Fenetre;

int initFenetre(Fenetre* fenetre);
void deleteFenetre(Fenetre* fenetre);
void clearFenetre(Fenetre* fenetre);
void drawCourbe(Fenetre* fenetre, int numCourbe, DataBuffer* dataBuffer);
void drawValeurs(Fenetre* fenetre, SDL_Surface* label, int valeur, char* txt, SDL_Color couleur, int num);

#endif //IHM_FENETRE_H