#ifndef MESURE
#define MESURE

#include <time.h>

#define SEUIL_HAUT 500
#define SEUIL_BAS -500

struct AcMesures
{
	int passagePar0;
	int seuilHautPasse;
	int seuilBasPasse;

	int lastValue;

	clock_t periodeDeb;
	clock_t periodeFin;	

	int min;
	int max;

	float bpm;
};
typedef struct AcMesures AcMesures;

void mesure(int* bpm, float* rsIR, int acR, int acIR, int dcR, int dcIR);

void majMaxMinDepasseSeuil(AcMesures* ac, int acNew);
void majPassageZero(AcMesures* ac, int acNew);
int majBpm(AcMesures* ac);

float calculSPo2(float acRmax, float acrmin, float acIRmax, float acIRmin, int dcR, int dcIR);
float convertRatioToSPO2(float ratio);

#endif