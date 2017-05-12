/* Initialise les informations des deux joueurs */
void initJoueurs(Player *pa, Player *pb){
        (*pa)->value=1;
        (*pb)->value=2;
        printf("Quel est le nom du premier joueur ? ");
        scanf("%s",&(*pa)->nom);
        printf("Quel est le nom du second joueur ? ");
        scanf("%s",&(*pb)->nom);
        (*pa)->dernierCoupJouer=NULL;
        (*pb)->dernierCoupJouer=NULL;
        (*pa)->nbCoups=0;
        (*pb)->nbCoups=0;
}

/* Retourne le joueur qui jouera en premier */
int chooseFirstPlayer(Player *pa,Player *pb){
        int nbAlea;
        nbAlea=(rand()%2)+1;
        
        if (nbAlea == (*pa)->value ){
                printf("Le premier joueur est %s.\n",(*pa)->nom);
        }else{
                printf("Le premier joueur est %s.\n",(*pb)->nom);
        }
        
        return nbAlea;
}
