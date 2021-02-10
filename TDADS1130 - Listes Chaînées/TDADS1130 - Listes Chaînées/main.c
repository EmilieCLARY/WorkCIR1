#include "listes.h"


int main() {

	LinkedList* list = NewLinkedList();

	//Test Affichage

	for (int i = 0; i < 10; i++) {

		SingleLinkedListElem* E = NewLinkedListItem(i);
		AjouterNouveauElemt(list, E);

		//Test Enlever Element

		if (i == 4) {
			EnleverElemt(list, E);
		}

	}

	DisplayList(list);
	
	printf("\n\n\n");


	/*//Test maillon en tete de liste

	LinkedList* elem;
	LinkedList*E;
	int i;
	for(i=0; i<10; i++){
		//elem=insertElemAtLinkedListHead(elem,E);
	}*/


	//Test Liste Aléatoire

	LinkedList* ListRand = NewLinkedList();

	InitRandLinkedList(ListRand, 10);

	DisplayList(ListRand);
	
	

	printf("\n\n\n");

	//Test GetElement

	SingleLinkedListElem* val = GetElementAt(ListRand, 2);
	printf("%d", val->data);

	printf("\n\n\n");

	//Test Insérer Maillon en tête

	SingleLinkedListElem* F = NewLinkedListItem(4);
	insertElemAtLinkedListHead(list, F);

	DisplayList(list);




	printf("\n\n\n");

	return(1);
}