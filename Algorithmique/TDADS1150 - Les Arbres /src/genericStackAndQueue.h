#pragma once
/************************************************************************/
/*  Pascal Ricq 2020                                                    */
/*  ver 2.0                                                             */
/************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

// paquetage de gestion de piles et de files de taille fixe
// implémentées à l'aide d'un tableau alloué par malloc
// la valeur empilée est un pointeur void

#define STACKOVERFLOW -1


typedef struct Stack {

	void **tab;
	int stackMaxSize;  // taille max
	int stackNbElemts; // nb elements

} Stack;


typedef struct Queue {

	void **tab;
	int first;			// index of the first element in the array
	int last;			// index of the last element in the array
	int queueMaxSize;   // maximum number of elements in the Queue
	int queueNbElemt;	// current count of elements in the Queue

} Queue;

// implémentation des Piles avec des tableaux statiques
void NewStack(Stack **stack, int initialStackSize);
int isStackFull(Stack * stack);
int isStackEmpty(Stack *stack);
int push(Stack *stack, void *value);
int pull(Stack *stack, void **value);
int peek(Stack *stack, void **value);




void NewQueue(Queue **queue, size_t initialQueueSize);
int isQueueEmpty(Queue *queue);
int isQueueFull(Queue *queue);
int enQueue(Queue *queue, void *value);
int deQueue(Queue *queue, void **value);



void DisplayTab(int *tab, int Size);
