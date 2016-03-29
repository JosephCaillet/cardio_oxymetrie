#ifndef LECTURE
#define LECTURE

#include "dataBuffer.h"
#include <stdio.h>

int lecture(void* source, int typeSource, absorp* absorb);

int lectureFichier(FILE* source,  absorp* absorb);
int lectureUSB(FILE* source,  absorp* absorb);
#endif