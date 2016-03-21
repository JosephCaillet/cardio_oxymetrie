//
// Created by joseph on 21/03/16.
//

#ifndef IHM_BUTTON_H
#define IHM_BUTTON_H

#include <SDL/SDL.h>

struct Fenetre;
typedef struct Fenetre Fenetre;

#define BUTTON_LARGEUR 250
#define BUTTON_HAUTEUR 70

#define BUTTON_LABEL_OFFSET 5
#define BUTTON_VALUE_OFFSET 50
#define BUTTON_SUB_BUTTON_OFFSET 150

#define BUTTON_COULEUR_FOND_R 139
#define BUTTON_COULEUR_FOND_V 140
#define BUTTON_COULEUR_FOND_B 134
#define BUTTON_COULEUR_FOND BUTTON_COULEUR_FOND_R, BUTTON_COULEUR_FOND_V, BUTTON_COULEUR_FOND_B

#define BUTTON_COULEUR_VALUE_R 200
#define BUTTON_COULEUR_VALUE_V 200
#define BUTTON_COULEUR_VALUE_B 200
#define BUTTON_COULEUR_VALUE BUTTON_COULEUR_VALUE_R, BUTTON_COULEUR_VALUE_V, BUTTON_COULEUR_VALUE_B

#define BUTTON_COULEUR_LABEL_R 100
#define BUTTON_COULEUR_LABEL_V 100
#define BUTTON_COULEUR_LABEL_B 100
#define BUTTON_COULEUR_LABEL BUTTON_COULEUR_LABEL_R, BUTTON_COULEUR_LABEL_V, BUTTON_COULEUR_LABEL_B

struct Button
{
	Fenetre* fenetre;
	SDL_Rect pos;
	SDL_Surface* bgBtn;
	SDL_Surface* txtLabel;
	SDL_Surface* txtValue;
	SDL_Surface* txtSubButton;
	
	int value;
	int min;
	int max;
	int pas;

	SDL_Color colorFond;
	SDL_Color colorValeur;
	SDL_Color colorLabel;
};
typedef struct Button Button;

void initButton(Button* btn, Fenetre* fenetre, char* lbl, int val, int min, int max, int pas, int x, int y);
void deleteButton(Button* btn);
void updButtonValue(Button* btn);
int updButtonState(Button* btn, SDL_Event* event);
void drawButton(Button* btn);

#endif //IHM_BUTTON_H