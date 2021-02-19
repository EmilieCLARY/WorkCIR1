#include "tri.h"

#define TAILLETABMAX 1000000
#define NOMBREMAX 100


int tab[TAILLETABMAX];
int min=NOMBREMAX;


int main(){

    printf("\n\n");

    //Génération aléatoire du tableau
    srand(time(NULL));

    printf("Tableau random non trié :\n");

    for(int n = 0; n < TAILLETABMAX; n++) {
        tab[n] = rand() % NOMBREMAX+1;
        printf("| ");
        printf("%d ", tab[n]);
    }
    printf("|");

    printf("\n\n");

    //Tri à sélection ordinaire

    //TriSelection(tab,TAILLETABMAX);

    //Tri par insertion séquentielle

    TriInsertionSequentiel(tab, TAILLETABMAX);

    //Tri par insertion Dichotomique




 }
