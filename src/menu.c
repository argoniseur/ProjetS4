#include "menu.h"

/* Initialise les informations des deux joueurs */
void initJoueurs(Player *pa, Player *pb){
        *pa = (Player)malloc(sizeof(Player));
        *pb = (Player)malloc(sizeof(Player));
        (*pa)->value = 1;
        (*pb)->value = 2;
        (*pa)->dernierCoupJouer = NULL;
        (*pb)->dernierCoupJouer = NULL;
        (*pa)->nbCoups = 0;
        (*pb)->nbCoups = 0;
}