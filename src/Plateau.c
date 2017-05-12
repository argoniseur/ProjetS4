#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Plateau.h"
#define N 11

#define E 0
#define SE 1
#define SO 2
#define O 3
#define NO 4
#define NE 5

//Bord gauche
Board init_B1(Board b){
    for(int i=0;i<N;i++){
        b->sentinelB1->neighboors[i] = b->tab[i*N];
        b->tab[i*N]->neighboors[SO] = b->sentinelB1;
        b->tab[i*N]->neighboors[O] = b->sentinelB1;
    }
    return b;
}

//Bord droit
Board init_B2(Board b){
    for(int i=0;i<N;i++){
        b->sentinelB2->neighboors[i] = b->tab[(i*N)+(N-1)];
        b->tab[(i*N)+(N-1)]->neighboors[E] = b->sentinelB2;
        b->tab[(i*N)+(N-1)]->neighboors[NE] = b->sentinelB2;
    }
    return b;
}

//Bord haut
Board init_W1(Board b){
    for(int i=0;i<N;i++){
        b->sentinelW1->neighboors[i] = b->tab[i];
        b->tab[i]->neighboors[NE] = b->sentinelW1;
        b->tab[i]->neighboors[NO] = b->sentinelW1;
    }
    return b;
}

//Bord bas
Board init_W2(Board b){
    for(int i=0;i<N;i++){
        b->sentinelB1->neighboors[i] = b->tab[(N*(N-1))+i];
        b->tab[(N*(N-1))+i]->neighboors[SE] = b->sentinelW2;
        b->tab[(N*(N-1))+i]->neighboors[SO] = b->sentinelW2;
    }
    return b;
}


/**Creation du plateau
 * Par COURDY-BAHSOUN Clémence
 * Dernière modification: 13.04.2017
 */

  //Fonction de creation d'une Cellule
Cell create_cell(int index){ 
    //allocation espace mémoire pour une cellule
    Cell c = (Cell)malloc(sizeof(struct s_cell));
    
    c->index = index;
    
    //initialisation du contenu de la cellule à 0 = case de plateau vide
    c->value = 0;
    c->neighboors = (Cell *)malloc(6*sizeof(struct s_cell));
    return c;
}
  
  //Fonction de création d'une sentinelle
Cell create_sentinel(int val){
    Cell s = (Cell)malloc(sizeof(struct s_cell));
    
    s->value = val;
    s->index = -1;
    s->neighboors = (Cell *)malloc(N*(sizeof(Cell)));
	return s;
}

//Fonction de création du plateau
Board create_board(){ 
    
    Board b=(Board)malloc(sizeof(struct s_board));
    
    b->size = N*N;
    
    //Création de la sentinelle pour les bord supérieure et inférieure
    b->sentinelB1 = create_sentinel(3);
    b->sentinelB2 = create_sentinel(1);
    
    //Création de la sentinelle pour les bord gauche et droite
    b->sentinelW1 = create_sentinel(4);
    b->sentinelW2 = create_sentinel(2);
    
    for(int i=0;i<b->size;i++)
        b->tab[i] = create_cell(i);
      
    //Chainage des sentinel au cellules bordantes
        b = init_B1(b);
        b = init_B2(b);
        b = init_W1(b);
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
        if(i+N-1 < N*N)
            b->tab[i]->neighboors[SO] = b->tab[i+N-1];

        //chainage ouest
        if(i%N != 0)
            b->tab[i]->neighboors[O] = b->tab[i-1];

        //chainage nord ouest
        if(i-N > 0)
            b->tab[i]->neighboors[NO] = b->tab[i-N];

        //chainage nord est
        if(i-N+1 > 0)
            b->tab[i]->neighboors[NE] = b->tab[i-N+1];
    }

    return b;
}

/**Suppression du plateau
 * Par COURDY-BAHSOUN Clémence
 * Dernière modification le 15.04.2017
 */
  
    //Destructon d'une cellule
  
void cell_delete(Cell c){
    free(c);
}

  //Suppression d'une sentinelle
void sentinel_delete(Cell s){
    
    for(int i=0;i<N;i++)
        cell_delete(s->neighboors[i]);
    
    free(s->neighboors);
    
    free(s);
}

//Suppression du plateau
void board_delete(Board b){
  
    for(int i=0;i<b->size;i++)
        cell_delete(b->tab[i]);
  
    sentinel_delete(b->sentinelB1);
    sentinel_delete(b->sentinelB2);
    sentinel_delete(b->sentinelW1);
    sentinel_delete(b->sentinelW2);
  
    free(b);
}

