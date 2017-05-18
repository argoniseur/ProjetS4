/*Test plateau */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "Plateau.h"

#define N 11

#define E 0
#define SE 1
#define SO 2
#define O 3
#define NO 4
#define NE 5

int main(){
	int cptErr=0;
	int cptTest=0;
	int i;
	
	bool chainE=true;
	bool chainSE=true;
	bool chainSO=true;
	bool chainO=true;
	bool chainNO=true;
	bool chainNE=true;
	bool continu=true;
	
	Board btest;
	
	cptTest++; //Création du plateau
	if (!(btest=create_board())){
		printf("[ERREUR] Creation du plateau - create_board()\n");
		cptErr++;
	}else{
		cptTest++; //initialisation taille du plateau
		if (btest->size != N*N){
			cptErr++;
			printf("[ERREUR] Taille du plateau - create_board()\n");
		}else{
			printf("[OK] Taille du plateau.\n");
			cptTest++; //valeurs cellules initialisées à 0
			i=0;
			while ( i < btest->size && btest->tab[i]->value == 0 ){			
				i++;
			}
			if ( i != btest->size ){
				printf("[ERREUR] Valeur != 0 - create_board()\n");
				cptErr++;
			}else printf("[OK] Valeur cellules initialisées à 0.\n");
			
			//Vérification initialisation des bords
			cptTest=cptTest+4;
			//Bord gauche
			i=0;
			while ( i < N && continu ){
				if (!( btest->sentinelB1->neighboors[i] == btest->tab[i*N] || btest->tab[i*N]->neighboors[SO] == btest->sentinelB1 || btest->tab[i*N]->neighboors[O] == btest->sentinelB1 )){
					printf("[ERREUR] Bord gauche - init_B1()\n");
					cptErr++;
					continu=false;
				}
				i++;
			}
			//Bord droit
			i=0;
			continu=true;
			while ( i < N && continu ){
				if (!(btest->sentinelB2->neighboors[i] == btest->tab[(i*N)+(N-1)] || btest->tab[(i*N)+(N-1)]->neighboors[E] == btest->sentinelB2 || btest->tab[(i*N)+(N-1)]->neighboors[NE] == btest->sentinelB2 )){
					printf("[ERREUR] Bord droit - init_B2()\n");
					cptErr++;
					continu=false;
				}
				i++;
			}
			//Bord haut
			i=0;
			continu=true;
			while ( i < N && continu ){
				if (!( btest->sentinelW1->neighboors[i] == btest->tab[i] || btest->tab[i]->neighboors[NE] == btest->sentinelW1 || btest->tab[i]->neighboors[NO] == btest->sentinelW1 )){
					printf("[ERREUR] Bord haut - init_W1()\n");
					cptErr++;
					continu=false;
				}
				i++;
			}
			//Bord bas
			i=0;
			continu=true;
			while ( i < N && continu ){
				if (!( btest->sentinelB1->neighboors[i] == btest->tab[(N*(N-1))+i] || btest->tab[(N*(N-1))+i]->neighboors[SE] == btest->sentinelW2 ||btest ->tab[(N*(N-1))+i]->neighboors[SO] == btest->sentinelW2 )) {
					printf("[ERREUR] Bord bas - init_W2()\n");
					cptErr++;
					continu=false;
				}
				i++;
			}
			printf("[OK] Initialisation des bords.\n");
				
			cptTest++;//vérification des chainages
			i=0;
			while ( i < btest->size && chainE && chainSE && chainSO && chainO && chainNO && chainNE ){
				//est
				if((i+1)%N != 0) chainE=(btest->tab[i]->neighboors[E] == btest->tab[i+1]);
            	//sud est
            	if(i+N < N*N) chainSE=(btest->tab[i]->neighboors[SE] == btest->tab[i+N]);
				//chainage sud ouest
        		if(i+N-1 < N*N) chainSO=(btest->tab[i]->neighboors[SO] == btest->tab[i+N-1]);
        		//chainage ouest
       			if(i%N != 0) chainO=(btest->tab[i]->neighboors[O] == btest->tab[i-1]);           		
        		//chainage nord ouest
       			if(i-N > 0) chainNO=(btest->tab[i]->neighboors[NO] == btest->tab[i-N]);
        		//chainage nord est
        		if(i-N+1 > 0) chainNE=(btest->tab[i]->neighboors[NE] == btest->tab[i-N+1]);				
				i++;
			}
			if ( i != btest->size ){
				printf("[ERREUR] Chainage - create_board()\n");
				cptErr++;
			}else printf("[OK] Chainage.\n");
			
			
			//vérification des sentinelles
		
			/* /!\ AJOUTER VÉRIFICATION DE LA VALEUR AUSSI /!\ */
			
			cptTest=cptTest+4;
			if ( btest->sentinelB1->index != -1 ){ 
				printf("[ERREUR] Sentinelle B1 - create_board()\n");
				cptErr++;
			}
			if ( btest->sentinelB2->index != -1 ){
				printf("[ERREUR] Sentinelle B2 - create_board()\n");
				cptErr++;
			}
			if ( btest->sentinelW1->index != -1 ){
				printf("[ERREUR] Sentinelle W1 - create_board()\n");
				cptErr++;
			}
			if ( btest->sentinelW2->index != -1 ){
				printf("[ERREUR] Sentinelle W2 - create_board()\n");
				cptErr++;
			}
			printf("[OK] Vérification des valeurs des sentinelles.\n");
			
			printf("[OK] Creation du plateau.\n");	
		}
	}
	
	 //Insertion d'une valeur dans une cellule
	 insert_cell_value(btest,3,1);
	 cptTest++;
	 if (btest->tab[3]->value != 1){
	 	printf("[ERREUR] Contenu de la case - insert_cell_value ou get_cell_value()\n");
	 	cptErr++;
	 }else printf("[OK] Contenu de la case.\n");
                
                
	 //Vérification de la validité de coordonnées
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
	 	
	 //Vérification cellule occupée	
	 cptTest++;
	 check_coord(5,2);
	 insert_cell_value(btest,(N*(5-1))+(2-1),2);
	 if (!(check_cell(btest,5,2))){
	 	printf("[Erreur] Cellule occupée - check_cell()\n");
	 	cptErr++;
	 }else printf("[OK] Cellule occupée.\n");
	 
	 //Saisie des coordonnées d'entrée
	 
	 
	 
	 //Supression du plateau
	 board_delete(btest);
	 
	 
	//Affichage des résultats des tests
	printf("\nIl y a %d erreurs sur %d tests.\n\n",cptErr,cptTest);

	return (0);
}
