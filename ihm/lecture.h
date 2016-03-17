//
// Created by joseph on 17/03/16.
//

#ifndef IHM_LECTURE_H
#define IHM_LECTURE_H

struct Mesures
{
	int spo2;
	int bpm;
	int acr;
	int acir;
};
typedef struct Mesures Mesures;

void getMesures(Mesures* mesures);

#endif //IHM_LECTURE_H