#include "Plateau.h"
#define N 9

typedef struct s_element{
  int couleur;
}*Element;

struct s_plateau{
  Element tab[N*N];
};

Plateau creer_plateau(){
  Plateau p = (Plateau)malloc(sizeof(struct s_plateau));
  for (int i = 0;i < N*N;i++){
    p->tab[i]->couleur = 0;
  }
  return p;
}
