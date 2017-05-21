//Module plateau
//Par: Gaffiero Allison, Courdy-Bahsoun Clémence, de Fercluc Louis
//Dernière modification: 21.05.2017
//Objectif: plateau de jeu
//	    Permet l'utilisation d'un plateau de jeu
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Plateau.h"
#include "menu.h"
#define N 11

#define E 0
#define SE 1
#define SO 2
#define O 3
#define NO 4
#define NE 5

#define white_p 1
#define black_p 2

/**
 * Initialise le bord gauche du plateau
 * Paramètre : b = plateau du jeu
 * Retourne le plateau du jeu entré en paramètre avec le bord gauche inititialisé
 */
Board init_B1(Board b){
    for(int i=0;i<N;i++){
        b->sentinelB1->neighboors[i] = b->tab[i*N];
        b->tab[i*N]->neighboors[SO] = b->sentinelB1;
        b->tab[i*N]->neighboors[O] = b->sentinelB1;
    }
    return b;
}

/**
 * Initialise le bord droit du plateau
 * Paramètre : b = plateau du jeu
 * Retourne le plateau du jeu entré en paramètre avec le bord droit inititialisé
 */
Board init_B2(Board b){
    for(int i=0;i<N;i++){
        b->sentinelB2->neighboors[i] = b->tab[(i*N)+(N-1)];
        b->tab[(i*N)+(N-1)]->neighboors[E] = b->sentinelB2;
        b->tab[(i*N)+(N-1)]->neighboors[NE] = b->sentinelB2;
    }
    return b;
}

/**
 * Initialise le bord supérieur du plateau
 * Paramètre : b = plateau du jeu
 * Retourne le plateau du jeu entré en paramètre avec le bord supérieur inititialisé
 */
Board init_W1(Board b){
    for(int i=0;i<N;i++){
        b->sentinelW1->neighboors[i] = b->tab[i];
        b->tab[i]->neighboors[NE] = b->sentinelW1;
        b->tab[i]->neighboors[NO] = b->sentinelW1;
    }
    return b;
}

/**
 * Initialise le bord inférieur du plateau
 * Paramètre : b = plateau du jeu
 * Retourne le plateau du jeu entré en paramètre avec le bord inférieur inititialisé
 */
Board init_W2(Board b){
    for(int i=0;i<N;i++){
        b->sentinelW2->neighboors[i] = b->tab[(N*(N-1))+i];
        b->tab[(N*(N-1))+i]->neighboors[SE] = b->sentinelW2;
        b->tab[(N*(N-1))+i]->neighboors[SO] = b->sentinelW2;
    }
    return b;
}


/**Creation du plateau
 * Par COURDY-BAHSOUN Clémence
 * Dernière modification: 13.04.2017
 */
 
/**
 * Création d'une cellule
 * Paramètre : index = indice de la cellule
 * Retourne la cellule créée, initialisée à l'indice index et à la valeur 0
 */
Cell create_cell(int index){ 
    //allocation espace mémoire pour une cellule
    Cell c = (Cell)malloc(sizeof(struct s_cell));
    
    c->index = index;
    
    //initialisation du contenu de la cellule à 0 = case de plateau vide
    c->value = 0;
    c->neighboors = (Cell *)malloc(6*sizeof(struct s_cell));
    return c;
}

/**
 * Création d'une sentinelle
 * Paramètre : val = valeur de la cellule sentinelle
 * Retourne la cellule sentinelle créée, initialisée à l'indice -1 et à la valeur val
 */
Cell create_sentinel(int val){
    Cell s = (Cell)malloc(sizeof(struct s_cell));
    
    s->value = val;
    s->index = -1;
    s->neighboors = (Cell *)malloc(N*(sizeof(Cell)));
	return s;
}

/**
 * Création d'un plateau
 * Aucun parametres d'entrés
 * Retourne le plateau créé et initialisés
 */
Board create_board(){ 
    
    Board b=(Board)malloc(sizeof(struct s_board));
    
    b->size = N*N;
    
    //Création de la sentinelle pour les bords supérieur et inférieur
    b->sentinelW1 = create_sentinel(-2);
    b->sentinelW2 = create_sentinel(-3);

    //Création de la sentinelle pour les bords gauche et droite
    b->sentinelB1 = create_sentinel(-4);
    b->sentinelB2 = create_sentinel(-6);
    
    for(int i=0;i<b->size;i++)
        b->tab[i] = create_cell(i);
      
    //Chainage des sentinelles aux cellules bordantes
        b = init_B1(b);
        b = init_W1(b);
        b = init_B2(b);
        b = init_W2(b);        

    //Chainage des cellules du palteau
    for(int i=0;i<b->size;i++){
      
        //chainage est
        if((i+1)%N != 0)
            b->tab[i]->neighboors[E] = b->tab[i+1];

        //chainage sud est
        if(i+N < N*N)
            b->tab[i]->neighboors[SE] = b->tab[i+N];

        //chainage sud ouest
        if((i+N)%N != 0 && i < N*N-N)
            b->tab[i]->neighboors[SO] = b->tab[i+N-1];

        //chainage ouest
        if(i%N != 0)
            b->tab[i]->neighboors[O] = b->tab[i-1];

        //chainage nord ouest
        if(i >= N)
            b->tab[i]->neighboors[NO] = b->tab[i-N];

        //chainage nord est
        if((i-N+1)%N > 0)
            b->tab[i]->neighboors[NE] = b->tab[i-N+1];
    }

    return b;
}

/**
 * Insertion d'une valeur dans le plateau
 * Paramètres : b = plateau du jeu
 * 				index = indice de la cellule où il faut insérer une valeur
 *				value = valeur à insérer dans le plateau à l'indice index
 * Retourne le plateau avec la valeur value à l'indice index du plateau
 */
Board insert_cell_value(Board b, int index, int value){
    b->tab[index]->value = value;
    return b;
}

/**
 * Vérification de la validité des coordonnées
 * Paramètres : a = entier correspondant à la ligne
 * 				c = entier correspondant à la colonne
 * Retourne un boolean, faux si a ou c n'est pas dans l'intervalle [1;N], vrai sinon
 */
bool check_coord(int a, int c){
    if(a<1 || a>N)
        return false;
    if(c<1 || c>N)
        return false;

    return true;
}

/**
 * Vérification si une cellule est vide
 * Paramètres : b = plateau du jeu
 * 				a = entier correspondant à la ligne
 * 				c = entier correspondant à la colonne
 * Retourne un boolean si la case correspondant n'est pas vide
 */
bool check_cell(Board b, int a, int c){
    if((a>0 && a<=N) && (c>0 && c<=N))
        if(b->tab[N*(a-1)+(c-1)]->value != 0)
            return false;
    return true;
}

/**
 * Recherche si le joueur white_p est gagnant
 * Paramètres : b = plateau du jeu
 * 				cell = tableau de cellule
 */
void search_W(Board b, int cells[]){
    int cpt = 0;

    for(int i = 0;i<N;i++){
        if(b->tab[i]->value == white_p){
            cells[cpt] = i;
            cpt++;
        }
    }
    cells[N] = cpt;
}

/**
 * Recherche si le joueur black_p est gagnant
 * Paramètres : b = plateau du jeu
 * 				cell = tableau de cellule
 */
void search_B(Board b, int cells[]){
    int cpt = 0;

    for(int i = 0;i<N;i++){
        if(b->tab[i*N]->value == black_p){
            cells[cpt] = i*N;
            cpt++;
        }
    }
    cells[N] = cpt;
}

/**
 * Recherche la cellule tst
 * Paramètres : tested = tableau de cellule
 *				tst = cellule à trouver
 *				cpt_tested = nombre de cellule dans le tableau tested
 * Retourne un boolean, vrai si la cellule test est dans le tableau tested, faux sinon
*/
bool tested_cell(Cell tested[], Cell tst, int cpt_tested){
    for(int i=0;i<cpt_tested;i++){
        //printf("tested: value_c=%d, index_c=%d\n",tested[i]->value, tested[i]->index);
        if(tested[i] == tst)
            return true;
    }
    return false;
}

/**
 * Recherche si un joueur a relié ses deux bords du plateau
 * Paramètres : tst = cellule de départ située sur un bord
 *				tested = tableau de cellule
 *				cpt_tested = nombre de cellule dans le tableau tested
 *				joueur = entier désignant le joueur
 * Retourne un boolean, vrai si le joueur a relié les deux bords du plateau
*/
bool search_winner_through(Cell tst, Cell tested[], int cpt_tested, int joueur){
    bool win = false;
    for(int i = 0;i<6;i++){
        if(tst->neighboors[i]->value == -3*joueur)
            return true;

        if(tst->neighboors[i]->value == joueur && !tested_cell(tested, tst->neighboors[i], cpt_tested)){
            tested[cpt_tested] = tst->neighboors[i];
            cpt_tested++;
            win = search_winner_through(tst->neighboors[i],tested,cpt_tested,joueur);
            if(win)
                return win;
        }
        //int z; printf("value_c=%d, index_c=%d, i=%d, value=%d, win=%d",tst->value, tst->index, i, tst->neighboors[i]->value, win); scanf("%d", &z);
    }
    return win;
}

/**
 * Rechercher gagnant
 * Paramètre : b = plateau du jeu
 * Appel la fonction search_winner_through autant de fois qu'il y a de cellule blanche ou noire sur les bords
 * Retourne un entier désignant le gagnant du jeu, ou 0 s'il n'y a pas de gagnant
 */
int search_winner(Board b){
    int cells[N+1];
    Cell tested[((N*N)/2)+1];
    int cpt_tested = 0;

    search_W(b,cells);
    for(int i = 0;i<((N*N)/2)+1;i++){
        tested[i] = NULL;
    }

    for(int i = 0; i<cells[N]; i++){
        if(search_winner_through(b->tab[cells[i]],tested,cpt_tested,white_p))
            return white_p;
    }

    search_B(b,cells);
    for(int i = 0;i<((N*N)/2)+1;i++){
        tested[i] = NULL;
    }

    for(int i = 0; i<cells[N]; i++){
        if(search_winner_through(b->tab[cells[i]],tested,cpt_tested,black_p))
            return black_p;
    }    
    return 0;
}

/**Suppression du plateau
 * Par COURDY-BAHSOUN Clémence
 * Dernière modification le 15.04.2017
 */
  
/**
 * Destruction d'une cellule
 * Paramètre : c = cellule à supprimer
 * Supprime la cellule et ses cellules voisines
 */
void cell_delete(Cell c){
    free(c->neighboors);
    free(c);
}

/**
 * Destruction d'une sentinelle
 * Paramètre : s = sentinelle à supprimer
 * Supprime la sentinelle et ses cellules voisines
 */
void sentinel_delete(Cell s){
    free(s->neighboors);
    free(s);
}

/**
 * Suppression du plateau
 * Paramètre : b = plateau à supprimer
 * Supprime toutes les cellules et les sentinelles
 */
void board_delete(Board b){
  
    for(int i=0;i<b->size;i++)
        cell_delete(b->tab[i]);
  
    sentinel_delete(b->sentinelB1);
    sentinel_delete(b->sentinelB2);
    sentinel_delete(b->sentinelW1);
    sentinel_delete(b->sentinelW2);
    free(b);
}

