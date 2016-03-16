#include "mesure.h"
#include <stdio.h>

void mesure(Oxy* oxy, Absorp absorp)
{
	int periodeAquise = 0;
	static AcMesures acRm = {0,0,0, 0,0, SEUIL_BAS,SEUIL_HAUT, 0.0, "R"};
	static AcMesures acIRm = {0,0,0, 0,0, SEUIL_BAS,SEUIL_HAUT, 0.0, "IR"};

	//majMaxMinSeuil
	majMaxMinDepasseSeuil(&acRm, absorp.acr);
	majMaxMinDepasseSeuil(&acIRm, absorp.acir);

	//upd passage par 0
	majPassageZero(&acRm, absorp.acr);
	majPassageZero(&acIRm, absorp.acir);

	//updBpm
	periodeAquise += majBpm(&acRm);
	periodeAquise += majBpm(&acIRm);

	//updSPo2	
	if(periodeAquise > 0)
	{
		oxy->spo2 = calculSPo2(acRm.max, acRm.min, acIRm.max, acIRm.min, absorp.dcr, absorp.dcir);
		oxy->pouls = (acRm.bpm + acIRm.bpm) / 2.0f;
		printf("Rbmp: %f - IRbmp: %f\n", acRm.bpm, acIRm.bpm);
	}
}
//85spo2
//70bpm

void majMaxMinDepasseSeuil(AcMesures* ac, int acNew)
{
	if(acNew > ac->max)
	{
		ac->max = acNew;
		ac->seuilHautPasse = 1;
	}
	else if(acNew < ac->min && ac->seuilHautPasse == 1)//On veux faire les vérif sur un seuil bas précédé d'un seuil haut.
	{
		ac->min = acNew;
		ac->seuilBasPasse = 1;
	}
}

void majPassageZero(AcMesures* ac, int acNew)
{
	if(ac->lastValue * acNew <= 0)
	{
		ac->passagePar0++;
		printf("Passage par zéro n° %d pour %s\n", ac->passagePar0, ac->s);
	}
	ac->lastValue = acNew;
}

int majBpm(AcMesures* ac)
{
	if(ac->seuilBasPasse == 1 && ac->passagePar0 > 2)//Si on est passé par le seuil bas, implique passage seuil haut.
	{
		ac->seuilHautPasse = 0;
		ac->seuilBasPasse = 0;
		ac->passagePar0 = 1;

		ac->min = SEUIL_BAS;
		ac->max = SEUIL_HAUT;

		ac->bpm = (float)30000 / (float)ac->nbPoints;
		ac->nbPoints = 1;
		printf("Une période à été aquise sur : %s\n", ac->s);
		return 1;
	}

	ac->nbPoints++;

	return 0;
}

float calculSPo2(float acRmax, float acRmin, float acIRmax, float acIRmin, int dcR, int dcIR)
{
	float ptpACr = (float)acRmax - (float)acRmin;
	float rapport1 = ptpACr / (float)dcR;

	float ptpACir = (float)acIRmax - (float)acIRmin;
	float rapport2 = ptpACir / (float)dcIR;
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