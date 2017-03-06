//
// Created by joseph on 16/03/16.
//

#include <string.h>

#include "dataBuffer.h"
#include "fenetre.h"
#include "lecture.h"
#include "button.h"

#define TEMPS_ACQUISITION 20

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);

	bool displayACinfo = true;
	DataBuffer spo2, bpm, acr, acir;
	initBuffer(&spo2);
	initBuffer(&bpm);
	initBuffer(&acr);
	initBuffer(&acir);

	int tempsPrecedent = 0, tempsActuel = 0, souriRelachee = 0;

	Fenetre fenetre;

	printf("%d\n", argc);
	if(argc == 2 && strcmp(argv[1], "--hideACvalues") == 0)
	{
		displayACinfo = false;
	}


	if(initFenetre(&fenetre, displayACinfo) == -1)
	{
		return -1;
	}

	int continuer = 1;
	SDL_Event event;
	while(continuer)
	{
		tempsActuel = SDL_GetTicks();
		
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(souriRelachee == 1)
				{
					souriRelachee = 0;
					
					if(updButtonState(&fenetre.alarmeBas, &event) == 0)
					{
						updButtonState(&fenetre.alarmeHaut, &event);
					}
					tempsPrecedent = SDL_GetTicks();
				}
				break;
			case SDL_MOUSEBUTTONUP:
				souriRelachee = 1;
				break;
			case SDL_KEYDOWN:
				updEasterState(&fenetre, &event, 1);
				break;
			case SDL_KEYUP:
				updEasterState(&fenetre, &event, 0);
				break;

		}
		
		if(tempsActuel - tempsPrecedent > TEMPS_ACQUISITION)
		{
			Mesures m;
			getMesures(&m);

			if(m.bpm < fenetre.alarmeBas.value || m.bpm > fenetre.alarmeHaut.value)
			{
				fenetre.statusAlarme = 1;
			} 
			else
			{
				fenetre.statusAlarme = 0;
			}

			updFenetreTitre(&fenetre);
			clearFenetre(&fenetre);

			pushBackBuffer(&spo2, m.spo2);
			pushBackBuffer(&bpm, m.bpm);
			pushBackBuffer(&acr, m.acr);
			pushBackBuffer(&acir, m.acir);

			drawCourbe(&fenetre, 1, &spo2, COURBE_HAUTEUR / 2 - 1);
			drawCourbe(&fenetre, 2, &bpm, COURBE_HAUTEUR / 2 - 1);
			drawCourbe(&fenetre, 3, &acr, 0);
			drawCourbe(&fenetre, 4, &acir, 0);

			drawValeurs(&fenetre, fenetre.txtSpo2, m.spo2, " %d %% ", fenetre.colorSpo2, 1);
			drawValeurs(&fenetre, fenetre.txtBpm, m.bpm, " %d ", fenetre.colorBpm, 2);
			drawValeurs(&fenetre, fenetre.txtAcr, m.acr, " %d ", fenetre.colorAcr, 3);
			drawValeurs(&fenetre, fenetre.txtAcir, m.acir, " %d ", fenetre.colorAcir, 4);
			
			drawButton(&(fenetre.alarmeBas));
			drawButton(&(fenetre.alarmeHaut));

			doSomeMagic(&fenetre);
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