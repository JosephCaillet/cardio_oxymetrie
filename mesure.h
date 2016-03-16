#ifndef MESURE
#define MESURE

#include "dataBuffer.h"

#define SEUIL_HAUT 500
#define SEUIL_BAS -500

struct AcMesures
{
	int passagePar0;
	int seuilHautPasse;
	int seuilBasPasse;

	int lastValue;
	int nbPoints;

	int min;
	int max;

	float bpm;

	char* s;
};
typedef struct AcMesures AcMesures;

void mesure(Oxy* oxy, Absorp absorp, AcMesures* acRm, AcMesures* acIRm);

void majMaxMinDepasseSeuil(AcMesures* ac, int acNew);
void majPassageZero(AcMesures* ac, int acNew);
int majBpm(AcMesures* ac);

float calculSPo2(float acRmax, float acrmin, float acIRmax, float acIRmin, int dcR, int dcIR);
float convertRatioToSPO2(float ratio);

#endif