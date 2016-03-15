#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"
#include "firPB.h"
#include "iirPH.h"
#include "mesure.h"
#include "lecture.h"
#include "affichage.h"
#include "dataBuffer.h"


int main(int argc, char const *argv[])
{
	Absorp absorb;
	DataBuffer buffer;
	Oxy oxyDatas;
	int reussite, continuer, err, bpm, rsIR, typeSrc;
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
	char* src;

	initDataBuffer(&buffer);
	reussite = 0;
	continuer = 1;
	err = 0;
	bpm = 0;
	rsIR = 0;
	typeSrc = 0;

	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;

	if(argc == 1){
		src = argv[0];
		typeSrc = 1;
	}else{
		src = "";
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

			absorb.acR = acRPH;
			absorb.acIR = acIRPH;
			mesure(&bpm, &rsIR, absorb);

			oxyDatas.spo2 = rsIR;
			oxyDatas.pouls = bpm;
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