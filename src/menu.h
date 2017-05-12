#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Plateau.h"

#define NOMJOUEUR 20

typedef struct s_player{
        int value;
        int dernierCoupJouer;
        int nbCoups;
}*Player;

void initJoueurs(Player *pa, Player *pb);

Board get_and_insert_coord(Board b, Player *p);

char newGame();
#endif



