#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listes.h"


LinkedList *NewLinkedList() {
	LinkedList* tmp;

	tmp = (LinkedList*)malloc(sizeof(LinkedList));

	if (tmp != NULL) {
		tmp->head = NULL;
		tmp->tail = NULL;
		tmp->size = 0;
	}

	return tmp;

}

SingleLinkedListElem *NewLinkedListItem(int value) {
	SingleLinkedListElem* tmp;
	tmp = (SingleLinkedListElem*)malloc(sizeof(SingleLinkedListElem));

	if (tmp != NULL) {
		tmp->data = value;
		tmp->next = NULL;
	}
	return(tmp);
}


int AjouterNouveauElemt(LinkedList* list, SingleLinkedListElem* elem) {

	//test pour voir si la ligne est vide
	if (list == NULL || elem == NULL || elem->next != NULL) return 0;

	if (list->tail == NULL) {
		list->tail = elem;
		list->head = elem;
		list->size = 1;
	}
	else {
		//On rajoute un élément à la fin de la liste
		list->tail->next = elem;
		list->tail = elem;
		list->size += 1;
	}

	return 1;
}

int EnleverElemt(LinkedList* list, SingleLinkedListElem* elem) {
	/*-----------------Plusieurs cas d'erreur--------------*/

	//La liste n'exite pas
	if (list == NULL) return(0);

	//liste vide ou anomalie
	if ((list->head == NULL) || (list->tail == NULL)) return(0);

	//anomalie sur la taille
	if ((list->head == list->tail) && (list->size != 1)) return(0);

	//Elemts invalides ou aucun Elemts
	if ((list->size == 0) || (elem == NULL)) return (0);

	//initialisation d'un pointeur sur l'élément courant
	SingleLinkedListElem *tmp = list->head;

	//Previous correspond à l'élement qui précède l'élément courant
	SingleLinkedListElem* previous = NULL;

	//l'élément est en tète et en queue, il y a donc 1 seul élément dans la liste

	if((elem == list->head) && (elem == list->tail)) {

		list->head = NULL;
		list->tail = NULL;
		list->size = 0;
		free(elem);
		return(1);
	}





	//Il est en tête, on supprime la tête

	if (elem == list->head) {

		list->head = elem->next;
		list->size--;
		free(elem);
		return(1);

	}

	//Recherche du maillon dans le reste de la liste chainée

	while ((tmp != NULL) && (tmp != elem)) {
		previous = tmp;
		tmp = tmp->next;
	}



	//S'il est en queue on supprime la queue
	if ((previous != NULL) && (tmp == elem) && (tmp->next != NULL)) {

		list->tail=previous;
		previous->next = NULL;
		list->size--;
		free(elem);
		return(1);
	}

	//S'il est au milieu, on supprime l'élément

	if((previous != NULL) && (tmp == elem) && (tmp->next != NULL)) {
		previous->next = elem->next;
		list->size--;
		free(elem);
		return(1);
	}

	//l'élément recherché n'a pas été trouvé

	return(0);
}


int DisplayList(LinkedList *Liste) {
	
	SingleLinkedListElem* maillonActu = Liste->head;

	while (maillonActu != NULL) {

		printf("%d -> ", maillonActu->data);
		maillonActu = maillonActu->next;

	}

	printf("NULL");


}