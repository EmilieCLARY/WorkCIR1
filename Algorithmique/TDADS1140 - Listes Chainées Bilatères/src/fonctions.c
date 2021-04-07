#include "fonctions.h"

// Création d'une nouvelle liste chaînée bilatère vide
DoubleLinkedList *newDoubleLinkedList() {
    DoubleLinkedList* tmp;

	tmp = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));

	if (tmp != NULL) {
		tmp->head = NULL;
		tmp->tail = NULL;
		tmp->size = 0;
	}

	return tmp;

}

//Ajout d'un élément
DoubleLinkedListElem *NewDoubleLinkedListItem(int value){
    DoubleLinkedListElem* tmp;
	tmp = (DoubleLinkedListElem*)malloc(sizeof(DoubleLinkedListElem));

	if (tmp != NULL) {
		tmp->data = value;
		tmp->next = NULL;
        tmp->previous = NULL;
	}
	return(tmp);
}

//Affichage de la liste chaînée
int DisplayDoubleList(DoubleLinkedList *list){

	if (list != NULL) {
		DoubleLinkedListElem* maillonActu = list->head;

		while (maillonActu != NULL) {

			printf("%d -> ", maillonActu->data);
			maillonActu = maillonActu->next;

		}

		printf("NULL");
	}

    return(0);

}

//Affichage de la liste chaînée en partant de la fin
int RevDisplayDoubleList(DoubleLinkedList *list){

	if (list != NULL) {
		DoubleLinkedListElem* maillonActu = list->tail;

		while (maillonActu != NULL) {

			printf("%d -> ", maillonActu->data);
			maillonActu = maillonActu->previous;

		}

		printf("NULL");

	}

    return(EXIT_SUCCESS);

}

//Insertion d'un élément en queue de liste chaînée bilatère
int insertItemAtDoubleLinkedListTail(DoubleLinkedList *list, DoubleLinkedListElem *newItem){
	if (list == NULL) return(0);

	list->size++;

	if (list->tail == NULL) {
		list->tail = newItem;
		list->head = newItem;
	}
    else {
	    DoubleLinkedListElem* tmp = list->tail;
	    list->tail = newItem;
	    list->tail->previous = tmp;
        tmp->next = list->tail;
	}

	return(0);
}

int insertItemAtDoubleLinkedListHead(DoubleLinkedList *list, DoubleLinkedListElem *newItem){
    if (list == NULL) return(0);

	list->size++;

	if (list->head == NULL) {
		list->head = newItem;
		list->tail = newItem;
	}
    else {
	    DoubleLinkedListElem* tmp = list->head;
	    list->head = newItem;
	    list->head->next = tmp;
        tmp->previous = newItem;
    }

	return(0);
}

int getDoubleLinkedListSize(DoubleLinkedList *list){
    return(list->size);
}

int insertItemAfterItem(DoubleLinkedList *list, DoubleLinkedListElem *item, DoubleLinkedListElem *newItem){
    
    //test pour voir si la ligne est vide
	if (list == NULL || newItem == NULL || newItem->next != NULL || newItem->previous != NULL) return 0;

    //Cas général
    newItem->next = item->next;
    item->next->previous = newItem;
    item->next = newItem;
	newItem->previous = item;

    //Cas pour Item = tail
    if (item == list->tail){
        newItem->next = NULL;
        newItem->previous = list->tail;
        list->tail = newItem;
    }

	list->size += 1;

	return 0;
}

int insertItemBeforeItem(DoubleLinkedList *list, DoubleLinkedListElem *item, DoubleLinkedListElem *newItem){

    //test pour voir si la ligne est vide
	if (list == NULL || newItem == NULL || newItem->next != NULL || newItem->previous != NULL) return 0;

    //Cas général
    newItem->next = item;
	newItem->previous = item->previous;
    item->previous->next = newItem;
    item->previous = newItem;

    //Cas pour Item = head
    if (item == list->head){
        newItem->previous = NULL;
        newItem->next = item;
        list->head = newItem;
    }

	list->size += 1;

	return 0;


}