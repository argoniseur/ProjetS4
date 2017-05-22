//Module menu
//Par: Gaffiero Allison, Courdy-Bahsoun Clémence, de Fercluc Louis
//Dernière modification: 21.05.2017
//Objectif: l'interaction avec les joueurs
//	    Permet le stockage des données concernant les joueurs et leurs modifications
//Dépendances: Module plateau

#include "menu.h"
#define N 11
/**
 * Initialise les informations d'un joueur 
 * Paramètre : num = valeur du joueur
 * Retourne un joueur initialisé
 */
Player init_players(int num){
	Player pa = (Player)malloc(sizeof(struct s_player));
	printf("saisissez le nom du joueur\n");
	fgets((pa)->nom,22,stdin);

	/* Problème valgrind ici ; Il n'aime pas le changement de saut de ligne en caractère vide car il considère que le tableau n'est pas initialisé */
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
 * Paramètres: 	b = plateau en entrée modifié par l'insertion d'un pion de la valeur associé à p qui est alors retourné en sorti
 * 				p = informations du joueur dont c'est le tour qui sont affichés puis mises à jour
 *				histo = historique de la partie qui est mis à jour
 *				nbTurn = nombre de tour depuis le début de la partie
 *				quitter = entier changé si le joueur veut quitter la partie en cours
 * Retourne le plateau modifié
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
				printf("Att gros"); // Really man ?

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
 * Affichage du menu de jeu
 * Aucun parametres d'entrés
 * Retourne entier faisant office de choix pour savoir si nouvelle partie doit être lancée, ou charger une partie ou quitter le jeu
 */
int newGame(){
	int choose=0;
	while ( choose != 1  && choose != 2 && choose != 3 ){
		printf("------- Menu Hex -------\n");
		printf("1 - Nouvelle partie\n");
		printf("2 - Charger partie\n");
		printf("3 - Quitter\n");
		scanf("%d", &choose);
	}
	return choose;
}

/**
 * Mise à jour de l'historique de toutes les parties jouées
 * Paramètres :	pa = joueur gagnant
 *				pb = joueur perdant
*/
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

/**
 * Initialisation de l'historique
 * Paramètres : histo = créer un historique pouvant contenir N*N données
*/
void init_histo(Historique histo[]){
	for(int i = 0;i<N*N;i++){
		histo[i] = (Historique)malloc(sizeof(struct s_historique));
	}
}

/**
 * Sauvegarder la partie
 * Paramètres : b = plateau du jeu
 *				aa = l'un des deux joueur de la partie
 *				bb = l'autre joueur de la partie
 *				histo = historique de la partie
 *				nbTurn = nombre de tour actuel de la partie
*/
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

Board load_game(Board b){
		return b;

		/* Ceci est un début de code de la fonction de chargement de partie. Une erreur bizarre m'a forcé à arrêter.
			Mon compilateur ne trouve pas les fonctions contenues dans dirent.h donc impossible de faire quoi que ce soit de fonctionnel
		*/
        DIR* rep; 
        rep = opendir("./saves");
        int choix, cpt = 1;
        system("clear");
        if (rep != NULL){
                struct dirent * lecture;
                while((lecture = readdir(rep)) != NULL){
                    printf("%d: %s\n", cpt, lecture->d_name);
                    cpt++;
                }
                printf("Affichage du contenu du dossier de sauvegarde. Veuillez choisir un fichier\n de sauvegarde valide de format nom-nom-chiffre.txt:\n");
                scanf("%d", &choix);
                if(choix>0 && choix<cpt)
                	closedir(rep);
                	rep = opendir("./saves");
                	cpt = 1;
                	while((lecture = readdir(rep)) != NULL){
                    	if(cpt == choix){
                    		fopen(lecture->d_name,"a");

                    	}

                	}


                closedir(rep);
        }
}