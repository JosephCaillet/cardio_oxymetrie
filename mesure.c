#include "mesure.h"
#include <time.h>

void mesure(int* bpm, float* rsIR, int acR, int acIR, int dcR, int dcIR)
{
	static int passagePar0 = 0;

	static clock_t periodeDeb = 0;
	static clock_t periodeFin = 0;

	static int acRmin = SEUIL_BAS;
	static int acRmax = SEUIL_HAUT;
	static int acIRmin = SEUIL_BAS;
	static int acIRmax = SEUIL_HAUT;

	//Obtention min et max pour acR
	if(acR > acRmax)
	{
		acRmax = acR;
	}
	else if(acR < acRmin)
	{
		acRmin = acR;
	}

	//Obtention min et max pour acIR
	if(acIR > acIRmax)
	{
		acIRmax = acIR;
	}
	else if(acIR < acIRmin)
	{
		acIRmin = acIR;
	}

	//Taux SPo2
	*rsIR = calculSPo2(acRmax, acRmin, acIRmax, acIRmin, dcR, dcIR);

	//Calcul rythme cardiaque
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