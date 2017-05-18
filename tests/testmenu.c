/*Test menu */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
typedef struct s_player Player;

int main(){
	int cptErr=0;
	Player pa,pb;
	
	init_players(&pa,&pb);
	
	if (pa->value != 1) cptErr++;
	if (pb->value != 2) cptErr++;
	if ( pa->dernierCoupJouer != -1 ) cptErr++;
	if ( pb->dernierCoupJouer != -1 ) cptErr++;
	if ( pa->nbCoups != 0 ) cptErr++;
	if ( pb->nbCoups != 0 ) cptErr++;	
	if ( cptErr != 0 ) printf("[ERREUR] init_players()\n");
	else printf("[OK] Initialisation des jouers.\n");
	
	return(0);
}
