#ifndef MESURE
#define MESURE

#include "dataBuffer.h"

#define SEUIL_HAUT 500
#define SEUIL_BAS -500

struct AcMesures
{
	int seuilHautPasse;
	int seuilBasPasse;

	int nbPoints;

	int min;
	int max;

	float bpm;
};
typedef struct AcMesures AcMesures;

void mesure(Oxy* oxy, Absorp absorp);

void majMaxMinDepasseSeuil(AcMesures* ac, int acNew);
int majBpm(AcMesures* ac);

float calculSPo2(float acRmax, float acrmin, float acIRmax, float acIRmin, int dcR, int dcIR);
float convertRatioToSPO2(float ratio);

#endif