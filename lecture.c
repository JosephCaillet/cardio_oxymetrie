#include <ctype.h>

#include "lecture.h"

#define RETURN_IF_EOF_OR_READING_ERROR()    res = checkErrors(res, etat, pf); \
											if(res == -1) \
											{ \
												return absorb; \
											} \
											else if(res == 1) \
											{ \
												return lecture(pf, etat); \
											}

int readSequence(FILE* pf, float* nb)
{
	char tab[LONG_ELM_TRAME];
	int i;
	char res;
	static int j = 0;
	j++;
	for(i = 0; i < LONG_ELM_TRAME; i++)
	{
		res = fgetc(pf);
		if(res == EOF)
		{
			//puts("eof");
			printf("eof a exec nb : %d", j);
			return -1;
		}
		else if(!isdigit(res))
		{
			//puts("not digit");
			return 1;
		}
		tab[i] = res - 48;
	}

	//*nb = (tab[0] - 48) * 1000 + (tab[1] - 48) * 100 + (tab[2] - 48) * 10 + (tab[3] - 48);
	*nb = (tab[0] ) * 1000 + (tab[1] ) * 100 + (tab[2] ) * 10 + (tab[3] );
	printf("Read digits : %c%c%c%c\n", tab[0], tab[1], tab[2], tab[3]);
	printf("Read digits : %d%d%d%d\n", tab[0], tab[1], tab[2], tab[3]);
	printf("%f\n", *nb);
	return 0;
}

int isSeparatorValid(FILE* pf, int mode)
{
	char c1;
	char c2;
	if(mode == 0)
	{
		c1 = fgetc(pf);
		if(c1 == EOF)
		{
			//puts("ISV 1");
			return -1;
		}
		else if(c1 != ',')
		{
			//puts("ISV 2");
			return 1;
		}
		//puts("ISV 3");
		return 0;
	}
	else if(mode == 1)
	{
		c1 = fgetc(pf);
		c2 = fgetc(pf);
		if(c1 == EOF || c2 == EOF)
		{
			//puts("ISV 4");
			return -1;
		}
		else if(c1 != '\n' || c2 != '\r')
		{
			//puts("ISV 5");
			return 1;
		}
		//puts("ISV 6");
		return 0;
	}

	//puts("ISV 7");
	return -1;
}

int checkErrors(int res, int* eof, FILE* pf)
{
	if(res == -1)
	{
		//puts("EOF 1");
		*eof = EOF;
		return -1;
	}
	else if(res == 1)
	{
		if(waitForValidTrame(pf) == -1)
		{
			//puts("EOF 2");
			*eof = EOF;
			return -1;
		}
		//puts("ERR 1");
		return 1;
	}
	else
	{
		//puts("NO PB");
		return 0;
	}
}

int waitForValidTrame(FILE* pf)
{
	char c1, c2;
	int continuer = 1;

	while(continuer)
	{
		c1 = c2;
		c2 = fgetc(pf);
		if(c1 == '\n' && c2 == '\r')
		{
			continuer = 0;
		}
		else if(c1 == EOF || c2 == EOF)
		{
			return -1;
		}
	}

	return 0;
}

absorp lecture(FILE* pf, int* etat)
{
	absorp absorb;
	int res;

	//acr
	res = readSequence(pf, &absorb.acr);
	RETURN_IF_EOF_OR_READING_ERROR()
	//,
	res = isSeparatorValid(pf, 0);
	RETURN_IF_EOF_OR_READING_ERROR()

	//dcr
	res = readSequence(pf, &absorb.dcr);
	RETURN_IF_EOF_OR_READING_ERROR()
	//,
	res = isSeparatorValid(pf, 0);
	RETURN_IF_EOF_OR_READING_ERROR()

	//acir
	res = readSequence(pf, &absorb.acir);
	RETURN_IF_EOF_OR_READING_ERROR()
	//,
	res = isSeparatorValid(pf, 0);
	RETURN_IF_EOF_OR_READING_ERROR()

	//dcir
	res = readSequence(pf, &absorb.dcir);
	RETURN_IF_EOF_OR_READING_ERROR()
	//LF CR
	res = isSeparatorValid(pf, 1);
	RETURN_IF_EOF_OR_READING_ERROR()

	absorb.acr -= 2048;
	absorb.acir -= 2048;
	return absorb;
}

int lectureUSB(FILE* src,  absorp* absorb)
{
	return 0;
}