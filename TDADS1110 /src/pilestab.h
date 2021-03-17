#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>

// définition du symbole de dépassement de pile
#define STACKOVERFLOW -1
// définition d'une pile à l'aide d'une structure
typedef struct Stack {
int *tab;
 // le tableau de données qu'il faut allouer
int stackMaxSize; // taille max
int stackNbElemts; // nb d'éléments actuellement dans la pile
} Stack;

// implémentation des Piles avec des tableaux dynamiques
// création d'un pile
void NewStack(Stack **stack, int initialStackSize);

bool isStackFull(Stack * stack);

bool isStackEmpty(Stack *stack);

int push(Stack *stack, int value);

int pull(Stack *stack, int *value);

int peek(Stack *stack, int *value);
