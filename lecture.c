#include "lecture.h"

#define RETURN_IF_EOF_OR_READING_ERROR()    res = checkErrors(res, etat); \
											if(res == -1) \
											{ \
												return absorp; \
											} \
											else if(res == 1) \
											{ \
												return lecture(pf, etat); \
											} \

int readSequence(FILE* pf, int* nb)
{
	char tab[LONG_ELM_TRAME];
	int i;

	for(i = 0; i < LONG_ELM_TRAME)
	{
		char res = fgetc(pf);
		if(res == EOF)
		{
			return -1;
		}
		else if(!isdigit(res))
		{
			return 1;
		}
		tab[i] = res - 48;
	}

	*nb = (tab[3] - 48) * 1000 + (tab[2] - 48) * 100 + (tab[1] - 48) * 10 + (tab[0] - 48);
	return 0;
}

int isSeparatorValid(FILE* pf, int mode)
{
	if(mode == 0)
	{
		char c = fgetc(pf);
		if(c == EOF)
		{
			return -1;
		}
		else if(c1 != ',')
		{
			return 1;
		}
		return 0;
	}
	else if(mode == 1)
	{
		char c1 = fgetc(pf);
		char c2 = fgetc(pf);
		if(c1 == EOF || c2 == EOF)
		{
			return -1;
		}
		else if(c1 != '\n' || c2 != '\r')
		{
			return 1;
		}
		return 0;
	}

	return -1;
}

int checkErrors(int res, int* eof, FILE* pf)
{
	if(res == -1)
	{
		*eof == EOF;
		return -1;
	}
	else if(res == 1)
	{
		if(waitForValidTrame(pf) == -1)
		{
			*etat = EOF;
			return -1;
		}
		return 1;
	}
	else
	{
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

absorp lecture(File* pf, int* etat)
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
	res = isSeparatorValid(c1, NULL, 0);
	RETURN_IF_EOF_OR_READING_ERROR()

	//dcir
	res = readSequence(pf, &absorb.dcir);
	RETURN_IF_EOF_OR_READING_ERROR()
	//LF CR
	res = isSeparatorValid(pf, 1);
	RETURN_IF_EOF_OR_READING_ERROR()

	return absorb;
}

int lectureUSB(FILE* src,  absorp* absorb)
{
	return 0;
}