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

	getDataFromFile(DATA_FILE_1, VERROU_FILE_1, &mesures->spo2, &mesures->bpm);
	getDataFromFile(DATA_FILE_2, VERROU_FILE_2, &mesures->acr, &mesures->acir);

	return;
}

void getDataFromFile(char* dataFileName, char* verrouFileName, int* value1, int* value2)
{
	FILE* verrou = NULL;
	FILE* data = NULL;

	if(access(verrouFileName, F_OK) == -1){
		verrou = fopen(verrouFileName, "w");

		data = fopen(dataFileName, "r");
		if(data != NULL){
			fscanf(data, "%d", value1);
			fscanf(data, "%d", value2);
			fclose(data);
		}

		fclose(verrou);
		remove(verrouFileName);
	}
}