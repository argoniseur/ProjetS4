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
    
    //Création de la sentinelle pour les bords gauche et droite
    b->sentinelW1 = create_sentinel(-2);
    b->sentinelW2 = create_sentinel(-3);

    //Création de la sentinelle pour les bords supérieurs et inférieurs
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

/* Insère la valeur passée en paramètre dans la cellule d'index "index" */
Board insert_cell_value(Board b, int index, int value){
    b->tab[index]->value = value;
    return b;
}
/* Vérifie la validité des coordonnées */
bool check_coord(int a, int c){
    if(a<1 || a>N)
        return false;
    if(c<1 || c>N)
        return false;

    return true;
}

bool check_cell(Board b, int a, int c){
    if(a>0 && a<N && c>0 && c<N)
        if(b->tab[N*(a-1)+(c-1)]->value != 0)
            return false;

    return true;
}


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

bool tested_cell(Cell tested[], Cell tst, int cpt_tested){
    for(int i=0;i<cpt_tested;i++){
        //printf("tested: value_c=%d, index_c=%d\n",tested[i]->value, tested[i]->index);
        if(tested[i] == tst)
            return true;
    }
    return false;
}

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

