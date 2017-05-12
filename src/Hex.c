#include "Plateau.h"
#include "Affichage.h"
#include "menu.h"

int main(int argc, char ** argv){
  int nbTurn;  
  char game;
    
  game = newGame();
  if(game=='O'){
     Player p1; Player p2;
     init_players(&p1,&p2);  
  }
  else
    return 0;
    
  Board hexBoard=create_board(();
  print_board(hexBoard);

  nbTurn=0;
  Player p=p1;
  while(nbTurn<N*N){
    hexBoard = get_and_insert_coord(hexBoard,&p);
    print_board(hexBoard);
    
    if(p==p1)
      p=p2;
    else
      p=p1;
    
    nbTurn++;
  }
  
    return 0;
}