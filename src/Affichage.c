#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Affichage.h"
#define N 11

void print_board(Board b){

	for (int i=0;i<N;i++){
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
				printf("x ");
			else
				printf("  ");
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
	printf("\n");
}