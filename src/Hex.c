#include "Plateau.h"
#include "Affichage.h"
#include "menu.h"

int main(int argc, char ** argv){
    Board hexBoard = create_board();
    print_board(hexBoard);
    Player j1 = NULL, j2 = NULL;
    initJoueurs(&j1,&j2);
    return 0;
}
