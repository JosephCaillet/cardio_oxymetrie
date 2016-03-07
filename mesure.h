#ifndef MESURE
#define MESURE

#define SEUIL_HAUT 500
#define SEUIL_BAS -500

void mesure(int* bpm, float* rsIR, int acR, int acIR, int dcR, int dcIR);
float calculSPo2(float acRmax, float acrmin, float acIRmax, float acIRmin, int dcR, int dcIR);
float convertRatioToSPO2(float ratio);

#endif