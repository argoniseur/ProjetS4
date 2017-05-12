#include "menu.h"
#include "Plateau.h"

/* Initialise les informations des deux joueurs */
void initJoueurs(Player *pa, Player *pb){
        *pa = (Player)malloc(sizeof(Player));
        *pb = (Player)malloc(sizeof(Player));
        (*pa)->value = 1;
        (*pb)->value = 2;
        (*pa)->dernierCoupJouer = -1;
        (*pb)->dernierCoupJouer = -1;
        (*pa)->nbCoups = 0;
        (*pb)->nbCoups = 0;
}

/*Saisie des coordonnees d'entrer*/
Board get_and_insert_coord(Board b, Player *p){
        int lig, col;
        printf("Joueur %d, coup numéro %d\n", (*p)->value, (*p)->nbCoups);
  
        if((*p)->dernierCoupJouer != -1)
                printf("Votre dernier coup joué: [%d,%d]\n", (((*p)->dernierCoupJouer)%N)+1, (((*p)->dernierCoupJouer)/N)+1);
  
        printf("Saisissez les coordonnées de votre nouveau coup au format [ligne,colonne]\n");
        scanf("%d", &lig); scanf("%d", &col);
        (*p)->dernierCoupJouer = N*(lig-1)+(col-1);
        b = insert_cell_value(b, (*p)->dernierCoupJouer, (*p)->value);
        (*p)->nbCoups++;

        return b;
}