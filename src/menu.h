#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Plateau.h"

#define NOMJOUEUR 20

typedef struct s_player{
        int value;
        char* nom;
        Cell dernierCoupJouer;
        int nbCoups;
}*Player;

void initJoueurs(Player *pa, Player *pb);

#endif



