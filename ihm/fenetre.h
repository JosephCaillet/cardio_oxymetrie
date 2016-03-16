//
// Created by joseph on 16/03/16.
//

#ifndef IHM_FENETRE_H
#define IHM_FENETRE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#define FENETRE_HAUTEUR 900
#define FENETRE_LARGEUR 1000

struct Fenetre
{
	SDL_Surface* screen;
};
typedef struct Fenetre Fenetre;

int initFenetre(Fenetre* fenetre);
void deleteFenetre(Fenetre* fenetre);

#endif //IHM_FENETRE_H