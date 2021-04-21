#include "fonctions.h"
#include "genericStackAndQueue.h"



/************************************************************************/
/*  Pascal Ricq 2020                                                    */
/*  ver 2.0                                                             */
/************************************************************************/
#define STACKOVERFLOW -1

// paquetage de gestion de piles et de files de taille fixe
// impl�ment�es � l'aide d'un tableau allou� par malloc
// la valeur empil�e est un pointeur void


void NewStack(Stack **stack, int initialStackSize) {
	*stack = (Stack *)malloc(sizeof(Stack));
	if (*stack != NULL) {
		(*stack)->tab = (void **)malloc(sizeof(void *) * initialStackSize);
		if (((*stack)->tab) != NULL) {
			(*stack)->stackMaxSize = initialStackSize;
			(*stack)->stackNbElemts = 0;
		}
		else {
			free(*stack);
			*stack = NULL;
		}
	}
}


int isStackFull(Stack * stack) {
	return((stack->stackNbElemts >= stack->stackMaxSize));
};

int isStackEmpty(Stack *stack) {
	return(stack->stackNbElemts == 0);
}


int push(Stack *stack, void * value) {
	if (!isStackFull(stack)) {
		stack->tab[stack->stackNbElemts] = value;
		stack->stackNbElemts++;
		return(0);
	}
	else {
		return(STACKOVERFLOW);
	}
}

int pull(Stack *stack, void **value) {
	if (!isStackEmpty(stack)) {
		*value = stack->tab[stack->stackNbElemts - 1];
		stack->stackNbElemts--;
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);
}


int peek(Stack *stack, void **value) {
	if (!isStackEmpty(stack)) {
		*value = stack->tab[stack->stackNbElemts - 1];
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);

}
void NewQueue(Queue **queue, size_t initialQueueSize) {
	*queue = (Queue *)malloc(sizeof(Queue));
	if (*queue != NULL && initialQueueSize>0) {
		// allocation de l'espace de stockage des �l�ments empil�s, ici des pointeurs void
		(*queue)->tab = (void**)malloc(sizeof(void *) * initialQueueSize );
		if (((*queue)->tab) != NULL) {
			// initialisation de tous les pointeurs du tableau � NULL
			for (size_t i = 0; i < initialQueueSize; i++) {
				(*queue)->tab[i] = NULL;
			}
			(*queue)->first = -1;
			(*queue)->last = -1;
			(*queue)->queueNbElemt = 0;
			(*queue)->queueMaxSize = initialQueueSize;
		}
		else {
			free(*queue);
			*queue = NULL;
		}
	}
}
int isQueueEmpty(Queue *queue) {
	return(queue->queueNbElemt == 0);

}
int isQueueFull(Queue *queue) {
	return(queue->queueNbElemt == queue->queueMaxSize);
}
int enQueue(Queue *queue, void * value) { // gestion de la file en tableau circulaire
	if (isQueueFull(queue)) return(EXIT_FAILURE);
	if (isQueueEmpty(queue)) {
		queue->first = 0;
		queue->last = 0;
		queue->queueNbElemt = 1;
		queue->tab[queue->last] = value;
	}
	else {
		if ((queue->last + 1) >= queue->queueMaxSize) {
			queue->last = 0;
		}
		else {
			queue->last++;
		}
		queue->tab[queue->last] = value;
		queue->queueNbElemt++;
	}

	return(EXIT_SUCCESS);
}
int deQueue(Queue *queue, void **value) {
	if (isQueueEmpty(queue)) return(EXIT_FAILURE);
	*value = queue->tab[queue->first];
	if ((queue->first + 1) >= queue->queueMaxSize) {
		queue->first = 0;
	}
	else {
		queue->first++;
	}
	queue->queueNbElemt--;

	return(EXIT_SUCCESS);
}




// debug

void DisplayTab(int *tab, int Size) {
	printf("\n[");
	for (int i = 0; i < Size; i++) (printf("%4d", tab[i]));
	printf("]\n");
}