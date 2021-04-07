#include "fonctions.h"


int main(){

	DoubleLinkedList* list = newDoubleLinkedList();

	//Test Affichage

	for (int i = 0; i < 10; i++) {

		DoubleLinkedListElem* E = NewDoubleLinkedListItem(i);
		insertItemAtDoubleLinkedListTail(list, E);

	}

    //Affichage de la liste à l'endroit
    printf("Affichage à l'endroit\n");
	DisplayDoubleList(list);
    
    //Affichage de la liste à l'envers
    printf("\n\nAffichage à l'envers\n");
    RevDisplayDoubleList(list);
	
    srand(time(NULL));

    //Test Ajout à la fin
    DoubleLinkedListElem* D = NewDoubleLinkedListItem(rand() % 20);
    insertItemAtDoubleLinkedListTail(list, D);

    //Affichage de la liste à l'endroit
    printf("\n\n\nAffichage à l'endroit après rajout à la fin de la liste\n");
	DisplayDoubleList(list);
    
    //Affichage de la liste à l'envers
    printf("\n\nAffichage à l'envers après rajout à la fin de la liste\n");
    RevDisplayDoubleList(list);

    //Test Ajout au début
    DoubleLinkedListElem* F = NewDoubleLinkedListItem(rand() % 20);
    insertItemAtDoubleLinkedListHead(list, F);

    //Affichage de la liste à l'endroit
    printf("\n\n\nAffichage à l'endroit après rajout au début de la liste\n");
	DisplayDoubleList(list);
    
    //Affichage de la liste à l'envers
    printf("\n\nAffichage à l'envers après rajout au début de la liste\n");
    RevDisplayDoubleList(list);

    //Test Insertion Item

    /*DoubleLinkedListElem* G = NewDoubleLinkedListItem(rand() % 20);
    insertItemAfterItem(list, 3, G);

	DisplayDoubleList(list);*/

	printf("\n\n\n");


}