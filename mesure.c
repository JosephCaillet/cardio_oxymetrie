/*==============================================================================================================*/
/*	Nom : 		mesure.c																						*/
/*	Auteur : 	Joseph CAILLET																					*/
/*	Update :	Thomas COUSSOT																					*/
/*	Desc : 		La fonction a pour but de calculer le BPM et le spO2 avec les données absorp qui arrivent petit */
/*				à petit.																						*/
/*==============================================================================================================*/

#include "mesure.h"
#include <stdio.h>

/*------------------------------------------------------------------------------*/
/*	Fonction : 	mesure															*/
/*	Params :	absorp absorb, Acmesures* acR et acIR							*/
/*	Retour :	oxy* oxyDatas, Acmesures* acR et acIR							*/
/*	Desc :		La fonction reçoit les dernières valeurs d'absorption ainsi que */
/*				des sauvegardes de données sur acR et acIR. La fonction renvoie */
/*				les dernières valeurs de BPM et de spO2 calculées et met à jour */
/*				les données sauvegardées.										*/
/*------------------------------------------------------------------------------*/
void mesure(oxy* oxy, absorp absorp, AcMesures* acRm, AcMesures* acIRm)
{
	int periodeAquise = 0;
	//static int mesure = 0;

	//-- On détecte le dépassement de seuil et on met à jour le max et le min si nécessaire --//
	majMaxMinDepasseSeuil(acRm, absorp.acr);
	majMaxMinDepasseSeuil(acIRm, absorp.acir);

	//upd passage par 0
//	majPassageZero(acRm, absorp.acr);
//	majPassageZero(acIRm, absorp.acir);

	//-- On détecte si une nouvelle période a été acquise sur une des deux courbes (r et ir)(ou les deux) --//
	periodeAquise += majBpm(acRm, absorp.acr);
	periodeAquise += majBpm(acIRm, absorp.acir);

	//-- Si au moins une nouvelle période a été détecté, on met à jour le spO2 et le BPM --//
	if(periodeAquise > 0)
	{
//		puts("Avant spo2 :");
//		printf("acRmax : %f, acRmin : %f\nacIRmax : %f, acIRmin : %f\ndcR : %f, dcIR : %f\n", acRm->maxValid, acRm->minValid, acIRm->maxValid, acIRm->minValid, absorp.dcr, absorp.dcir);
		oxy->spo2 = calculSPo2(acRm->maxValid, acRm->minValid, acIRm->maxValid, acIRm->minValid, absorp.dcr, absorp.dcir);
		oxy->pouls = (acRm->bpm + acIRm->bpm) / 2.0;
		//printf("Rbmp: %f - IRbmp: %f\n", acRm->bpm, acIRm->bpm);
		//printf("ACR: %f - ACIR: %f\n", absorp.acr, absorp.acir);
		//printf("-- Absorb --\nacr : %f\ndcr : %f\nacir : %f\ndcir : %f\n", absorp.acr, absorp.dcr, absorp.acir, absorp.dcir);
	}
	//printf("%d --- ", ++mesure);
}
//85spo2
//70bpm

/*------------------------------------------------------------------------------*/
/*	Fonction : 	majMaxMinDepasseSeuil											*/
/*	Params :	AcMesures* ac, int acNew										*/
/*	Retour :	Acmesures* ac													*/
/*	Desc :		La fonction reçoit la dernière valeur d'absorption ainsi que	*/
/*				des sauvegardes de données sur ac. Elle met à jour le min et le */
/*				max si nécessaire. Si tel est le cas, il y a également un		*/
/*				dépassement de seuil (le max n'est jamais inférieur au seuil 	*/
/*				haut et inversement pour le min).								*/
/*------------------------------------------------------------------------------*/
void majMaxMinDepasseSeuil(AcMesures* ac, int acNew)
{
	if(acNew > ac->max)
	{
		ac->max = acNew;
		ac->seuilHautPasse = 1;
	}
	else if(acNew < ac->min)
	{
		ac->min = acNew;
		ac->seuilBasPasse = 1;
	}
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	majBpm															*/
/*	Params :	AcMesures* ac, float ech_ac										*/
/*	Retour :	int nouvellePeriode, AcMesures* ac								*/
/*	Desc :		La fonction calcul le nouveau bpm avec la nouvelle valeur de	*/
/*				compteur ainsi que l'ancienne. Il y a également réinitialisation*/
/*				de données sauvegardées sur ac.									*/
/*------------------------------------------------------------------------------*/
int majBpm(AcMesures* ac, float ech_ac)
{
	static float lastbpm = 425;
	if(ech_ac < SEUIL_BAS && ac->seuilHautPasse == 1)
	{
//		printf("Une période à été aquise sur : %s\n", ac->s);
		//affAcMesure(*ac);
		
		//-- Réinitialisation des seuils passés ainsi que les max et min --//
		ac->seuilHautPasse = 0;
		ac->seuilBasPasse = 0;
		//ac->passagePar0 = 1;

		ac->maxValid = ac->max;
		ac->max = SEUIL_HAUT;
		ac->minValid = ac->min;
		ac->min = SEUIL_BAS;

		//-- maj du bpm --//
		ac->bpm = (float)30000 / (((float)ac->nbPoints + (float)lastbpm)/2)  ;
//		ac->bpm = (float)30000 / (float)ac->nbPoints;
		printf("cpt : %d\tcpt_old : %1f\tbpm : %f\tbpm_old : %f\tbpm_moy : %f\n", ac->nbPoints, lastbpm, (float)30000/(float)ac->nbPoints, (float)30000/(float)lastbpm, ac->bpm);
		lastbpm = ac->nbPoints; //on met à jour l'ancienne valeur (de compteur, le fonctionnement a été modifié entre temps, d'où le nom peu représentatif de la variable)
		ac->nbPoints = 1;
		
		return 1;
	}

	ac->nbPoints++;

	return 0;
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	calculSPo2														*/
/*	Params :	float acRmax, float acRmin, float acIRmax, float acIRmin,		*/
/*				float dcR, float dcIR											*/
/*	Retour :	float spO2														*/
/*	Desc :		La fonction calcul le nouveau spO2 avec les valeurs de max et	*/
/*				min d'acr et d'acir ainsi que dcr et dcir.						*/
/*------------------------------------------------------------------------------*/
float calculSPo2(float acRmax, float acRmin, float acIRmax, float acIRmin, float dcR, float dcIR)
{
	//puts("Ds spo2 :");
	//printf("acRmax : %f, acRmin : %f\nacIRmax : %f, acIRmin : %f\ndcR : %f, dcIR : %f\n", acRmax, acRmin, acIRmax, acIRmin, dcR, dcIR);
	float ptpACr = acRmax - acRmin; //Valeur peek-to-peek d'acr
	float rapport1 = ptpACr / dcR;
//	printf("le rapport1 vaut : %f\n", rapport1);

	float ptpACir = acIRmax - acIRmin; //Valeur peek-to-peek d'acir
	float rapport2 = ptpACir / dcIR;
//	printf("le rapport2 vaut : %f\n", rapport2);

//	printf("le ratio vaut : %f\n", rapport1 / rapport2);
	return  convertRatioToSPO2( rapport1 / rapport2 );
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	convertRatioToSPO2												*/
/*	Params :	float ratio														*/
/*	Retour :	float spO2														*/
/*	Desc :		La fonction calcul le  spO2 en fonction du ratio envoyé. La		*/
/*				courbe de spO2/ratio peut-être représentée par deux droites dont*/
/*				les coeficients sont rentrés en dur dans la fonction			*/
/*------------------------------------------------------------------------------*/
float convertRatioToSPO2(float ratio)
{
	if(ratio < 1)
	{
		return -25 * ratio + 110;
	}
	return -35.71429 * ratio + 121.4285714;
}

//-- Fonction de test afin d'afficher des résultats intermédiaires --//
void affAcMesure(AcMesures ac)
{
	printf("-- %s --\n", ac.s);
	printf("SeuilHautPasse : %d\n", ac.seuilHautPasse);
	printf("SeuilBasPasse : %d\n", ac.seuilBasPasse);

	printf("LastValue : %d\n", ac.lastValue);
	printf("NbPoints: %d\n", ac.nbPoints);

	printf("Min : %f\n", ac.min);
	printf("Max : %f\n", ac.max);
}

/*------------------------------------------------------------------------------*/
/*	Fonction : 	mesureTest														*/
/*	Params :	char* nomFic													*/
/*	Retour :	bpm et spO2														*/
/*	Desc :		La fonction permet de tester la fonction mesure de manière		*/
/*				unitaire.														*/
/*------------------------------------------------------------------------------*/
oxy mesureTest(char* str){
	oxy oxyDatas;
	absorp absorb;
	AcMesures acRm = {0,0,0, 0,0, SEUIL_BAS,SEUIL_BAS,SEUIL_HAUT,SEUIL_HAUT, 0.0, "R"};
	AcMesures acIRm = {0,0,0, 0,0, SEUIL_BAS,SEUIL_BAS,SEUIL_HAUT,SEUIL_HAUT, 0.0, "IR"};
	char x, y;

	FILE* pf = fopen(str, "r");
	if(!pf){
		printf("Le fichier n'a pu être lu.\n");
		return oxyDatas;
	}

	do{
		fscanf(pf, "%f,%f,%f,%f,%c,%c", &absorb.acr, &absorb.dcr, &absorb.acir, &absorb.dcir, &x, &y);

		if(!feof(pf)){
			mesure(&oxyDatas, absorb, &acRm, &acIRm);
		}
	}while(!feof(pf));


	return oxyDatas;
}
