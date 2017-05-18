#ifndef __PLATEAU__
#define __PLATEAU__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <malloc.h>
#define N 11

typedef struct s_cell{
	int value;
	int index;
	struct s_cell **neighboors;
}*Cell;

typedef struct s_board{
	int size;
	Cell tab[N*N];
	Cell sentinelB1;
	Cell sentinelB2;
	Cell sentinelW1;
	Cell sentinelW2;
}*Board;

/* Initialiser les 4 sentinelles du plateau */

Board init_B1(Board b);

Board init_B2(Board b);

Board init_W1(Board b);

Board init_W2(Board b);

/* Retourne true si une cellule est située sur le bord du plateau */
bool cell_on_edges(Board b, Cell cell);

/* Retourne true si une cellule n'a aucune cases libre */
bool surrounded(Board b, Cell cell);

/* Initialise le plateau */
Board create_board();

Board insert_cell_value(Board b, int index, int value);

bool check_coord(int a, int c);

bool check_cell(Board b, int a, int c);

int search_winner(Board b);

/* Supprime le plateau et libère la mémoire */
void board_delete(Board b);

/* Retourne la valeur de la cellule */
int get_cell_value(Board b, int index);

/* Retourne la cellule correspondant à l'index passé en paramètre */
Cell get_cell(Board b, int index);

/* Insère la valeur passée en paramètre dans la cellule d'index "index" */
Board insert_cell_value(Board d, int index, int value);

#endif