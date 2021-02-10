#pragma once


typedef struct SingleLinkedListElem {

	int data;
	struct SingleLinkedListElem* next;

}SingleLinkedListElem;


typedef struct LinkedList {

	SingleLinkedListElem *head;
	int size;
	SingleLinkedListElem *tail;

}LinkedList;


LinkedList* NewLinkedList();

SingleLinkedListElem* NewLinkedListItem(int value);


int AjouterNouveauElemt(LinkedList* list, SingleLinkedListElem* elem);

int EnleverElemt(LinkedList* list, SingleLinkedListElem* elem);

void DisplayList(LinkedList* Liste);

int InitRandLinkedList(LinkedList * List, int ListSize);

SingleLinkedListElem *GetElementAt(LinkedList *Liste, int position);

int insertElemAtLinkedListHead(LinkedList *list, SingleLinkedListElem *elem);

int swapSingleLinkedListElements(LinkedList* liste, SingleLinkedListElem* elementA, SingleLinkedListElem* elementB);

int concatSingleLinkedLists(LinkedList* listC, LinkedList* listA, LinkedList* listB);