//
// Created by joseph on 16/03/16.
//

#include "dataBuffer.h"
#include "fenetre.h"
#include "lecture.h"

#define TEMPS_ACQUISITION 10

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);

	DataBuffer spo2, bpm, acr, acir;
	initBuffer(&spo2);
	initBuffer(&bpm);
	initBuffer(&acr);
	initBuffer(&acir);

	int tempsPrecedent = 0, tempsActuel = 0;

	Fenetre fenetre;
	if(initFenetre(&fenetre) == -1)
	{
		return -1;
	}

	int continuer = 1;
	SDL_Event event;
	while(continuer)
	{
		tempsActuel = SDL_GetTicks();
		
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			continuer = 0;
		}
		
		if(tempsActuel - tempsPrecedent > TEMPS_ACQUISITION)
		{
			clearFenetre(&fenetre);

			Mesures m;
			getMesures(&m);

			pushBackBuffer(&spo2, m.spo2);
			pushBackBuffer(&bpm, m.bpm);
			pushBackBuffer(&acr, m.acr);
			pushBackBuffer(&acir, m.acir);

			drawCourbe(&fenetre, 1, &spo2, COURBE_HAUTEUR / 2 - 1);
			drawCourbe(&fenetre, 2, &bpm, COURBE_HAUTEUR / 2 - 1);
			drawCourbe(&fenetre, 3, &acr, 0);
			drawCourbe(&fenetre, 4, &acir, 0);

			drawValeurs(&fenetre, fenetre.txtSpo2, m.spo2, "%d %%", fenetre.colorSpo2, 1);
			drawValeurs(&fenetre, fenetre.txtBpm, m.bpm, "%d", fenetre.colorBpm, 2);
			drawValeurs(&fenetre, fenetre.txtAcr, m.acr, "%d", fenetre.colorAcr, 3);
			drawValeurs(&fenetre, fenetre.txtAcir, m.acir, "%d", fenetre.colorAcir, 4);
			SDL_Flip(fenetre.screen);

			tempsPrecedent = tempsActuel;
		}
		else
		{
			SDL_Delay(TEMPS_ACQUISITION - (tempsActuel - tempsPrecedent));
			//printf("%d\n", TEMPS_ACQUISITION - (tempsActuel - tempsPrecedent));
		}
	}

	deleteFenetre(&fenetre);
	return 0;
}