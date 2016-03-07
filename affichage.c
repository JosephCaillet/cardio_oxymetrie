#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"

void affichage(int bpm, float rsIR){
	File *verrou = NULL;
	File *data = NULL²;

	verrou = fopen(".verrouData", "r");

	if(verrou == NULL){
		verrou = fopen(".verrouData", "w");

		data = fopen("Data.txt", "w+");
		if(data != NULL){
			fprintf(data, "%d\n%d", rsIR, bpm);

			fclose(data);
		}

		fclose(verrou);
	}

	remove(".verrouData");

	return;
}