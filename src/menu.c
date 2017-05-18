//Module menu
//Par: Gaffiero Allison, Courdy-Bahsoun Clémence, de Fercluc Louis
//Dernière modification: 12.05.2017
//Objectif: l'interaction avec les joueurs
//	    Permet le stockage des données concernant les joueurs et leurs modifications
//Dépendances: Module plateau

#include "menu.h"

/**
 * Initialise les informations des deux joueurs 
 * Rôle des paramètres: pa et pb sont des paramètres d'entrées/sorties qui sont initialisés avec les informations propres aux deux joueurs
 */
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

<<<<<<< HEAD
/**
 * Saisie des coordonnees d'entrer
 * Paramètres: b = plateau en entrée modifié par l'insertion d'un pion de la valeur associé à p qui est alors retourné en sorti
 * 		p = Information du joueur dont c'est le tour qui sont affichés puis mis à jour 
 */
Board get_and_insert_coord(Board b, Player *p){
        int lig, col;
        (*p)->nbCoups++;
        printf("Joueur %d, coup numéro %d\n", (*p)->value, (*p)->nbCoups);
  
        if((*p)->dernierCoupJouer != -1)
                printf("Votre dernier coup joué: [%d,%d]\n", (((*p)->dernierCoupJouer)%N)+1, (((*p)->dernierCoupJouer)/N)+1);
  
        bool tst;
        do{
            tst = false;
            printf("Saisissez les coordonnées de votre nouveau coup au format [ligne,colonne]\n");
	    printf("Numéro de ligne: "); scanf("%d", &lig);
	    printf("Numéro de colonne: "); scanf("%d", &col);

            if (!check_coord(lig, col))
            {
                printf("Coordonnées invalide\n");
                tst = true;
            }

            if (!check_cell(b,lig,col)){
                printf("Case occupée\n");
                tst = true;
            }

        }while(tst);
        
        (*p)->dernierCoupJouer = (N*(lig-1))+(col-1);
        
        b = insert_cell_value(b, (*p)->dernierCoupJouer, (*p)->value);

        return b;
}

/**
 * affichage du menu de jeu
 * Aucun parametres d'entrés
 * Retourne un char faisant office de booléen pour savoir si une nouvelle partie doit être lancé O-> OUI / N-> NON
 */
char newGame(){
  char choose;
=======
/*affichage du menu de jeu*/
int newGame(){
  int choose;
>>>>>>> 55ca53773ca48f1d7aa9cb35d144419ffc6de51e
  
  printf("------- Menu Hex -------\n");
  printf("1 - Nouvelle partie\n");
  printf("2 - Charger partie\n");
  printf("3 - Quitter\n");


  scanf("%d", &choose);
  
  return choose;
}