//
// Created by joseph on 16/03/16.
//

#include "dataBuffer.h"
#include "fenetre.h"

int main()
{
	//setbuf(stdout, NULL);
	//DataBuffer spo2, bpm, acr, acir;
	/*initBuffer(&spo2);
	initBuffer(&bpm);
	initBuffer(&acr);
	initBuffer(&acir);*/

	Fenetre fenetre;
	if(initFenetre(&fenetre) == -1)
	{
		return -1;
	}

	deleteFenetre(&fenetre);
	return 0;
}