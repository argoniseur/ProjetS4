#include "Plateau.h"
#include "Affichage.h"
#include "menu.h"

int main(int argc, char ** argv){
  	int nbTurn;  
  	char game;
  	Player p1; Player p2;
  
	game = newGame();
	if(game == 1){
    	init_players(&p1,&p2);  
	}
	else if(game == 2){
		printf("Pas encore dev");
	}
	else
    	return 0;
    
	Board hexBoard = create_board();
	print_board(hexBoard);

	for(int i=0;i<10;i++){
		hexBoard->tab[i*N]->value = 1;
	}
	hexBoard->tab[34]->value = 1;
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
  	if(winner == 1)
  		printf("Joueur 1 gagne\n");
  	else if(winner == 2)
  		printf("Joueur 2 gagne\n");
    return 0;
}