#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct s_board *Board;

Board init_B1(Board b, int n);

Board init_B2(Board b, int n);

Board init_W1(Board b, int n);

Board init_W2(Board b, int n);

bool cell_on_edges(Board b, Cell cell);

bool surrounded(Board b, Cell cell);
 
Board create_board();

void board_delete(Board b);

int get_cell_value(Board b, int index);

Cell get_cell(Board b, int index);

Board insert_cell_value(SkipList d, int index, int value);
