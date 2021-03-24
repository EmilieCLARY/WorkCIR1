#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>


typedef struct Queue {
int first; // Index of the first element in the array
int last; // Index of the last element in the array
int queueMaxSize; // Maximum number of elements in the Queue
int queueNbElemt; // Current count of elements in the Queue
int *tab; // Pointer towards dynamically allocated array

} Queue;
void NewQueue(Queue **queue, int initialQueueSize);

// Teste si la file est vide
bool isQueueEmpty(Queue *queue);

// Teste si la file est pleine
bool isQueueFull(Queue *queue);

// Ajoute un élément dans la file
int queue(Queue *queue, int value);

// Sort un élément de la file
int deQueue(Queue *queue, int *value);
