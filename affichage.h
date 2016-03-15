#ifndef AFFICHAGE
#define AFFICHAGE

struct Oxy
{
	int spo2;
	int pouls;
};
typedef struct Oxy Oxy;

void affichage(Oxy oxyDatas);

#endif