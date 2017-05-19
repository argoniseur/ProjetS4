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
	Historique histo[N*N];
    init_histo(histo);
	/*
	for (int i=0;i<10;i++)
		hexBoard->tab[N*i]->value = 1;
	*/
	print_board(hexBoard);
	int winner = 0;
	nbTurn = 0;
	Player p = p1;
    int quitter = 0;

	while(!winner && quitter == 0){

    	hexBoard = get_and_insert_coord(hexBoard,&p,histo,nbTurn,&quitter);
    	print_board(hexBoard);
    	
    	winner = search_winner(hexBoard);
    	if(p == p1)
      		p = p2;
    	else
			p = p1;
    
    	nbTurn++;
  	}
  	if(winner == 1){
  		historical(p1,p2);
        printf("%s remporte la partie ! Félicitations !", p1->nom);
  	}
  	else if(winner == 2){
  		historical(p2,p1);
        printf("%s remporte la partie ! Félicitations !", p2->nom);
  	}

    if(quitter == 1)
        save_game(hexBoard, p1, p2, histo, nbTurn);

  	free(p1);
  	free(p2);
    for(int i = 0;i<N*N;i++)
        free(histo[i]);
  	board_delete(hexBoard);
    return 0;
}
