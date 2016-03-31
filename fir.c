/*==============================================================================================================*/
/*	Nom : 		fir.C																							*/
/*	Auteur : 	Thomas COUSSOT																					*/
/*	Desc : 		La fonction a pour but de simuler un filtre à réponse finie (fir). Ce filtre à pour but de		*/
/*				supprimer les composantes hautes fréquences et garder le signal se trouvant autour de 1hz. On	*/
/*				utilise la formule y[n] = Somme[de k = 0 à 50]( h[k] * x[n-k] ). h[k] sont les coeficients du	*/
/*				filtre. On a un ordre de 51 sur ce filtre (0 à 50)												*/
/*==============================================================================================================*/

#include "fir.h"

/*------------------------------------------------------------------------------*/
/*	Fonction : 	fir																*/
/*	Params :	DataBuffer* x[k]												*/
/*	Retour :	float* y[n](R),	float* y[n](IR)									*/
/*	Desc :		La fonction applique le filtre fir								*/
/*------------------------------------------------------------------------------*/
void fir(DataBuffer* dataBuffer, float* acRFiltre, float* acIRFiltre){
	//-- hk est le tableau recenssant les coeficients du filtre --//
	float hk[51] = {
	1.4774946e-019,
	1.6465231e-004,
	3.8503956e-004,
	7.0848037e-004,
	1.1840522e-003,
	1.8598621e-003,
	2.7802151e-003,
	3.9828263e-003,
	5.4962252e-003,
	7.3374938e-003,
	9.5104679e-003,
	1.2004510e-002,
	1.4793934e-002,
	1.7838135e-002,
	2.1082435e-002,
	2.4459630e-002,
	2.7892178e-002,
	3.1294938e-002,
	3.4578348e-002,
	3.7651889e-002,
	4.0427695e-002,
	4.2824111e-002,
	4.4769071e-002,
	4.6203098e-002,
	4.7081811e-002,
	4.7377805e-002,
	4.7081811e-002,
	4.6203098e-002,
	4.4769071e-002,
	4.2824111e-002,
	4.0427695e-002,
	3.7651889e-002,
	3.4578348e-002,
	3.1294938e-002,
	2.7892178e-002,
	2.4459630e-002,
	2.1082435e-002,
	1.7838135e-002,
	1.4793934e-002,
	1.2004510e-002,
	9.5104679e-003,
	7.3374938e-003,
	5.4962252e-003,
	3.9828263e-003,
	2.7802151e-003,
	1.8598621e-003,
	1.1840522e-003,
	7.0848037e-004,
	3.8503956e-004,
	1.6465231e-004,
	1.4774946e-019
};
	int i;

	//-- initialisation des sorties à 0 (pour que la somme fonctionne correctement) --//
	*acRFiltre = 0;
	*acIRFiltre = 0;

	//-- On applique le filtre aux valeurs d'entrée. La boucle permet de simuler la fonction SOMME --//
	for(i=0; i<51; i++){
		*acRFiltre += hk[i] * at(dataBuffer, i).acr;
		*acIRFiltre += hk[i] * at(dataBuffer, i).acir;
	}

	return;
}


/*------------------------------------------------------------------------------*/
/*	Fonction : 	firTest															*/
/*	Params :	char* nomFic													*/
/*	Retour :	absorp acR et acIR filtrées										*/
/*	Desc :		La fonction permet de tester la fonction fir de manière unitaire*/
/*------------------------------------------------------------------------------*/
absorp firTest(char* str){
	absorp absorb;
	DataBuffer buffer;
	float acRPB, acIRPB;
	char x, y;

	//-- On initialise les valeurs actuelles et précédantes --//
	initDataBuffer(&buffer);

	//-- Ouverture du fichier envoyé en paramètre --//
	FILE* pf = fopen(str, "r");
	//-- Si le fichier n'a pu être lu, on envoi un message sur la console et on quitte la fonction --//
	if(!pf){
		printf("Le fichier n'a pu être lu.\n");
		return absorb;
	}

	//-- Boucle faire ... tant qu'on a pas atteint la fin du fichier --//
	do{
		fscanf(pf, "%f,%f,%f,%f,%c,%c", &absorb.acr, &absorb.dcr, &absorb.acir, &absorb.dcir, &x, &y); //On lit la ligne du fichier pf afin d'en extraire les valeurs

		//-- On test si on a pas atteint la fin du fichier. Comme on viens tout juste de lire une nouvelle ligne du fichier, la condition de la boucle ne s'applique pas encore --//
		if(!feof(pf)){
			//-- On ajoute les dernières valeurs lues au buffer --//
			push_front(&buffer, absorb);

			//-- On fait passer les composantes rouge et infrarouge dans le filtre iir --//
			fir(&buffer, &acRPB, &acIRPB);

			//-- On met à jour les données de sortie --//
			absorb.acr = acRPB;
			absorb.acir = acIRPB;
		}
	}while(!feof(pf));

	fclose(pf);

	return absorb;
}
