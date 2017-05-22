#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

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

/* Initialise les informations d'un joueur */
Player init_players(int num);

/* Saisie des coordonnees d'entrer */
Board get_and_insert_coord(Board b, Player *p, Historique histo[], int nbTurn, int *quitter);

/* Affichage du menu du jeu */
int newGame();

/* Mise à jour de l'historique de toutes les parties jouées */
void historical(Player pa, Player pb);

/* Initialisation de l'historique */
void init_histo(Historique histo[]);

/* Sauvegarder la partie */
void save_game(Board b, Player aa, Player bb, Historique histo[], int nbTurn);

Board load_game(Board b);

#endif