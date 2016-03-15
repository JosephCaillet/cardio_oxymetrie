#ifndef LECTURE
#define LECTURE

#include "dataBuffer.h"
#include <stdio.h>

int lecture(void* source, int typeSource, Absorp* absorb);

int lectureFichier(FILE*,  Absorp* absorb);
int lectureUSB(FILE*,  Absorp* absorb);
#endif