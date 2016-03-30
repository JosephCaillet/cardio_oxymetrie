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
void testIir();

int main()//int argc, char* argv[])
{
	//testLecture();
	//testIir();

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
	fclose(fic);
	fic = fopen(FIC_TEST_NAME, "r");

	int eof = 36;
	absorp a = {42, 42, 42, 42};
	a = lecture(fic, &eof);
	printf("Output given : %f %f %f %f\n", a.acr, a.dcr, a.acir, a.dcir);
	printf("Output expct : %s", output);

	fclose(fic);
	remove(FIC_TEST_NAME);
}

void testIir()
{
	puts(" -- Running test for iir : --");

	char* input = "rec/record1_fir.dat";
	char* output = "-716, 1830, -688, 1830\n";

	absorp a = {42, 42, 42, 42};
	a = iirTest(input);

	printf("Output given : %f %f %f %f\n", a.acr, a.dcr, a.acir, a.dcir);
	printf("Output expct : %s", output);
}