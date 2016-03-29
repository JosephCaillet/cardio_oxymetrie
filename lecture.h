#ifndef LECTURE
#define LECTURE

#include <stdio.h>
#include "dataBuffer.h"

#define LONG_ELM_TRAME 4

int readSequence(FILE* pf, int* nb);
int isSeparatorValid(FILE* pf, int mode);
int checkErrors(int res, int* eof, FILE* pf);

void waitForValidTrame(FILE* pf);
absorp lecture(FILE* pf, int* etat);
//int lecture(void* source, int typeSource, absorp* absorb);

int lectureFichier(FILE* source,  absorp* absorb);
int lectureUSB(FILE* source,  absorp* absorb);
#endif