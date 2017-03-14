#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct s_plateau *Plateau;

Plateau creer_plateau();

void ajouter_pion(Plateau p, int pion);
