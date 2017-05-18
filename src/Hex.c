#include "Plateau.h"
#include "Affichage.h"
#include "menu.h"

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

int main(int argc, char ** argv){
  	int nbTurn;  
  	char game;
  	Player p1; Player p2;
	game = newGame();
	if(game == 1){
		viderBuffer();
    	p1 = init_players(1);
    	p2 = init_players(2);
	}
	else if(game == 2){
		printf("Pas encore dev");
	}
	else{
		return 0;
	}
    
	Board hexBoard = create_board();
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
  	else{
  		historical(p2,p1);
  	}

  	free(p1);
  	free(p2);
  	board_delete(hexBoard);
    return 0;
}