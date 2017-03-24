#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct s_board *Board;
Board create_board(int N);

//void ajouter_pion(Plateau p, int pion);

bool case_vide(Plateau p, int x);
