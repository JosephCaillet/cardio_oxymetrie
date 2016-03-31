#include <ctype.h>
#include "lectureUSB.h"

#define RETURN_IF_USB_READING_ERROR()	if(res == -1) \
										{ \
											waitForValidTrameUsb(ft); \
											return lectureUsb(ft); \
										}

////////////////////////////
//     Lecture USB     /////
////////////////////////////

int readSequenceUsb(FT_HANDLE* ft, float* nb)
{
	char tab[LONG_ELM_TRAME];
	int i;
	char res;
	
	for(i = 0; i < LONG_ELM_TRAME; i++)
	{
		res = readCharsUsb(ft);
		if(res == -1 || !isdigit(res))
		{
			return -1;
		}
		tab[i] = res - 48;
	}

	*nb = (tab[0] ) * 1000 + (tab[1] ) * 100 + (tab[2] ) * 10 + (tab[3] );
	
	return 0;
}

int isSeparatorValidUsb(FT_HANDLE* ft, int mode)
{
	char c1;
	char c2;
	if(mode == 0)
	{
		c1 = readCharsUsb(ft);
		if(c1 == -1 || c1 != ',')
		{
			return -1;
		}

		return 0;
	}
	else if(mode == 1)
	{
		c1 = readCharsUsb(ft);
		c2 = readCharsUsb(ft);
		if(c1 == -1 || c2 == -1 || c1 != '\n' || c2 != '\r')
		{
			return -1;
		}

		return 0;
	}

	return -1;
}

char readCharsUsb(FT_HANDLE* ft)
{
	FT_STATUS ftStatus;
	DWORD n;
	char buffer = -1;
	
	ftStatus = FT_Read(ft, &buffer, 1, &n);

	if (ftStatus != FT_OK)
	{
		buffer = -1;
	}

	return buffer;
}

int waitForValidTrameUsb(FT_HANDLE* ft)
{
	char c1, c2;
	int continuer = 1;

	while(continuer)
	{
		c1 = c2;
		c2 = readCharsUsb(ft);
		if(c1 == '\n' && c2 == '\r')
		{
			continuer = 0;
		}
	}

	return 0;
}

absorp lectureUsb(FT_HANDLE* ft)
{
	absorp absorb;
	int res;

	//acr
	res = readSequenceUsb(ft, &absorb.acr);
	RETURN_IF_USB_READING_ERROR()
	//,
	res = isSeparatorValidUsb(ft, 0);
	RETURN_IF_USB_READING_ERROR()

	//dcr
	res = readSequenceUsb(ft, &absorb.dcr);
	RETURN_IF_USB_READING_ERROR()
	//,
	res = isSeparatorValidUsb(ft, 0);
	RETURN_IF_USB_READING_ERROR()

	//acir
	res = readSequenceUsb(ft, &absorb.acir);
	RETURN_IF_USB_READING_ERROR()
	//,
	res = isSeparatorValidUsb(ft, 0);
	RETURN_IF_USB_READING_ERROR()

	//dcir
	res = readSequenceUsb(ft, &absorb.dcir);
	RETURN_IF_USB_READING_ERROR()
	//LF CR
	res = isSeparatorValidUsb(ft, 1);
	RETURN_IF_USB_READING_ERROR()

	absorb.acr -= 2048;
	absorb.acir -= 2048;
	return absorb;
}