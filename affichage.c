#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"

void affichage(int bpm, float rsIR){
	File *verrou = null;
	File *data = null;

	verrou = fopen(".verrouData", "r");

	if(verrou == null){
		verrou = fopen(".verrouData", "w");

		data = fopen("Data.txt", "w+");
		if(data != null){
			fprintf(data, "%d\n%d", rsIR, bpm);

			fclose(data);
		}

		fclose(verrou);
	}

	remove(".verrouData");

	return;
}