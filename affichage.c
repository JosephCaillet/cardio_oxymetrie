/*--------------------------------------------------------------------------*/
/*--							Affichage v2							  --*/
/*--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "affichage.h"

void affichage(Oxy oxyDatas){

	FILE *verrou = NULL;
	FILE *data = NULL;

	if(access(".verrouData", F_OK) == -1){
		verrou = fopen(".verrouData", "w");

		data = fopen("Data.txt", "w+");
		if(data != NULL){
			fprintf(data, "%f\n%d", oxyDatas.spo2, oxyDatas.pouls);

			fclose(data);
		}

		fclose(verrou);
		remove(".verrouData");
	}

	return;
}