/*--------------------------------------------------------------------------*/
/*--							Affichage v2							  --*/
/*--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "affichage.h"

void affichage(oxy oxyDatas){
	printInFile("Data.txt", ".verrouData", oxyDatas.spo2, oxyDatas.pouls);
	return;
}

void affichage2(float acr, float acir)
{
	printInFile("Data2.txt", ".verrouData2", (int)acr, (int)acir);
	return;
}

void printInFile(char* dataFileName, char* verrouFileName, int value1, int value2)
{
	FILE *verrou = NULL;
	FILE *data = NULL;

	if(access(verrouFileName, F_OK) == -1){
		verrou = fopen(verrouFileName, "w");

		data = fopen(dataFileName, "w+");
		if(data != NULL){
			fprintf(data, "%d\n%d", value1, value2);

			fclose(data);
		}

		fclose(verrou);
		remove(verrouFileName);
	}

	return;
}