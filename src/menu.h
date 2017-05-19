#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Plateau.h"

#define NOMJOUEUR 20

typedef struct s_player{
	char nom[NOMJOUEUR+1];
    int value;
    int dernierCoupJouer;
    int nbCoups;
}*Player;

typedef struct s_historique{
	int player_c;
	int line;
	int column;
}*Historique;

Player init_players(int num);

Board get_and_insert_coord(Board b, Player *p, Historique histo[], int nbTurn, int *quitter);

int newGame();

void historical(Player pa, Player pb);

void init_histo(Historique histo[]);

void save_game(Board b, Player aa, Player bb, Historique histo[], int nbTurn);

#endif