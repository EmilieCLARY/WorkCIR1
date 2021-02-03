#include "listes.h"


int main() {

	LinkedList* list = NewLinkedList();

	for (int i = 0; i < 10; i++) {

		SingleLinkedListElem* E = NewLinkedListItem(i);
		AjouterNouveauElemt(list, E);

	}

	DisplayList(list);
	
	//SingleLinkedListElem* E = 

	EnleverElemt(list, 4);

	printf("\n\n");

	DisplayList(list);

}