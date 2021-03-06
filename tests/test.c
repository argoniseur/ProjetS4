#include "../src/Plateau.c"
#include "../src/menu.c"
#include "../src/Affichage.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N 11

#define E 0
#define SE 1
#define SO 2
#define O 3
#define NO 4
#define NE 5

#define white_p 1
#define black_p 2

int main(int argc, char ** argv){
	Board d;
	Board testcolonne;
	Board testligne;
	Board b;
	Board bwhitewinner;
	Board bblackwinner;
	int cptErr=0;
	int cptTest=0;
	int testint;
	Historique histo[N*N];
	//Plateau
	bool chainE=true;
	bool chainSE=true;
	bool chainSO=true;
	bool chainO=true;
	bool chainNO=true;
	bool chainNE=true;
	bool continu=true;
	//Menu
	Player pa,pb;
	int cptErrMenu=0;

		/* Plateau */
	printf("\n-- Plateau --\n");
	cptTest++; //Création du plateau
	if (!(d=create_board())){
		printf("[ERREUR] Creation du plateau - create_board()\n");
		cptErr++;
	}else{
		testcolonne=create_board();
		testligne=create_board();
		b = create_board();
		bwhitewinner = create_board();
		bblackwinner = create_board();
		cptTest++; //initialisation taille du plateau
		if (d->size != N*N){
			cptErr++;
			printf("[ERREUR] Taille du plateau - create_board()\n");
		}else{
			cptTest++; //valeurs cellules initialisées à 0
			testint=0;
			while ( testint < d->size && d->tab[testint]->value == 0 ) testint++;
			if ( testint != d->size ){
				printf("[ERREUR] Valeur != 0 - create_board() - create_cell()\n");
				cptErr++;
			}else printf("[OK] Valeur cellules initialisées à 0.\n");
			
			//Vérification initialisation des bords
			cptTest=cptTest+4;
			//Bord gauche - init_B1()
			testint=0;
			while ( testint < N && continu ){
				if (!( d->sentinelB1->neighboors[testint] == d->tab[testint*N] 
				|| d->tab[testint*N]->neighboors[SO] == d->sentinelB1 
				|| d->tab[testint*N]->neighboors[O] == d->sentinelB1 )){
					printf("[ERREUR] Bord gauche - init_B1()\n");
					cptErr++;
					continu=false;
				}
				testint++;
			}
			//Bord droit - init_B2()
			testint=0;
			continu=true;
			while ( testint < N && continu ){
				if (!(d->sentinelB2->neighboors[testint] == d->tab[(testint*N)+(N-1)] 
				|| d->tab[(testint*N)+(N-1)]->neighboors[E] == d->sentinelB2 
				|| d->tab[(testint*N)+(N-1)]->neighboors[NE] == d->sentinelB2 )){
					printf("[ERREUR] Bord droit - init_B2()\n");
					cptErr++;
					continu=false;
				}
				testint++;
			}
			//Bord haut - init_W1()
			testint=0;
			continu=true;
			while ( testint < N && continu ){
				if (!( d->sentinelW1->neighboors[testint] == d->tab[testint] 
				|| d->tab[testint]->neighboors[NE] == d->sentinelW1 
				|| d->tab[testint]->neighboors[NO] == d->sentinelW1 )){
					printf("[ERREUR] Bord haut - init_W1()\n");
					cptErr++;
					continu=false;
				}
				testint++;
			}
			//Bord bas - init_W2()
			testint=0;
			continu=true;
			while ( testint < N && continu ){
				if (!( d->sentinelB1->neighboors[testint] == d->tab[(N*(N-1))+testint] 
				|| d->tab[(N*(N-1))+testint]->neighboors[SE] == d->sentinelW2 
				||d ->tab[(N*(N-1))+testint]->neighboors[SO] == d->sentinelW2 )) {
					printf("[ERREUR] Bord bas - init_W2()\n");
					cptErr++;
					continu=false;
				}
				testint++;
			}
			printf("[OK] Initialisation des bords.\n");
				
			cptTest++;//vérification des chainages
			testint=0;
			while ( testint < d->size && chainE && chainSE && chainSO && chainO && chainNO && chainNE ){
				//est
				if ( (testint+1)%N != 0 ) chainE=(d->tab[testint]->neighboors[E] == d->tab[testint+1]);
            	//sud est
            	if ( testint+N < N*N ) chainSE=(d->tab[testint]->neighboors[SE] == d->tab[testint+N]);
				//chainage sud ouest
        		if( (testint+N)%N != 0 && testint < N*N-N ) chainSO=(d->tab[testint]->neighboors[SO] == d->tab[testint+N-1]);
        		//chainage ouest
       			if ( testint%N != 0 ) chainO=(d->tab[testint]->neighboors[O] == d->tab[testint-1]);           		
        		//chainage nord ouest
       			if ( testint >= N ) chainNO=(d->tab[testint]->neighboors[NO] == d->tab[testint-N]);
        		//chainage nord est
        		if ( (testint-N+1)%N > 0 ) chainNE=(d->tab[testint]->neighboors[NE] == d->tab[testint-N+1]);				
				testint++;
			}
			if ( testint != d->size ){
				printf("[ERREUR] Chainage - create_board()\n");
				cptErr++;
			}else printf("[OK] Chainage.\n");
			
			//vérification des sentinelles
			cptTest=cptTest+4;
			if ( d->sentinelB1->index != -1 && d->sentinelB1->value != -4 ){ 
				printf("[ERREUR] Sentinelle B1 - create_board()\n");
				cptErr++;
			}
			if ( d->sentinelB2->index != -1 && d->sentinelB2->value != -6 ){
				printf("[ERREUR] Sentinelle B2 - create_board()\n");
				cptErr++;
			}
			if ( d->sentinelW1->index != -1 && d->sentinelW1->value != -2  ){
				printf("[ERREUR] Sentinelle W1 - create_board()\n");
				cptErr++;
			}
			if ( d->sentinelW2->index != -1 && d->sentinelW2->value != -3 ){
				printf("[ERREUR] Sentinelle W2 - create_board()\n");
				cptErr++;
			}
			printf("[OK] Vérification des valeurs des sentinelles.\n");
			
			printf("[OK] Creation du plateau.\n");	
			
			//Insertion d'une valeur dans le plateau
			insert_cell_value(d,3,1);
			cptTest++;
			if (d->tab[3]->value != 1){
			printf("[ERREUR] Contenu de la case - insert_cell_value ou get_cell_value()\n");
			cptErr++;
			}else printf("[OK] Contenu de la case.\n");
			
			//Vérification de la validité de coordonnées - check_coord()
			cptTest=cptTest+5;
			//coordonnées, ligne < à la taille du plateau
			if ( check_coord(-1,2) ){
				printf("[ERREUR] Validité coordonnées ligne < - check_coord()\n");
				cptErr++;
			}else printf("[OK] Validité coordonnées ligne <\n");
				//coordonnées, colonne < à la taille du plateau
			if ( check_coord(2,-1) ) {
				printf("[ERREUR] Validité coordonnées colonne < - check_coord()\n");
				cptErr++;
			}else printf("[OK] Validité coordonnées colonne <\n");
			//coordonnées, ligne et colonne = dans le plateau
			if ( !(check_coord(2,2)) ) {
				printf("[ERREUR] Validité coordonnées = - check_coord()\n");
				cptErr++;
			}else printf("[OK] Validité coordonnées =\n");
			//coordonnées, ligne > à la taille du plateau
			if ( check_coord(N+2,2) ){
				printf("[ERREUR] Validité coordonnées ligne > - check_coord()\n");
				cptErr++;
			}else printf("[OK] Validité coordonnées ligne >\n");
			//coordonnées, colonne > à la taille du plateau
			if ( check_coord(2,N+2) ){
				printf("[ERREUR] Validité coordonnées colonne > - check_coord()\n");
				cptErr++;
			}else printf("[OK] Validité coordonnées colonne >\n");
			printf("[OK] Vérification validité coordonnées.\n");
			
			//Vérification cellule occupée	- check_cell()
			cptTest++;
			check_coord(5,2);
			insert_cell_value(d,(N*(5-1))+(2-1),2);
			if ( check_cell(d,5,2) ){
				printf("[ERREUR] Cellule occupée - check_cell()\n");
				cptErr++;
			}else printf("[OK] Cellule occupée.\n");
			cptTest++;
			if ( !(check_cell(d,5,3)) ){
				printf("[ERREUR] Cellule vide - check_cell()\n");
				cptErr++;
			}else printf("[OK] Cellule vide.\n");
			
			//Recherche d'un gagnant - search_winner()
			int winner=0;
			int joueurTestGagnant=1;
			int cptTour=0;
			//Mise en place d'un plateau de jeu où il reste une seule case à remplir
			cptTest++;
			for ( testint=0 ; testint < ((b->size)-2) && !winner ; testint++ ){
				if (cptTour == 2){
					if (joueurTestGagnant == 1) joueurTestGagnant=2;
					else joueurTestGagnant=1;
					cptTour=0;
				}
				insert_cell_value(b,testint,joueurTestGagnant);
				winner=search_winner(b);
				cptTour++;
			}
			if ( winner != 0 ){
				printf("[ERREUR] Le plateau à un gagnant.\n");
				cptErr++;
			}else{
				cptTest++;
				insert_cell_value(b,(b->size),2);
				insert_cell_value(b,(b->size)-1,2);
				winner=search_winner(b);
				if ( winner != 0 ) { 
					printf("[ERREUR] Le plateau à un gagnant.\n");
					cptErr++;
				}else{ //il reste une seule case vide, d'indice (b->size)-2
					bwhitewinner=b;
					bblackwinner=b;

					//cas où le gagnant est le joueur white
					cptTest++;
					insert_cell_value(bwhitewinner,(b->size)-2,1);
					winner=search_winner(bwhitewinner);
					if ( winner != 1 ){
						printf("[ERREUR] Recherche d'un gagnant 1/2 - search_winner()\n");
						cptErr++;
					}else printf("[OK] Recherche d'un gagnant 1/2.\n");
					//cas où le gagnant est le joueur black
					cptTest++;
					insert_cell_value(bblackwinner,(b->size)-2,2);
					winner=search_winner(bblackwinner);
					if ( winner != 2 ){
						printf("[ERREUR] Recherche d'un gagnant 2/2 - search_winner()\n");
						cptErr++;
					}else printf("[OK] Recherche d'un gagnant 2/2.\n");
				}
			}
			cptTest++;
			winner=0;
			for ( testint=0 ; testint < N-1 ; testint++ ) {
				insert_cell_value(testligne,testint,1);
				winner=search_winner(testligne);
			}
			if ( winner != 0 ){
					printf("[ERREUR] Le plateau à un gagnant.\n");
					cptErr++;
			}else{
				cptTest++;
				insert_cell_value(testligne,N-1,1);
				winner=search_winner(testligne);
				if ( winner == 1 ){ 
					printf("[ERREUR] Recherche d'un gagnant ligne 1/2 - search_winner().\n");
					cptErr++;
				}else{
					printf("[OK] Recherche d'un gagnant ligne 1/2.\n");
				}
				cptTest++;
				winner=0;
				insert_cell_value(testligne,0,0);
				for( testint=10 ; testint < ((N*N)-11) ; testint=testint+11 ){
					insert_cell_value(testligne,testint,1);
					winner=search_winner(testligne);
				}
				if ( winner == 1 ){ 
					printf("[ERREUR] Le plateau à un gagnant\n");
					cptErr++;
				}else{
					insert_cell_value(testligne,N*N-1,1);
					winner=search_winner(testligne);
					if ( winner != 1 ){ 
						printf("[ERREUR] Recherche d'un gagnant ligne 2/2 - search_winner().\n");
						cptErr++;
					}else{
						printf("[OK] Recherche d'un gagnant ligne 2/2.\n");
					}
				}
			}
			cptTest++;
			winner=0;
			for ( testint=0 ; testint < N-1 ; testint++ ) {
				insert_cell_value(testcolonne,testint,2);
				winner=search_winner(testcolonne);
			}
			if ( winner != 0 ){
					printf("[ERREUR] Le plateau à un gagnant.\n");
					cptErr++;
			}else{
				cptTest++;
				insert_cell_value(testcolonne,N-1,2);
				winner=search_winner(testcolonne);
				if ( winner != 2 ){ 
					printf("[ERREUR] Recherche d'un gagnant colonne 1/2 - search_winner().\n");
					cptErr++;
				}else{
					printf("[OK] Recherche d'un gagnant colonne 1/2.\n");
				}
				cptTest++;
				winner=0;
				insert_cell_value(testcolonne,0,0);
				for( testint=10 ; testint < ((N*N)-11) ; testint=testint+11 ){
					insert_cell_value(testcolonne,testint,2);
					winner=search_winner(testcolonne);
				}
				if ( winner == 2 ){ 
					printf("[ERREUR] Le plateau à un gagnant\n");
					cptErr++;
				}else{
					insert_cell_value(testcolonne,N*N-1,2);
					winner=search_winner(testcolonne);
					if ( winner == 2 ){ 
						printf("[ERREUR] Recherche d'un gagnant colonne 2/2 - search_winner().\n");
						cptErr++;
					}else{
						printf("[OK] Recherche d'un gagnant colonne 2/2.\n");
					}
				}
			}
			
                /* Menu */
            printf("\n-- Menu -- \n");
				
			//Initialise les informations d'un joueur - init_players()
            cptTest=cptTest+6;
			pa=init_players(1);
			pb=init_players(2);
			if (pa->value != 1) cptErrMenu++;
			if (pb->value != 2) cptErrMenu++;
			if ( pa->dernierCoupJouer != -1 ) cptErrMenu++;
			if ( pb->dernierCoupJouer != -1 ) cptErrMenu++;
			if ( pa->nbCoups != 0 ) cptErrMenu++;
			if ( pb->nbCoups != 0 ) cptErrMenu++;	
			if ( cptErrMenu != 0 ) printf("[ERREUR] init_players() - %d erreurs sur 6 tests.\n",cptErrMenu);
			else printf("[OK] Initialisation des joueurs - 6 tests effectués.\n");
               
            cptErr=cptErr+cptErrMenu;
			
			//Initialisation de l'historique
			init_histo(histo);
			printf("Historique initialisé.\n");
			
			//Saisie des coordonnees d'entrer - get_and_insert_coord()
			printf("     Coordonnées valides : Faites [1,1].\n");
			d=get_and_insert_coord(d,&pa,histo,0,&testint);
			printf("     Coordonnées invalides, les deux : Faites [-3,-2]. Puis [3,2].\n");
			d=get_and_insert_coord(d,&pa,histo,1,&testint);
			printf("     Coordonnées invalides, ligne : Faites [414,3]. Puis [2,3].\n");
			d=get_and_insert_coord(d,&pa,histo,2,&testint);
			printf("     Coordonnées invalides, colonne : Faites [3,414]. Puis [3,3].\n");
			d=get_and_insert_coord(d,&pa,histo,3,&testint);
			printf("     Case occupée : Essayez [3,3]. Puis [3,4].\n");
			d=get_and_insert_coord(d,&pa,histo,4,&testint);
			
			//Affichage du menu de jeu - newGame()
			cptTest++;
			testint=newGame();
			if ( testint == 1 || testint == 2 || testint == 3 ){
				printf("[OK] Menu du jeu.\n");
			}else{
				printf("[ERREUR] Menu du jeu - newGame()\n");
				cptErr++;
			}
			
			/* Affichage */
            printf("\n-- Affichage --\n");
            print_board(d);
		}
		
		//Suppression des plateaux
		board_delete(d);
		board_delete(b);
		board_delete(testcolonne);
		board_delete(testligne);
        
    }
        
    //Affichage des résultats des tests
    printf("\nIl y a %d erreurs sur %d tests.\n\n",cptErr,cptTest);
	return (0);
}