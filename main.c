#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "lecture.h"
#include "lectureUSB.h"
#include "affichage.h"
#include "dataBuffer.h"


int main(int argc, char* argv[])
{
	absorp absorb;
	DataBuffer buffer;
	oxy oxyDatas;
	int typeSrc, eof = 42;
	//int lastBpm = 0;
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
	FILE* src = NULL;
	FT_HANDLE ftHandle;
	FT_STATUS ftStatus;

	AcMesures acRm = {0,0,0, 0,0, SEUIL_BAS,0,SEUIL_HAUT,0, 0.0, "R"};
	AcMesures acIRm = {0,0,0, 0,0, SEUIL_BAS,0,SEUIL_HAUT,0, 0.0, "IR"};

	initDataBuffer(&buffer);
	typeSrc = 0;

	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;

	if(argc == 2){
		src = fopen(argv[1], "r");
		if(src == NULL)
		{
			printf("Impossible ouvrir fichier source.");
			exit(1);
		}
		typeSrc = 1;
	}else{
		ftStatus = FT_Open(0, &ftHandle);
		if(ftStatus != FT_OK)
		{
			puts("Impossible d'ouvrir l'USB.");
			return 1;
		}
		typeSrc = 0;
	}

	while(eof != EOF){
		if(typeSrc == 1){
			absorb = lecture(src, &eof);
		}
		else
		{
			//puts("a");
			absorb = lectureUsb(ftHandle);
		}

		if(eof != EOF){
			//puts("o");
			push_front(&buffer, absorb);
			acRPBPrec = acRPB;
			acIRPBPrec = acIRPB;

			fir(&buffer, &acRPB, &acIRPB);

			acRPHPrec = acRPH;
			acRPH = iir(acRPB, acRPBPrec, acRPHPrec);

			acIRPHPrec = acIRPH;
			acIRPH = iir(acIRPB, acIRPBPrec, acIRPHPrec);

			absorb.acr = acRPH;
			absorb.acir = acIRPH;
			mesure(&oxyDatas, absorb, &acRm, &acIRm);

			//oxyDatas.pouls += lastBpm;
			//oxyDatas.pouls /= 2;

			printf("%d\t%d\n", oxyDatas.pouls, oxyDatas.spo2);
			affichage(oxyDatas);
			affichage2(absorb.acr, absorb.acir);
			if(typeSrc == 1){
				usleep(2000);
			}
			//lastBpm = oxyDatas.pouls;
		}

	}

	return 0;
}
