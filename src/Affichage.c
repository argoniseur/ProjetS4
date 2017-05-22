#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Affichage.h"
#define N 11

void print_board(Board b){
	system("clear");
	printf("Liste des commandes:\n");
	printf("-1: Quitter et sauvegarder\n");
	printf("-2: Quitter sans sauvegarder\n");
	printf("Entrer le chiffre dans 'Numéro de ligne' et valider\n");
	printf("\n");
	for (int i=0;i<N;i++){
		if(i==0)
			printf("W ");
		else
			printf("W ");
	}
	printf("W/B\n");

	for (int i=0;i<N;i++){
		for (int j=0;j<i+1;j++){
			printf(" ");
		}
		printf("B ");

		for (int j=0;j<N;j++){
			if (b->tab[(i*N)+j]->value == 1)
				printf("o ");
			else if (b->tab[(i*N)+j]->value == 2)
				printf("* ");
			else
				printf(". ");
		}
		printf("B\n");
	}
	for (int j=0;j<N+1;j++){
		printf(" ");
	}
	printf("B/W ");
	for (int i=0;i<N;i++){
		printf("W ");
	}
	printf("\n\n");
}

