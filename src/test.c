#include "Plateau.h"
#include "menu.h"
#include "Affichage.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FINI 0

int main(int argc, char ** argv){
        Board d;
        int cptErr=0;
        int cptTest=0;

                        /* Plateau */
        printf("\n-- Plateau --\n");
        cptTest++;//création du plateau
        if (!(d=create_board())){
                printf("[ERREUR] Creation du plateau - create_board()\n");
                cptErr++;
        }else{
                printf("[OK] Creation du plateau.\n");
        
                /*
                insert_cell_value(d,3,1);
                cptTest++;//contenu de la case d'index 3 du tableau
                if (get_cell_value(d,3) != 1){
                        printf("[ERREUR] Contenu de la case - insert_cell_value ou get_cell_value()\n");
                        cptErr++;
                }else{
                        printf("[OK] Contenu de la case.\n");
                }
                
                cptTest++;//Insertion d'une valeur dans une cellule non vide
                insert_cell_value(d,3,2);
                if (get_cell_value(d,3) != 1 || get_cell_value(d,3) == 2){
                        printf("[ERREUR] Insertion d'une valeur dans une case non vide - insert_cell_value()\n");
                        cptErr++;
                }else{
                        printf("[OK] Insertion d'une valeur dans une case non vide.\n");
                }*/ //A (peut-être) SUPPRIMER
                
                
                        /* Menu */
                printf("\n-- Menu -- \n");
                Player pa;
                Player pb;
                 
                printf("Initialisation des joueurs : \n");
                init_players(&pa,&pb);//Initialisation des joueurs
                
                
                get_and_insert_coord(d,&pa);//Ajouter et insérer valeur dans plateau
                
                        /* Affichage */
                printf("\n-- Affichage --\n");
                print_board(d);
                
        }
        
        board_delete(d); //Suppression du plateau
        
        
        
        //Affichage des résultats des tests
        printf("\nIl y a %d erreurs sur %d tests.\n\n",cptErr,cptTest);
        
        return (TEST_FINI);
}

