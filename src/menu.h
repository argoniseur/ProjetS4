#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Plateau.h"

#define NOMJOUEUR 20

typedef struct s_player{
	char nom[20];
    int value;
    int dernierCoupJouer;
    int nbCoups;
}*Player;

Player init_players(int num);

Board get_and_insert_coord(Board b, Player *p);

int newGame();

void historical(Player pa, Player pb);
#endif



