#ifndef IIR
#define IIR

#include <stdio.h>
#include "define.h"

#define ALPHA 0.992

float iir(float acFiltre, float acFiltrePrec, float acFiltrePHPrec);
absorp iirTest(char* str);

#endif
