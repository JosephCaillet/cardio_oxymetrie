#ifndef MESURE
#define MESURE

#include "dataBuffer.h"

#define SEUIL_HAUT 100
#define SEUIL_BAS -100

struct AcMesures
{
	int passagePar0;
	int seuilHautPasse;
	int seuilBasPasse;

	int lastValue;
	int nbPoints;

	float min;
	float minValid;
	float max;
	float maxValid;

	float bpm;

	char* s;
};
typedef struct AcMesures AcMesures;

void mesure(oxy* oxy, absorp absorp, AcMesures* acRm, AcMesures* acIRm);

void majMaxMinDepasseSeuil(AcMesures* ac, int acNew);
void majPassageZero(AcMesures* ac, int acNew);
int majBpm(AcMesures* ac, float ech_ac);

float calculSPo2(float acRmax, float acrmin, float acIRmax, float acIRmin, float dcR, float dcIR);
float convertRatioToSPO2(float ratio);

void affAcMesure(AcMesures ac);

oxy mesureTest(char*);

#endif
