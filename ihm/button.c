#include "button.h"
#include "fenetre.h"

void initButton(Button* btn, Fenetre* fenetre, char* lbl, int val, int min, int max, int pas, int x, int y)
{
	btn->fenetre = fenetre;
	btn->pos.x = x;
	btn->pos.y = y;

	btn->value = val;
	btn->min = min;
	btn->max = max;
	btn->pas = pas;

	btn->colorFond.r = BUTTON_COULEUR_FOND_R;
	btn->colorFond.g = BUTTON_COULEUR_FOND_V;
	btn->colorFond.b = BUTTON_COULEUR_FOND_B;
	
	btn->colorValeur.r = BUTTON_COULEUR_VALUE_R;
	btn->colorValeur.g = BUTTON_COULEUR_VALUE_V;
	btn->colorValeur.b = BUTTON_COULEUR_VALUE_B;
	
	btn->colorLabel.r = BUTTON_COULEUR_LABEL_R;
	btn->colorLabel.g = BUTTON_COULEUR_LABEL_V;
	btn->colorLabel.b = BUTTON_COULEUR_LABEL_B;

	btn->bgBtn = SDL_CreateRGBSurface(SDL_HWSURFACE, BUTTON_LARGEUR, BUTTON_HAUTEUR, 32, 0, 0, 0, 0);
	SDL_FillRect(btn->bgBtn, NULL, SDL_MapRGB(fenetre->screen->format, BUTTON_COULEUR_FOND));
	btn->txtLabel = TTF_RenderText_Shaded(fenetre->font, lbl, btn->colorLabel, btn->colorFond);
	btn->txtSubButton = TTF_RenderText_Shaded(fenetre->font, "+ -", btn->colorLabel, btn->colorFond);

	char str[4];
	sprintf(str, "%d", val);
	btn->txtValue = TTF_RenderText_Shaded(fenetre->font, str, btn->colorValeur, btn->colorFond);
}

void deleteButton(Button* btn)
{
	SDL_FreeSurface(btn->bgBtn);
	SDL_FreeSurface(btn->txtLabel);
	SDL_FreeSurface(btn->txtValue);
	SDL_FreeSurface(btn->txtSubButton);
}

void updButtonValue(Button* btn, char sign)
{
	if(sign == '+')
	{
		btn->value += btn->pas;
		if(btn->value > btn->max)
		{
			btn->value = btn->max;
		}
	}
	else if(sign == '-')
	{
		btn->value -= btn->pas;
		if(btn->value < btn->min)
		{
			btn->value = btn->min;
		}
	}

	char str[4];
	sprintf(str, "%d", btn->value);
	SDL_FreeSurface(btn->txtValue);
	btn->txtValue = TTF_RenderText_Shaded(btn->fenetre->font, str, btn->colorValeur, btn->colorFond);
}

int updButtonState(Button* btn, SDL_Event* event)
{
	if(! (event->button.x < btn->pos.x + BUTTON_SUB_BUTTON_OFFSET ||
			event->button.x > btn->pos.x + BUTTON_SUB_BUTTON_OFFSET + btn->txtSubButton->w ||
			event->button.y < btn->pos.y ||
			event->button.y > btn->pos.y + BUTTON_HAUTEUR ))
	{
		if(event->button.button == SDL_BUTTON_WHEELUP || event->button.x < btn->pos.x + BUTTON_SUB_BUTTON_OFFSET + btn->txtSubButton->w / 2)
		{
			updButtonValue(btn, '+');
			return 1;
		}
		else if(event->button.button == SDL_BUTTON_WHEELDOWN)
		{
			updButtonValue(btn, '-');
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

void drawButton(Button* btn) 
{
	SDL_Rect pos;

	pos.x = btn->pos.x;
	pos.y = btn->pos.y;
	SDL_BlitSurface(btn->bgBtn, NULL, btn->fenetre->screen, &pos);

	pos.x += BUTTON_LABEL_OFFSET;
	SDL_BlitSurface(btn->txtLabel, NULL, btn->fenetre->screen, &pos);

	pos.x = btn->pos.x + BUTTON_VALUE_OFFSET;
	SDL_BlitSurface(btn->txtValue, NULL, btn->fenetre->screen, &pos);

	pos.x = btn->pos.x + BUTTON_SUB_BUTTON_OFFSET;
	SDL_BlitSurface(btn->txtSubButton, NULL, btn->fenetre->screen, &pos);
}