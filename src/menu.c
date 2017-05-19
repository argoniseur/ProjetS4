//Module menu
//Par: Gaffiero Allison, Courdy-Bahsoun Clémence, de Fercluc Louis
//Dernière modification: 12.05.2017
//Objectif: l'interaction avec les joueurs
//	    Permet le stockage des données concernant les joueurs et leurs modifications
//Dépendances: Module plateau

#include "menu.h"
#define N 11
/**
 * Initialise les informations des deux joueurs 
 * Rôle des paramètres: pa et pb sont des paramètres d'entrées/sorties qui sont initialisés avec les informations propres aux deux joueurs
 */
Player init_players(int num){
	Player pa = (Player)malloc(sizeof(struct s_player));
	printf("saisissez le nom du joueur\n");
	fgets((pa)->nom,22,stdin);

	/* Problème valgrind ici. Il n'aime pas le changement de saut de ligne en caractère vide car il considère que le tableau n'est pas initialisé */
	for (int i = 0;i<21;i++)
		if(pa->nom[i] == '\n')
			pa->nom[i] = '\0';

	(pa)->value = num;
	(pa)->dernierCoupJouer = -1;
	(pa)->nbCoups = 0;
	return pa;
}

/**
 * Saisie des coordonnees d'entrer
 * Paramètres: b = plateau en entrée modifié par l'insertion d'un pion de la valeur associé à p qui est alors retourné en sorti
 * 		p = Information du joueur dont c'est le tour qui sont affichés puis mis à jour 
 */
Board get_and_insert_coord(Board b, Player *p, Historique histo[], int nbTurn, int *quitter){
		int lig, col;
		(*p)->nbCoups++;
		printf("%s, coup numéro %d\n", (*p)->nom, (*p)->nbCoups);
  
		if((*p)->dernierCoupJouer != -1)
				printf("Votre dernier coup joué: [%d,%d]\n", (((*p)->dernierCoupJouer)/N)+1, (((*p)->dernierCoupJouer)%N)+1);
  
		bool tst;
		do{
			tst = false;
			printf("Saisissez les coordonnées de votre nouveau coup au format [ligne,colonne]\n");
			printf("Numéro de ligne: "); scanf("%d", &lig);
			if(lig == -1){
				*quitter = 1;
				return b;
			}
			if(lig == -2){
				*quitter = 2;
				return b;
			}
			if(lig == -3)
				printf("Att gros");

			printf("Numéro de colonne: "); scanf("%d", &col);

			if (!check_coord(lig, col)){
				printf("Coordonnées invalide\n");
				tst = true;
			}
			if (!check_cell(b,lig,col)){
				printf("Case occupée\n");
				tst = true;
			}
		}while(tst);
		
		histo[nbTurn]->player_c = (*p)->value;
		histo[nbTurn]->line = lig;
		histo[nbTurn]->column = col;

		(*p)->dernierCoupJouer = (N*(lig-1))+(col-1);
		b = insert_cell_value(b, (*p)->dernierCoupJouer, (*p)->value);

		return b;
}

/**
 * affichage du menu de jeu
 * Aucun parametres d'entrés
 * Retourne un char faisant office de booléen pour savoir si une nouvelle partie doit être lancé O-> OUI / N-> NON
 */
int newGame(){
	int choose;
	printf("------- Menu Hex -------\n");
	printf("1 - Nouvelle partie\n");
	printf("2 - Charger partie\n");
	printf("3 - Quitter\n");
	scanf("%d", &choose);

	return choose;
}

void historical(Player pa, Player pb){
	FILE* fic = NULL;
  
	fic = fopen("./saves/historique","a");
  
		if(fic == NULL)
			fprintf(stderr,"Impossible d'ouvrir l'historique\n");
		else{
			fprintf(fic,"%s gagne en %d coups contre %s\n",pa->nom,pa->nbCoups,pb->nom);
			fclose(fic);
		}
}

void init_histo(Historique histo[]){
	for(int i = 0;i<N*N;i++){
		histo[i] = (Historique)malloc(sizeof(struct s_historique));
	}
}

void save_game(Board b, Player aa, Player bb, Historique histo[], int nbTurn){
	FILE* fichier = NULL;
	char nomfic[55], tmp[11];
	char chemin[66];
	time_t sec = time(NULL);
	strcat(nomfic,aa->nom);
	strcat(nomfic,"-");
	strcat(nomfic,bb->nom);
	strcat(nomfic,"-");
	sprintf(tmp,"%ld",sec);
	strcat(nomfic,tmp);
	if(nomfic[0] == '\n')
		for(int i=0;i<67;i++)
			nomfic[i] = nomfic[i+1];

	sprintf(chemin,"./saves/%s.txt", nomfic);

	fichier = fopen(chemin,"a");

	if(fichier == NULL)
		fprintf(stderr,"Impossible d'ouvrir le fichier de sauvegarde\n");
	else{
		fprintf(fichier,"\\hex\n\\dim %d\n\\board\n", N);
		for (int i = 0;i<N*N;i++){
			if(b->tab[i]->value == 0)
				fprintf(fichier,". ");
			if(b->tab[i]->value == 1)
				fprintf(fichier,"o ");
			if(b->tab[i]->value == 2)
				fprintf(fichier,"* ");

			if((i+1)%N == 0)
				fprintf(fichier,"\n");
		}
		fprintf(fichier,"\\endboard\n");
		fprintf(fichier,"\\game\n");
		for(int i = 0;i<nbTurn;i++){
			if(histo[i]->player_c == 1)
				fprintf(fichier,"\\play o %d %d\n", histo[i]->line, histo[i]->column);
			else if(histo[i]->player_c == 2)
				fprintf(fichier,"\\play * %d %d\n", histo[i]->line, histo[i]->column);
		}
		fprintf(fichier,"\\endgame\n");
		fprintf(fichier,"\\endhex\n");
		fclose(fichier);
	}
}
