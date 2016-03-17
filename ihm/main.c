//
// Created by joseph on 16/03/16.
//

#include "dataBuffer.h"
#include "fenetre.h"
#include "lecture.h"

int main()
{
	setbuf(stdout, NULL);

	DataBuffer spo2, bpm, acr, acir;
	initBuffer(&spo2);
	initBuffer(&bpm);
	initBuffer(&acr);
	initBuffer(&acir);

	Fenetre fenetre;
	if(initFenetre(&fenetre) == -1)
	{
		return -1;
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
		clearFenetre(&fenetre);

		Mesures m;
		getMesures(&m);

		pushBackBuffer(&spo2, m.spo2);
		pushBackBuffer(&bpm, m.bpm);
		pushBackBuffer(&acr, m.acr);
		pushBackBuffer(&acir, m.acir);

		drawCourbe(&fenetre, 1, &spo2);
		drawCourbe(&fenetre, 2, &bpm);
		drawCourbe(&fenetre, 3, &acr);
		drawCourbe(&fenetre, 4, &acir);
		SDL_Flip(fenetre.screen);
	}

	deleteFenetre(&fenetre);
	return 0;
}