#include "Plateau.h"
#include "Affichage.h"
#include "menu.h"

int main(int argc, char ** argv){
  	int nbTurn;  
  	char game;
  	Player p1; Player p2;
  	Board hexBoard = create_board();
	game = newGame();
	if(game == 1){
    	p1 = init_players(1);
    	p2 = init_players(2);  
	}
	else if(game == 2){
		printf("Pas encore dev");
	}
	else
    	return 0;
    
	
	for(int i=0;i<10;i++){
		hexBoard->tab[i*N]->value = 1;
		hexBoard->tab[i*N+1]->value = 2;
	}
	print_board(hexBoard);

	int winner;
	nbTurn=0;
	Player p=p1;

	while(nbTurn<N*N && !winner){
    	hexBoard = get_and_insert_coord(hexBoard,&p);
    	print_board(hexBoard);
    	
    	winner = search_winner(hexBoard);
    	if(p==p1)
      		p=p2;
    	else
      	p=p1;
    
    	nbTurn++;
  	}
  	if(winner == 1){
  		historical(p1,p2);
  	}
  	else if(winner == 2){
  		historical(p2,p1);
  	}

  	free(p1);
  	free(p2);
  	board_delete(hexBoard);
    return 0;
}