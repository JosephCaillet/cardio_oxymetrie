#include "mesure.h"

void mesure(int* bpm, float* rsIR, Absorp absorp)
{
	int periodeAquise = 0;
	static AcMesures acRm = {0,0,0, 0, 0,0, SEUIL_BAS,SEUIL_HAUT, 0.0};
	static AcMesures acIRm = {0,0,0, 0, 0,0, SEUIL_BAS,SEUIL_HAUT, 0.0};

	//majMaxMinSeuil
	majMaxMinDepasseSeuil(&acRm, absorp.acR);
	majMaxMinDepasseSeuil(&acIRm, absorp.acIR);

	//upd passage par 0
	majPassageZero(&acRm, absorp.acR);
	majPassageZero(&acIRm, absorp.acIR);

	//updBpm
	periodeAquise += majBpm(&acRm);
	periodeAquise += majBpm(&acIRm);

	//updSPo2	
	if(periodeAquise > 0)
	{
		*rsIR = calculSPo2(acRm.max, acRm.min, acIRm.max, acIRm.min, absorp.dcR, absorp.dcIR);
		*bpm = (acRm.bpm + acIRm.bpm) / 2.0;
	}
}

void majMaxMinDepasseSeuil(AcMesures* ac, int acNew)
{
	if(acNew > ac->max)
	{
		ac->max = acNew;
		ac->seuilHautPasse = 1;
	}
	else if(acNew < ac->min)
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
	}
	ac->lastValue = acNew;
}

int majBpm(AcMesures* ac)
{
	if(ac->seuilBasPasse == 1 && ac->seuilHautPasse == 1 && ac->passagePar0 > 2)
	{
		ac->seuilHautPasse = 0;
		ac->seuilBasPasse = 0;
		ac->passagePar0 = 1;
		ac->min = SEUIL_BAS;
		ac->max = SEUIL_HAUT;

		ac->periodeFin = clock();
		ac->bpm = (ac->periodeFin - ac->periodeDeb) / CLOCKS_PER_SEC;
		ac->bpm = 1.0 / ac->bpm;
		ac->periodeDeb = ac->periodeFin;

		return 1;
	}

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
	return -31.25 * ratio + 112.5;
}