#include "mesure.h"
#include <stdio.h>

void mesure(oxy* oxy, absorp absorp, AcMesures* acRm, AcMesures* acIRm)
{
	int periodeAquise = 0;
	//static int mesure = 0;

	//majMaxMinSeuil
	majMaxMinDepasseSeuil(acRm, absorp.acr);
	majMaxMinDepasseSeuil(acIRm, absorp.acir);

	//upd passage par 0
	majPassageZero(acRm, absorp.acr);
	majPassageZero(acIRm, absorp.acir);

	//updBpm
	periodeAquise += majBpm(acRm, absorp.acr);
	periodeAquise += majBpm(acIRm, absorp.acir);

	//updSPo2	
	if(periodeAquise > 0)
	{
//		puts("Avant spo2 :");
//		printf("acRmax : %f, acRmin : %f\nacIRmax : %f, acIRmin : %f\ndcR : %f, dcIR : %f\n", acRm->maxValid, acRm->minValid, acIRm->maxValid, acIRm->minValid, absorp.dcr, absorp.dcir);
		oxy->spo2 = calculSPo2(acRm->maxValid, acRm->minValid, acIRm->maxValid, acIRm->minValid, absorp.dcr, absorp.dcir);
		oxy->pouls = (acRm->bpm + acIRm->bpm) / 2.0f;
		//printf("Rbmp: %f - IRbmp: %f\n", acRm->bpm, acIRm->bpm);
		//printf("ACR: %f - ACIR: %f\n", absorp.acr, absorp.acir);
		//printf("-- Absorb --\nacr : %f\ndcr : %f\nacir : %f\ndcir : %f\n", absorp.acr, absorp.dcr, absorp.acir, absorp.dcir);
	}
	//printf("%d --- ", ++mesure);
}
//85spo2
//70bpm

void majMaxMinDepasseSeuil(AcMesures* ac, int acNew)
{
	if(acNew > ac->max)
	{
		ac->max = acNew;
		ac->seuilHautPasse = 1;
		//ac->min = SEUIL_BAS;
	}
	else if(acNew < ac->min)//On veux faire les vérif sur un seuil bas précédé d'un seuil haut.
	{
		ac->min = acNew;
		ac->seuilBasPasse = 1;
		//ac->max = SEUIL_HAUT;
	}
}

void majPassageZero(AcMesures* ac, int acNew)
{
	/*if(ac->lastValue * acNew < 0)
	{
		ac->passagePar0++;
		printf("Passage par zéro n° %d pour %s - old : %d new : %d\n", ac->passagePar0, ac->s, ac->lastValue, acNew);
	}*/

	if(ac->lastValue > 0 && acNew < 0)
	{
		ac->maxValid = ac->max;
		ac->max = SEUIL_HAUT;
	}
	else if(ac->lastValue < 0 && acNew > 0)
	{
		ac->minValid = ac->min;
		ac->min = SEUIL_BAS;
	}

	ac->lastValue = acNew;
}

int majBpm(AcMesures* ac, float ech_ac)
{
	static float lastbpm = 425;
	//if(ac->seuilBasPasse == 1 && ac->seuilHautPasse == 1 && ac->passagePar0 > 2)//Si on est passé par le seuil bas, implique passage seuil haut.
	if(ech_ac < SEUIL_BAS && ac->seuilHautPasse == 1)//Si on est passé par le seuil bas, implique passage seuil haut.
	{
//		printf("Une période à été aquise sur : %s\n", ac->s);
		//affAcMesure(*ac);
		
		ac->seuilHautPasse = 0;
		ac->seuilBasPasse = 0;
		//ac->passagePar0 = 1;

		//ac->min = SEUIL_BAS;
		//ac->max = SEUIL_HAUT;

		//ac->bpm = (float)30000 / (float)ac->nbPoints;
//		ac->bpm = (((float)30000 / (float)ac->nbPoints) + lastbpm) / 2.0  ;
//		lastbpm = ac->bpm;
		ac->bpm = (float)30000 / (((float)ac->nbPoints + (float)lastbpm)/2)  ;
		printf("cpt : %d\tcpt_old : %1f\tbpm : %f\tbpm_old : %f\tbpm_moy : %f\n", ac->nbPoints, lastbpm, (float)30000/(float)ac->nbPoints, (float)30000/(float)lastbpm, ac->bpm);
		lastbpm = ac->nbPoints;
		ac->nbPoints = 1;
		
		return 1;
	}

	ac->nbPoints++;

	return 0;
}

float calculSPo2(float acRmax, float acRmin, float acIRmax, float acIRmin, float dcR, float dcIR)
{
	//puts("Ds spo2 :");
	//printf("acRmax : %f, acRmin : %f\nacIRmax : %f, acIRmin : %f\ndcR : %f, dcIR : %f\n", acRmax, acRmin, acIRmax, acIRmin, dcR, dcIR);
	float ptpACr = acRmax - acRmin;
	float rapport1 = ptpACr / dcR;
//	printf("le rapport1 vaut : %f\n", rapport1);

	float ptpACir = acIRmax - acIRmin;
	float rapport2 = ptpACir / dcIR;
//	printf("le rapport2 vaut : %f\n", rapport2);

//	printf("le ratio vaut : %f\n", rapport1 / rapport2);
	return  convertRatioToSPO2( rapport1 / rapport2 );
}

float convertRatioToSPO2(float ratio)
{
	if(ratio < 1)
	{
		return -25 * ratio + 110;
	}
	return -35.71429 * ratio + 121.4285714;
}

void affAcMesure(AcMesures ac)
{
	printf("-- %s --\n", ac.s);
	printf("SeuilHautPasse : %d\n", ac.seuilHautPasse);
	printf("SeuilBasPasse : %d\n", ac.seuilBasPasse);

	printf("LastValue : %d\n", ac.lastValue);
	printf("NbPoints: %d\n", ac.nbPoints);

	printf("Min : %f\n", ac.min);
	printf("Max : %f\n", ac.max);
}

oxy mesureTest(char* str){
	oxy oxyDatas;
	absorp absorb;
	AcMesures acRm = {0,0,0, 0,0, SEUIL_BAS,SEUIL_BAS,SEUIL_HAUT,SEUIL_HAUT, 0.0, "R"};
	AcMesures acIRm = {0,0,0, 0,0, SEUIL_BAS,SEUIL_BAS,SEUIL_HAUT,SEUIL_HAUT, 0.0, "IR"};
	char x, y;

	FILE* pf = fopen(str, "r");
	if(!pf){
		printf("Le fichier n'a pu être lu.\n");
		return oxyDatas;
	}

	do{
		fscanf(pf, "%f,%f,%f,%f,%c,%c", &absorb.acr, &absorb.dcr, &absorb.acir, &absorb.dcir, &x, &y);

		if(!feof(pf)){
			mesure(&oxyDatas, absorb, &acRm, &acIRm);
		}
	}while(!feof(pf));


	return oxyDatas;
}
