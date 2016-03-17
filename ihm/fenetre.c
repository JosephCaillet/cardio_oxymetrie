//
// Created by joseph on 16/03/16.
//

#include <stdio.h>
#include <stdlib.h>

#include "fenetre.h"

int initFenetre(Fenetre* fenetre)
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		puts("Erreur chargement SDL.");
		return -1;
	}

	putenv("SDL_VIDEO_CENTERED=1");
	fenetre->screen = SDL_SetVideoMode(FENETRE_LARGEUR, FENETRE_HAUTEUR, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(fenetre->screen == NULL)
	{
		puts("Erreur création fenetre.");
	}

	SDL_WM_SetCaption("Oxymètre de pouls", NULL);

	if(TTF_Init() == -1)
	{
		puts("Erreur chargement SDL_ttf.");
		return -1;
	}

	fenetre->pxSPO2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
	fenetre->pxBPM = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
	fenetre->pxACR = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
	fenetre->pxACIR = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
	fenetre->bgCourbe = SDL_CreateRGBSurface(SDL_HWSURFACE, COURBE_LONGUEUR, COURBE_HAUTEUR, 32, 0, 0, 0, 0);
	fenetre->zeroCourbe = SDL_CreateRGBSurface(SDL_HWSURFACE, COURBE_LONGUEUR, 1, 32, 0, 0, 0, 0);

	SDL_FillRect(fenetre->pxSPO2, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_SPO2));
	SDL_FillRect(fenetre->pxBPM, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_BPM));
	SDL_FillRect(fenetre->pxACR, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_ACR));
	SDL_FillRect(fenetre->pxACIR, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_ACIR));
	SDL_FillRect(fenetre->bgCourbe, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_FOND_COURBE));
	SDL_FillRect(fenetre->zeroCourbe, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_ZERO_COURBE));

	return 0;
}

void deleteFenetre(Fenetre* fenetre)
{
	TTF_Quit();
	SDL_FreeSurface(fenetre->pxSPO2);
	SDL_FreeSurface(fenetre->pxBPM);
	SDL_FreeSurface(fenetre->pxACR);
	SDL_FreeSurface(fenetre->pxACIR);
	SDL_FreeSurface(fenetre->bgCourbe);
	SDL_FreeSurface(fenetre->zeroCourbe);
	SDL_Quit();
}

void clearFenetre(Fenetre* fenetre)
{
	SDL_FillRect(fenetre->screen, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_FOND_ECRAN));

	SDL_Rect pos;
	pos.x = COURBE_OFFSET_X;
	pos.y = COURBE_OFFSET_Y / 2;

	for(int i = 0; i < 4; i++)
	{
		SDL_BlitSurface(fenetre->bgCourbe, NULL, fenetre->screen, &pos);
		pos.y += COURBE_HAUTEUR / 2;
		SDL_BlitSurface(fenetre->zeroCourbe, NULL, fenetre->screen, &pos);
		pos.y += COURBE_HAUTEUR / 2 + COURBE_OFFSET_Y;
	}
}

void drawCourbe(Fenetre* fenetre, int numCourbe, DataBuffer* dataBuffer)
{
	SDL_Rect pos;
	pos.x = COURBE_OFFSET_X;
	int y = (COURBE_OFFSET_Y + COURBE_HAUTEUR) * ( 0.5 + numCourbe-1);

	SDL_Surface* px = NULL;
	float coeff = 0;

	switch(numCourbe)
	{
		case 1:
			px = fenetre->pxSPO2;
			coeff = COEFF_BPM;
			break;
		case 2:
			px = fenetre->pxBPM;
			coeff = COEFF_BPM;
			break;
		case 3:
			px = fenetre->pxACR;
			coeff = COEFF_ACR;
			break;
		case 4:
			px = fenetre->pxACIR;
			coeff = COEFF_ACIR;
			break;
	}

	for(int i = 0; i < COURBE_LONGUEUR; i++)
	{
		pos.y = y + atBuffer(dataBuffer, i) * coeff;
		SDL_BlitSurface(px, NULL, fenetre->screen, &pos);
		pos.x++;
	}
}