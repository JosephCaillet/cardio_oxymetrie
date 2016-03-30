//
// Created by joseph on 17/03/16.
//

#include "lecture.h"
#include <stdio.h>
#include <unistd.h>

void getMesures(Mesures* mesures)
{
	/*static int spo2 = 0;
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
return;*/
	/*mesures->spo2 = 0;
	mesures->bpm = 0;
	mesures->acr = 0;
	mesures->acir = 0;*/

	FILE *verrou = NULL;
	FILE *data = NULL;

	//char ligne[5] = "";

	if(access(VERROU_FILE_1, F_OK) == -1){
		verrou = fopen(VERROU_FILE_1, "w");

		data = fopen(DATA_FILE_1, "r");
		if(data != NULL){
			fscanf(data, "%d\n", &mesures->spo2); 
			fscanf(data, "%d", &mesures->bpm);
			fclose(data);
		}

		fclose(verrou);
		remove(VERROU_FILE_1);
	}

	if(access(VERROU_FILE_2, F_OK) == -1){
		verrou = fopen(VERROU_FILE_2, "w");

		data = fopen(DATA_FILE_2, "r");
		if(data != NULL){
			fscanf(data, "%d\n", &mesures->acr); 
			fscanf(data, "%d", &mesures->acir);
			fclose(data);
		}

		fclose(verrou);
		remove(VERROU_FILE_2);
	}

	return;
}