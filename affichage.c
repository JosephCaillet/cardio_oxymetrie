/*--------------------------------------------------------------------------*/
/*--							Affichage v2							  --*/
/*--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "affichage.h"

void affichage(oxy oxyDatas){

	FILE *verrou = NULL;
	FILE *data = NULL;

	if(access(".verrouData", F_OK) == -1){
		verrou = fopen(".verrouData", "w");

		data = fopen("Data.txt", "w+");
		if(data != NULL){
			fprintf(data, "%d\n%d", oxyDatas.spo2, oxyDatas.pouls);

			fclose(data);
		}

		fclose(verrou);
		remove(".verrouData");
	}

	return;
}

void affichage2(float acr, float acir)
{
	FILE *verrou = NULL;
	FILE *data = NULL;

	if(access(".verrouData2", F_OK) == -1){
		verrou = fopen(".verrouData2", "w");

		data = fopen("Data2.txt", "w+");
		if(data != NULL){
			fprintf(data, "%d\n%d", (int)acr, (int)acir);

			fclose(data);
		}

		fclose(verrou);
		remove(".verrouData2");
	}

	return;
}
