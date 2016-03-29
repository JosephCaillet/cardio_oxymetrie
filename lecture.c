#include "lecture.h"

int lecture(void* source, int typeSource, absorp* absorb)
{
	if(typeSource == 1)
	{
		return lectureFichier( (FILE*)source, absorb);
	}
	else
	{
		return lectureUSB( (FILE*)source, absorb);
	}
}

int lectureFichier(FILE* src,  absorp* absorb)
{
	int status = fscanf(src, "%f,%f,%f,%f", &absorb->acr, &absorb->dcr, &absorb->acir, &absorb->dcir);
	
	if(status == 4)
	{
		absorb->acr = absorb->acr - 2048;
		absorb->acir = absorb->acir - 2048;
		//printf("%f,%f,%f,%f\n", absorb->acr, absorb->dcr, absorb->acir, absorb->dcir);
		return 0;
	}
	return 2;
}

int lectureUSB(FILE* src,  absorp* absorb)
{
	return 0;
}