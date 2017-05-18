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
int newGame(){
  int choose;
  
  printf("------- Menu Hex -------\n");
  printf("1 - Nouvelle partie\n");
  printf("2 - Charger partie\n");
  printf("3 - Quitter\n");


  scanf("%d", &choose);
  
  return choose;
}