#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "lecture.h"
#include "affichage.h"
#include "dataBuffer.h"

#define FIC_TEST_NAME "test_fic_input"

void testLecture();

int main(int argc, char* argv[])
{
	puts("Running test for Lecture :");

	return 0;
}

void testLecture()
{
	puts(" -- Running test for Lecture : --");

	puts("Test 1 : ");
	
	char* input = "1230,0800,1400,0700\n\r";
	char* output = "-818 800 648 700\n\r";

	FILE* fic = fopen(FIC_TEST_NAME, "w");
	fputs(input, fic);
	rewind(fic);

	int eof = 36;
	absorb a = lecture()

	fclose(fic);
	remove(FIC_TEST_NAME);
}