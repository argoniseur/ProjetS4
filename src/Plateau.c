#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Plateau.h"
#define N 9

struct s_cell{
	int value;
	int index;
	struct s_cell *neighboors[6];
};

typedef struct s_sentinel{
    Cell *edges;
    int value;
}*Sentinel;

struct s_board{
	int size;
	Sentinel sentinelB1;
	Sentinel sentinelB2;
	Sentinel sentinelW1;
	Sentinel sentinelW2;
};

Board init_B1(Board b, int n){
    // assert
    int val;
    for(int i=0;i<N;i++){
        val = board_ith(b, i);
        b->sentinelB1->edges[i] = val;
    }
    return b;

}
/*
Board create_board(){
    Board b = (Board)malloc(sizeof(struct s_board));
    return b;
}*/
