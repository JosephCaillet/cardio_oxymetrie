#include "lecture.h"

int lecture(void* source, int typeSource, Absorp* absorb)
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

int lectureFichier(FILE* src,  Absorp* absorb)
{
	if(4 != fscanf
}

int lectureUSB(FILE* src,  Absorp* absorb)
{

}