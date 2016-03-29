#ifndef DEFINE_H
#define DEFINE_H

struct oxy
{
	int spo2;
	int pouls;
};
typedef struct oxy oxy;

struct absorp
{
	float acr;
	float acir;
	float dcr;
	float dcir;
};
typedef struct absorp absorp;

#endif