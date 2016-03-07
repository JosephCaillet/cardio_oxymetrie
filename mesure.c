#include "mesure.h"
#include <time.h>

void mesure(int* bpm, float* rsIR, int acR, int acIR, int dcR, int dcIR)
{
	int calculPossible = 0;

	static int acRpassagePar0 = 0;
	static int acRseuilHautPasse = 0;
	static int acRseuilBasPasse = 0;

	static int acRlastValue = 0;

	static clock_t acRperiodeDeb = 0;
	static clock_t acRperiodeFin = 0;	

	static int acRmin = SEUIL_BAS;
	static int acRmax = SEUIL_HAUT;

	static float acRbpm;

	static int acIRpassagePar0 = 0;
	static int acIRseuilHautPasse = 0;
	static int acIRseuilBasPasse = 0;

	static int acIRlastValue = 0;

	static clock_t acIRperiodeDeb = 0;
	static clock_t acIRperiodeFin = 0;

	static int acIRmin = SEUIL_BAS;
	static int acIRmax = SEUIL_HAUT;
	static float acIRbpm


	if(acR > acRmax)
	{
		acRmax = acR;
		acRseuilHautPasse = 1;
	}
	else if(acR < acRmin)
	{
		acRmin = acR;
		acRseuilBasPasse = 1;
	}

	if(acIR > acIRmax)
	{
		acIRmax = acIR;
		acIRseuilHautPasse = 1;
	}
	else if(acIR < acIRmin)
	{
		acIRmin = acIR;
		acRseuilBasPasse = 1;
	}


	if(acRlastValue * acR <= 0)
	{
		acRpassagePar0++;
	}
	acRlastValue = acR;

	if(acIRlastValue * acIR <= 0)
	{
		acRpassagePar0++;
	}
	acIRlastValue = acIR;


	if(acRseuilBasPasse == 1 && acRseuilHautPasse == 1 && acRpassagePar0 > 2)
	{
		calculPossible = 1;

		acRseuilHautPasse = 0;
		acRseuilBasPasse = 0;
		acRpassagePar0 = 1;

		acRperiodeFin = clock();
		acRbpm = (acRperiodeFin - acRperiodeDeb) / CLOCKS_PER_SEC;
		acRperiodeDeb = acRperiodeFin;
		acRbpm = 1.0 / acRbpm;
	}

	if(acIRseuilBasPasse == 1 && acIRseuilHautPasse == 1 && acIRpassagePar0 > 2)
	{
		calculPossible = 1;

		acIRseuilHautPasse = 0;
		acIRseuilBasPasse = 0;
		acIRpassagePar0 = 1;

		acIRperiodeFin = clock();
		acIRbpm = (acIRperiodeFin - acIRperiodeDeb) / CLOCKS_PER_SEC;
		acIRperiodeDeb = acIRperiodeFin;
		acIRbpm = 1.0 / acIRbpm;
	}
	
	if(calculPossible == 1)
	{
		calculPossible = 0;
		*rsIR = calculSPo2(acRmax, acRmin, acIRmax, acIRmin, dcR, dcIR);
		*bpm = (acRbpm + acIRbpm)/2.0
	}
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