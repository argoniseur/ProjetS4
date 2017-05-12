#include "menu.h"
#include "Plateau.h"

/* Initialise les informations des deux joueurs */
void init_players(Player *pa, Player *pb){
        *pa = (Player)malloc(sizeof(Player));
        *pb = (Player)malloc(sizeof(Player));
        (*pa)->value = 1;
        (*pb)->value = 2;
        (*pa)->dernierCoupJouer = -1;
        (*pb)->dernierCoupJouer = -1;
        (*pa)->nbCoups = 0;
        (*pb)->nbCoups = 0;
}

/*affichage du menu de jeu*/
char newGame(){
  char choose;
  
  printf("Souhaitez vous lancer une partie ? [O/N]\n [O] pour charger une nouvelle partie\n [N] pour quitter le jeu\n");
  scanf("%c", &choose);
  
  return choose;
}