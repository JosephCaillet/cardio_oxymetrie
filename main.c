#include <stdio.h>
#include <stdlib.h>
#include "lecture.c"
#include "firPB.c"
#include "iirPH.c"
#include "mesure.c"
#include "affichage.c"
#include "dataBuffer.c"


int main(int argc, char const *argv[])
{
	Data acData;
	DataBuffer buffer;
	int reussite, acRPB, acRPBPrec, acRPH, acRPHPrec, acIRPB, acIRPBPrec, acIRPH, acIRPHPrec, dcR, dcIR, bpm, continuer, err, typeSrc;
	float rsIR;
	String src;

	initDataBuffer(&buffer);
	continuer = 1;
	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;
	err = 0;

	if(argc == 1){
		src = argv[0];
		typeSrc = 1;
	}else{
		src = "";
		typeSrc = 0;
	}

	while(continuer){

		reussite = lecture(src, typeSrc, &acData, &dcR, &dcIR);

		if(reussite == 0){
			err = 0;

			push_front(&buffer, acData);
			acRPBPrec = acRPB;
			acIRPBPrec = acIRPB;

			firPB(&buffer, &acRPB, &acIRPB);

			acRPHPrec = acRPH;
			acRPH = iirPH(acRPB, acRPBPrec, acRPHPrec);

			acIRPHPrec = acIRPH;
			acIRPH = iirPH(acIRPB, acIRPBPrec, acIRPHPrec);

			mesure(&bpm, &rsIR, acRPH, acIRPH, dcR, dcIR);

			affichage(bpm, rsIR);
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