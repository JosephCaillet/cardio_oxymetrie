//
// Created by joseph on 17/03/16.
//

#include "lecture.h"
#include <stdio.h>

void getMesures(Mesures* mesures)
{
	static int spo2 = 0;
	static int sens = 1;

	if(spo2 >= 150)
	{
		sens = -1;
	}
	else if(spo2 <= -150)
	{
		sens = 1;
	}

	spo2 += sens*5;

	mesures->spo2 = spo2;
	mesures->bpm = spo2;
	mesures->acr = spo2;
	mesures->acir = spo2;
}