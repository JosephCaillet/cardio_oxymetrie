/*==============================================================================================================*/
/*	Nom : 		lecture.c																						*/
/*	Auteur : 	Joseph CAILLET																					*/
/*	Desc : 		Lit des donnes depuis un fichier pour simuler la carte.											*/
/*==============================================================================================================*/

#include <ctype.h>

#include "lecture.h"

//Macro servant a :
//- quitter la fonction de lecture si une fin de fichier est rencontré
//- relancer une nouvelle aquisition si une trame est incorecte.
#define RETURN_IF_EOF_OR_READING_ERROR()    res = checkErrors(res, etat, pf); \
											if(res == -1) \
											{ \
												return absorb; \//fin de fichier, arret.
											} \
											else if(res == 1) \
											{ \
												return lecture(pf, etat); \//erreur de lecture, passe à la trame suivante.
											}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	readSequence													*/
/*	Params :	FILE* pf, float* nb												*/
/*	Retour :	-1 si EOF, 1 si erreur, char caractere sinon.					*/
/*	Desc :		La fonction lit une sequence de 4 char ds pf					*/
/*------------------------------------------------------------------------------*/
int readSequence(FILE* pf, float* nb)
{
	char tab[LONG_ELM_TRAME];
	int i;
	char res;

	for(i = 0; i < LONG_ELM_TRAME; i++)
	{
		res = fgetc(pf);//lecture des 4 char
		if(res == EOF)
		{
			return -1;//si fin fichier
		}
		else if(!isdigit(res))
		{
			return 1;//si erreur de lecture
		}
		tab[i] = res - 48;//transformaton du char ascii en nb
	}
	
	*nb = (tab[0] ) * 1000 + (tab[1] ) * 100 + (tab[2] ) * 10 + (tab[3] );//calcul du nombre
	return 0;
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	isSeparatorValid												*/
/*	Params :	FILE* pf, float* nb												*/
/*	Retour :	-1 si EOF, 1 si erreur, char caractere sinon.					*/
/*	Desc :		La fonction lit un char dan pf et vérifie suivant le mode si 	*/
/* 				le separateur est bien valide      								*/
/*------------------------------------------------------------------------------*/
int isSeparatorValid(FILE* pf, int mode)
{
	char c1;
	char c2;
	if(mode == 0)//si separateur de nombre en cour de trame
	{
		c1 = fgetc(pf);
		if(c1 == EOF)
		{
			return -1;//si fin fichier
		}
		else if(c1 != ',')
		{
			return 1;//si separarteur n'est pas une virgule
		}

		return 0;//separateur ok
	}
	else if(mode == 1)
	{
		c1 = fgetc(pf);
		c2 = fgetc(pf);
		if(c1 == EOF || c2 == EOF)
		{
			return -1;//si fin de fichier
		}
		else if(c1 != '\n' || c2 != '\r')
		{
			return 1;//si séparateur n'est pas LFCR
		}

		return 0;//separateur ok
	}

	return -1;//erreur mode incorect
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	checkErrors														*/
/*	Params :	int res, int* eof, FILE* pf										*/
/*	Retour :	-1 si EOF, 1 si erreur, 0 sinon.								*/
/*	Desc :		La fonction verifie si il y a de erreurs: rerourne -1 si eof,   */
/* 				 1 si erreur de lecture et trame de pf stabilise, 0 sinon.		*/
/*------------------------------------------------------------------------------*/
int checkErrors(int res, int* eof, FILE* pf)
{
	if(res == -1)
	{
		*eof = EOF;
		return -1;//fin de fichier
	}
	else if(res == 1)
	{
		if(waitForValidTrame(pf) == -1)//on passe a latrame suivante
		{
			*eof = EOF;
			return -1;//fin de fichier
		}
		return 1;//la trame comportait une erreur, et le fichier à été remis ds un état valide.
	}
	else
	{
		return 0;//pas d'erreur
	}
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	waitForValidTrame												*/
/*	Params :	FILE* pf														*/
/*	Retour :	-1 si EOF, 1 si erreur, 0 sinon.								*/
/*	Desc :		La fonction stabilise la trame a un etat connu : rerourne -1 	*/
/* 				si eof, 1 si erreur de lecture et trame stabilise, 0 sinon.		*/
/*------------------------------------------------------------------------------*/
int waitForValidTrame(FILE* pf)
{
	char c1, c2;
	int continuer = 1;

	while(continuer)//on lit des caracter tant que l'on est pas revenu a un etat stable, connu, celui de fin de trame.
	{
		c1 = c2;
		c2 = fgetc(pf);
		if(c1 == '\n' && c2 == '\r')//si fin de trame
		{
			continuer = 0;//on est revenu a un etat connu
		}
		else if(c1 == EOF || c2 == EOF)
		{
			return -1;// si fin de fichier
		}
	}

	return 0;
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	lecture															*/
/*	Params :	FILE* pf, int* etat												*/
/*	Retour :	absor.															*/
/*	Desc :		La fonction lit dan le fichier pf, et retourne une struc absorb */
/*				avec les valeurs lues. etat est mis a EOF si fin du fichier		*/
/*				rencontrée														*/
/*------------------------------------------------------------------------------*/
absorp lecture(FILE* pf, int* etat)
{
	absorp absorb;
	int res;

	//memorisaton de acr
	res = readSequence(pf, &absorb.acr);
	RETURN_IF_EOF_OR_READING_ERROR()
	//verification separateur ,
	res = isSeparatorValid(pf, 0);
	RETURN_IF_EOF_OR_READING_ERROR()

	//memorisaton de dcr
	res = readSequence(pf, &absorb.dcr);
	RETURN_IF_EOF_OR_READING_ERROR()
	//verification separateur ,
	res = isSeparatorValid(pf, 0);
	RETURN_IF_EOF_OR_READING_ERROR()

	//memorisaton de acir
	res = readSequence(pf, &absorb.acir);
	RETURN_IF_EOF_OR_READING_ERROR()
	//verification separateur ,
	res = isSeparatorValid(pf, 0);
	RETURN_IF_EOF_OR_READING_ERROR()

	//memorisaton de dcir
	res = readSequence(pf, &absorb.dcir);
	RETURN_IF_EOF_OR_READING_ERROR()
	//verification separateur LF CR
	res = isSeparatorValid(pf, 1);
	RETURN_IF_EOF_OR_READING_ERROR()

	//supression de l'offset, retablissement de l'origine a zero
	absorb.acr -= 2048;
	absorb.acir -= 2048;
	
	return absorb;
}