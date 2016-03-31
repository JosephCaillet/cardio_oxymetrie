/*==============================================================================================================*/
/*	Nom : 		affichage.c																						*/
/*	Auteur : 	Thomas COUSSOT																					*/
/*	Update :	Joseph CAILLET																					*/
/*	Desc : 		La fonction a pour but d'écrire dans un fichier les valeurs de spO2 et de BPM dans Data.txt		*/
/*				tout en mettant en place un verrou. affichage2 est la pour l'interface graphique supplémentaire.*/
/*==============================================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "affichage.h"

/*------------------------------------------------------------------------------*/
/*	Fonction : 	affichage														*/
/*	Params :	oxy oxyDatas													*/
/*	Retour :	/																*/
/*	Desc :		La fonction écrit le spO2 et le BPM dans Data.txt avec			*/
/*				un système de verrou pour éviter l'utilisation simultanée du	*/
/*				fichier.														*/
/*------------------------------------------------------------------------------*/
void affichage(oxy oxyDatas){
	printInFile("Data.txt", ".verrouData", oxyDatas.spo2, oxyDatas.pouls);
	return;
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	affichage2														*/
/*	Params :	float acr, float acir											*/
/*	Retour :	/																*/
/*	Desc :		La fonction écrit la valeur d'acr et d'acir dans 				*/
/*				Data2.txt avec un système de verrou pour éviter l'utilisation 	*/
/*				simultanée du fichier.											*/
/*------------------------------------------------------------------------------*/
void affichage2(float acr, float acir)
{
	printInFile("Data2.txt", ".verrouData2", (int)acr, (int)acir);
	return;
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	printInFile														*/
/*	Params :	char* fileName, char* verrouName, int valeur1, int valeur2		*/
/*	Retour :	/																*/
/*	Desc :		La fonction applique écrit les deux valeurs d'entrées dans le	*/
/*				fichier spécifié en créant un verrou pendant l'opération afin 	*/
/*				d'éviter l'utilisation simultanée du fichier.					*/
/*------------------------------------------------------------------------------*/
void printInFile(char* dataFileName, char* verrouFileName, int value1, int value2)
{
	FILE *verrou = NULL;
	FILE *data = NULL;

	//-- Si le verrou spécifié n'existe pas, on peut faire un traitement --//
	if(access(verrouFileName, F_OK) == -1){
		//-- On créé le verrou --//
		verrou = fopen(verrouFileName, "w");

		//-- On ouvre le fichier dans lequel on veut écrire en supprimant tout ce qu'il y a déjà à l'intérieur --//
		data = fopen(dataFileName, "w+");
		//-- Si le fichier existe on peut faire le traitement --//
		if(data != NULL){
			fprintf(data, "%d\n%d", value1, value2);

			fclose(data);
		}

		//-- on ferme et on supprime le verrou --//
		fclose(verrou);
		remove(verrouFileName);
	}

	return;
}
