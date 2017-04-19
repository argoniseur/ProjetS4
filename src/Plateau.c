#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Plateau.h"
#define N 11

struct s_cell{
	int value;
	int index;
	struct s_cell **neighboors;
};

struct s_board{
	int size;
	Cell tab[N*N];
	Cell sentinelB1;
	Cell sentinelB2;
	Cell sentinelW1;
	Cell sentinelW2;
};

/*Board init_B1(Board b, int n){
    // assert
    int val;
    for(int i=0;i<N;i++){
        val = board_ith(b, i);
        b->sentinelB1->edges[i] = val;
    }
    return b;

}*/


/**Creation du plateau
 * Par COURDY-BAHSOUN Clémence
 * Dernière modification: 13.04.2017
 */

  //Fonction de creation d'une Cellule
  
  Cell create_cell(int index){
    
    //allocation espace mémoire pour une cellule
    Cell c=(Cell)malloc(sizeof(struct s_cell));
    
    c->index=index;
    
    //initialisation du contenu de la cellule à 0 = case de plateau vide
    c->value=0;
    return c;
  }
  
  //Fonction de création d'une sentinelle
  
  Cell create_sentinel(int val){
    
    Cell s=(Cell)malloc(sizeof(struct s_cell));
    
    s->value=val;
    
    s->neighboors = (Cell *)malloc(N*(sizeof(Cell)));
	return s;
  }

//Fonction de création du plateau
Board create_board(){
    
  Board b=(Board)malloc(sizeof(struct s_board));
    
  b->size=N*N;
    
 //Création de la sentinelle pour les bord supérieure et inférieure
  b->sentinelB1=create_sentinel(1);
  b->sentinelB2=create_sentinel(1);
    
 //Création de la sentinelle pour les bord gauche et droite
  b->sentinelW1=create_sentinel(2);
  b->sentinelW2=create_sentinel(2);
    
  for(int i=0;i<b->size;i++)
    b->tab[i]=create_cell(i);
      
 //Chainage des sentinel au cellules bordantes
  //b->sentinelB1=init_B1(b,N);
  //b->sentinelB2=init_B2(b,N);
  //b->sentinelW1=init_W1(b,N);
  //b->sentinelW2=init_W2(b,N);
    
 //Chainage des cellules du palteau
  for(int i=0;i<b->size;i++){
      
  //Case bordure supérieur
    if(0<=(b->tab[i]->index) && (b->tab[i]->index)<N){
      b->tab[i]->neighboors[3]=b->sentinelB1;
      b->tab[i]->neighboors[2]=b->sentinelB1;
    }
    else{
      b->tab[i]->neighboors[3]=b->tab[i-N+1];
      b->tab[i]->neighboors[2]=b->tab[i-N];
    }
      
  //Case bordure droite
    if( ((b->tab[i]->index) % N) == N-1)
      b->tab[i]->neighboors[0]=b->sentinelW2;
    else
      b->tab[i]->neighboors[0]=b->tab[i+1];
      
 //Case bordure inférieure
    if( ((b->size-N)>=b->tab[i]->index) && ((b->tab[i]->index)<b->size) ){
      b->tab[i]->neighboors[5]=b->sentinelB2;
      b->tab[i]->neighboors[4]=b->sentinelB2;
    }
    else{
      b->tab[i]->neighboors[5]=b->tab[i+N];
      b->tab[i]->neighboors[4]=b->tab[i+N-1];
    }
      
    if( ((b->tab[i]->index) % N) == 0)
      b->tab[i]->neighboors[1]=b->sentinelW1;
    else
      b->tab[i]->neighboors[1]=b->tab[i-1];
      
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

