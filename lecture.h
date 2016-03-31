#ifndef LECTURE
#define LECTURE

#include <stdio.h>
#include "dataBuffer.h"

//Longueur
#define LONG_ELM_TRAME 4

int readSequence(FILE* pf, float* nb);
int isSeparatorValid(FILE* pf, int mode);
int checkErrors(int res, int* eof, FILE* pf);

int waitForValidTrame(FILE* pf);
absorp lecture(FILE* pf, int* etat);

#endif