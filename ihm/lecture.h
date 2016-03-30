//
// Created by joseph on 17/03/16.
//

#ifndef IHM_LECTURE_H
#define IHM_LECTURE_H

#define DATA_FILE_1 "../Data.txt"
#define DATA_FILE_2 "../Data2.txt"
#define VERROU_FILE_1 "../.verrouData"
#define VERROU_FILE_2 "../verrouData2"

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
