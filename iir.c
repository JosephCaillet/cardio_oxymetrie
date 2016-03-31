/*==============================================================================================================*/
/*	Nom : 		iir.C																							*/
/*	Auteur : 	Thomas COUSSOT																					*/
/*	Desc : 		La fonction a pour but de simuler un filtre à réponse infinie (IIR). On utilise donc la formule */
/*				y(n) = x[n] - x[n-1] + ALPHA * y[n-1]  . ALPHA est une constante appliquée au filtre. Nous		*/
/*				choisie la valeur 0.992 pour cette constante.													*/
/*==============================================================================================================*/

#include "iir.h"

/*------------------------------------------------------------------------------*/
/*	Fonction : 	iir																*/
/*	Params :	float x[n], float x[n-1], float y[n-1]							*/
/*	Retour :	float y(n) (valeur filtrée)										*/
/*	Desc :		La fonction applique le filtre iir								*/
/*------------------------------------------------------------------------------*/
float iir(float ac, float acPrec, float acPHPrec){
	return ac - acPrec + ALPHA * acPHPrec;
}


/*------------------------------------------------------------------------------*/
/*	Fonction : 	iirTest															*/
/*	Params :	char* nomFic													*/
/*	Retour :	absorp acR et acIR filtrées										*/
/*	Desc :		La fonction permet de tester la fonction iir de manière unitaire*/
/*------------------------------------------------------------------------------*/
absorp iirTest(char* str){
	absorp absorb;
	float acRPH, acRPHPrec, acRPB, acRPBPrec, acIRPH, acIRPHPrec, acIRPB, acIRPBPrec;
	char x, y;

//	FILE* ficOTest = fopen("testIirOutput", "w+"); //Fichier permettant l'obtention de résultats intermédiaires

	//-- Ouverture du fichier envoyé en paramètre --//
	FILE* pf = fopen(str, "r");
	if(!pf){
		printf("Le fichier n'a pu être lu.\n");
		return absorb;
	}

	//-- Initialisation des variables utilisées (et nécessitant une initialisation) --//
	acRPB = 0;
	acIRPB = 0;
	acRPH = 0;
	acIRPH = 0;

	//-- Boucle faire ... tant qu'on a pas atteint la fin du fichier --//
	do{
		//-- On réactualise les anciennes valeur avant que les nouvelles ne soient à leur tour actualisé par la nouvelle lecture de ligne --//
		acRPHPrec = acRPH;
		acIRPHPrec = acIRPH;
		acRPBPrec = acRPB;
		acIRPBPrec = acIRPB;

		fscanf(pf, "%f,%f,%f,%f,%c,%c", &acRPB, &absorb.dcr, &acIRPB, &absorb.dcir, &x, &y); //On lit la ligne du fichier pf afin d'en extraire les valeurs

		//-- On test si on a pas atteint la fin du fichier. Comme on viens tout juste de lire une nouvelle ligne du fichier, la condition de la boucle ne s'applique pas encore --//
		if(!feof(pf)){
			//-- On fait passer les composantes rouge et infrarouge tour à tour dans le filtre iir --//
			acRPH = iir(acRPB, acRPBPrec, acRPHPrec);
			acIRPH = iir(acIRPB, acIRPBPrec, acIRPHPrec);

			//-- On met à jour les données de sortie --//
			absorb.acr = acRPH;
			absorb.acir = acIRPH;
//			fprintf(ficOTest, "%f,%f,%f,%f\n\r", absorb.acr, absorb.dcr, absorb.acir, absorb.dcir);
		}
	}while(!feof(pf));
	
	fclose(pf);

	return absorb;
}
