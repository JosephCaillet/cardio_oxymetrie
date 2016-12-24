/*==============================================================================================================*/
/*	Nom : 		integration.c																					*/
/*	Auteur : 	Thomas COUSSOT																					*/
/*	Desc : 		Lit des donnes depuis un fichier pour simuler la carte.											*/
/*==============================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "lecture.h"
#include "affichage.h"
#include "dataBuffer.h"


/*------------------------------------------------------------------------------*/
/*	Fonction : 	integrationTest													*/
/*	Params :	char* fileName													*/
/*	Retour :	ras																*/
/*	Desc :		La fonction permet de tester l'ensemble des blocs.				*/
/*------------------------------------------------------------------------------*/
void integrationTest(char* fileName){
	absorp absorb;
	DataBuffer buffer;
	oxy oxyDatas;
	int reussite, continuer, err, typeSrc, eof;
	
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

	AcMesures acRm = {0,0,0, 0,0, SEUIL_BAS,0,SEUIL_HAUT,0, 0.0, "R"};//initialisation des memoires intermediaires
	AcMesures acIRm = {0,0,0, 0,0, SEUIL_BAS,0,SEUIL_HAUT,0, 0.0, "IR"};

	initDataBuffer(&buffer);//init buffer
	typeSrc = 0;

	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;

	src = fopen(fileName, "r");//ouverture source
	if(src == NULL)
	{
		printf("Impossible ouvrir fichier source.");
		exit(1);
	}
	typeSrc = 1;

	while(eof != EOF){//tant que fin fichier non atteinte

		if(typeSrc == 1){
			absorb = lecture(src, &eof);//aquisition des données
		}

		if(eof != EOF){
			push_front(&buffer, absorb);//mise a jour historique valeurs brutes
			acRPBPrec = acRPB;
			acIRPBPrec = acIRPB;

			fir(&buffer, &acRPB, &acIRPB);//filtrage fir

			acRPHPrec = acRPH;
			acRPH = iir(acRPB, acRPBPrec, acRPHPrec);//filtrage iir acR

			acIRPHPrec = acIRPH;
			acIRPH = iir(acIRPB, acIRPBPrec, acIRPHPrec);//filtrage iir acIR

			absorb.acr = acRPH;
			absorb.acir = acIRPH;
			mesure(&oxyDatas, absorb, &acRm, &acIRm);//calcul spo2 et bpm


			printf("%d\t%d\n", oxyDatas.pouls, oxyDatas.spo2);
			affichage(oxyDatas);//ecriture ds fichier
		}

	}

	return;
}
