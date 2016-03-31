#ifndef LECTURE_USB
#define LECTURE_USB

#include <windows.h>
#include "dataBuffer.h"
#include "ftd2xx.h"

#define LONG_ELM_TRAME 4

int readSequenceUsb(FT_HANDLE* ft, float* nb);
int isSeparatorValidUsb(FT_HANDLE* ft, int mode);
char readCharsUsb(FT_HANDLE* ft);

int waitForValidTrameUsb(FT_HANDLE* ft);
absorp lectureUsb(FT_HANDLE* ft);

#endif