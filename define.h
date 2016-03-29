#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

void integrationTest(char* str);

#endif
