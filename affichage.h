#ifndef AFFICHAGE
#define AFFICHAGE

struct Oxy
{
	int spo2;
	int pouls;
};
typedef struct Oxy Oxy;

void affichage(int bpm, float rsIR);

#endif