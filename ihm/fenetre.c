//
// Created by joseph on 16/03/16.
//

#include "fenetre.h"

#include <stdio.h>

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

	int continuer = 1;
	SDL_Event event;
	while(continuer)
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT)
		{
			continuer = 0;
		}
		SDL_Delay(10);
	}
	return 0;
}

void deleteFenetre(Fenetre* fenetre)
{
	SDL_Quit();
}