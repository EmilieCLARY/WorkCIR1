#include "pilestab.h"
#define TAILLEMAX 20

Stack *pile;

int main() {

    printf("\n");
    printf("Pile Initiale\n\n");

    //Génération de la pile
    srand(time(NULL));

    NewStack(&pile, 10);

    for (int i=0; i<pile->stackMaxSize; i++){
        printf("%d / ", pile->tab[i]);
    }

    printf("\n");

    for (int i=0; i<pile->stackMaxSize; i++){
        push(pile, rand()%50);
    }

    printf("\n\n");


    //Affichage

    printf("Pile Remplie\n\n");

    for (int i = 0; i<pile->stackNbElemts; i++) {
        printf("%d / ", pile->tab[i]);

    }

    printf("\n\n");

    printf("Test de dépilage\n\n");

    pull(pile, 1);

    for (int i = 0; i<pile->stackNbElemts; i++) {
        printf("%d / ", pile->tab[i]);

    }

}