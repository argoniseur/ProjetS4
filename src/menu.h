#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOMJOUEUR 20

struct s_player{
        int value;
        char nom[NOMJOUEUR+1];
        Cell dernierCoupJouer;
        int nbCoups;
};

initJoueurs(Player *pa, Player *pb);

int chooseFirstPlayer(Player *pa,Player *pb);

#endif



