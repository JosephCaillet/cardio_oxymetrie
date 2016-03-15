#ifndef LECTURE
#define LECTURE

#include "dataBuffer.h"
#include <stdio.h>

int lecture(void* source, int typeSource, Absorb* absorb);

int lectureFichier(FILE*,  Absorb* absorb);
int lectureUSB(FILE*,  Absorb* absorb);
#endif