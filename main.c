#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"
#include "firPB.h"
#include "iirPH.h"
#include "mesure.h"
#include "lecture.h"
#include "affichage.h"
#include "dataBuffer.h"


int main(int argc, char* argv[])
{
	Absorp absorb;
	DataBuffer buffer;
	Oxy oxyDatas;
	int reussite, continuer, err, typeSrc;
	float acRPB, acRPBPrec, acRPH, acRPHPrec, acIRPB, acIRPBPrec, acIRPH, acIRPHPrec;
	/*
	acRPB - acR filtré passe bas
	acRPBPrec - acR filtré passe bas précedent
	acRPH - acR filtré passe haut
	acRPHPrec  - acR filtré passe haut précedent
	
	acIRPB - acIR filtré passe bas
	acIRPBPrec - acIr filtré passe bas précedent
	acIRPH - acIR filtré passe haut
	acIRPHPrec - acIR passe haut précedent
	*/
	void* src;

	initDataBuffer(&buffer);
	reussite = 0;
	continuer = 1;
	err = 0;
	typeSrc = 0;

	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;

	if(argc == 1){
		src = fopen(argv[1], "r");
		if(src == NULL)
		{
			printf("Impossible ouvrir fichier source.");
			exit(1);
		}
		typeSrc = 1;
	}else{
		src = NULL;/*remplacer par usb*/
		typeSrc = 0;
	}

	while(continuer){

		reussite = lecture(src, typeSrc, &absorb);

		if(reussite == 0){
			err = 0;

			push_front(&buffer, absorb);
			acRPBPrec = acRPB;
			acIRPBPrec = acIRPB;

			firPB(&buffer, &acRPB, &acIRPB);

			acRPHPrec = acRPH;
			acRPH = iirPH(acRPB, acRPBPrec, acRPHPrec);

			acIRPHPrec = acIRPH;
			acIRPH = iirPH(acIRPB, acIRPBPrec, acIRPHPrec);

			absorb.acr = acRPH;
			absorb.acir = acIRPH;
			mesure(&oxyDatas, absorb);

			affichage(oxyDatas);
		}else if(reussite == 1){
			err++;

			if(err >= 10){
				continuer = 0;
			}
		}else{
			continuer = 0;
		}

	}

	return 0;
}