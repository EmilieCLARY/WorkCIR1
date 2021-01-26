#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ConsoleTools.h"

#define LifeSizeX 30
#define LifeSizeY 30
#define NBLIVES 150
#define Alive '*'
#define Dead ' '


// Gen1 et Gen2 contiennent les générations successives d'êtres en vie ou morts
char* Gen1; // Gen1 et Gen2 doivent être initialisés avec une allocation dynamique
char* Gen2;

// initLife initialise un tableau, d'abord complètement avec des morts puis place les êtres en vie et renvoie leur nombre
int initLife(char** life, int sizeX, int sizeY);

// nextGen calcule l'apparition ou la disparition des êtres à la génération suivante, de Gen1 vers Gen2 et renvoie leur nb
int nextGen(char* gen1, char* gen2, int sizeX, int sizeY);

// displayGen Affiche une génération sur la console
void displayGen(char* life, int sizeX, int sizeY);

// countNeighbours dénombre les êtres en vie autour de la postion (posX, posY) dans le tableau Life (une génération)
int countNeighbours(char* life, int sizeX, int sizeY, int posX, int posY);

// Détermine s'il y a une naissance ou une disparition en fonction du nombre de voisins et de l'état actuel
char lifeState(int nbNeighbours, char state);