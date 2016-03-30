#include "iir.h"

float iir(float ac, float acPrec, float acPHPrec){
	return ac - acPrec + ALPHA * acPHPrec;
}

absorp iirTest(char* str){
	absorp absorb;
	float acRPH, acRPHPrec, acRPB, acRPBPrec, acIRPH, acIRPHPrec, acIRPB, acIRPBPrec;
	char x, y;

	FILE* ficOTest = fopen("testIirOutput", "w+");

	FILE* pf = fopen(str, "r");
	if(!pf){
		printf("Le fichier n'a pu être lu.\n");
		return absorb;
	}

	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;

	do{
		fscanf(pf, "%f,%f,%f,%f,%c,%c", &acRPB, &absorb.dcr, &acIRPB, &absorb.dcir, &x, &y);

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
