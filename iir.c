#include "iir.h"

float iir(float ac, float acPrec, float acPHPrec){
	return ac - acPrec + ALPHA * acPHPrec;
}

absorp iirTest(char* str){
	absorp absorb;
	float acRPH, acRPHPrec, acRPB, acRPBPrec, acIRPH, acIRPHPrec, acIRPB, acIRPBPrec;
	int x, y;

	File* pf = fopen(str, "r");
	if(!pf){
		printf("Le fichier n'a pu être lu.\n");
		return absorb;
	}

	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;

	do{
		fscanf(pf, "%d,%d,%d,%d,%c,%c", &absorb.acr, &absorb.dcr, &absorb.acir, &absorb.dcir, &x, &y);;

		acRPHPrec = acRPH;
		acIRPHPrec = acIRPH;
		acRPBPrec = acRPB;
		acIRPBPrec = acIRPB;


		if(!feof(pf)){
			acRPH = iir(acRPB, acRPBPrec, acRPHPrec);
			acIRPH = iir(acIRPB, acIRPBPrec, acIRPHPrec);

			absorb.acr = acRPH;
			absorb.acir = acIRPH;
		}
	}while(!feof(pf));
	
	return absorb;
}
