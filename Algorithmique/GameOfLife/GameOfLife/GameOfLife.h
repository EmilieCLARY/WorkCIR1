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


// Gen1 et Gen2 contiennent les g�n�rations successives d'�tres en vie ou morts
char* Gen1; // Gen1 et Gen2 doivent �tre initialis�s avec une allocation dynamique
char* Gen2;

// initLife initialise un tableau, d'abord compl�tement avec des morts puis place les �tres en vie et renvoie leur nombre
int initLife(char** life, int sizeX, int sizeY);

// nextGen calcule l'apparition ou la disparition des �tres � la g�n�ration suivante, de Gen1 vers Gen2 et renvoie leur nb
int nextGen(char* gen1, char* gen2, int sizeX, int sizeY);

// displayGen Affiche une g�n�ration sur la console
void displayGen(char* life, int sizeX, int sizeY);

// countNeighbours d�nombre les �tres en vie autour de la postion (posX, posY) dans le tableau Life (une g�n�ration)
int countNeighbours(char* life, int sizeX, int sizeY, int posX, int posY);

// D�termine s'il y a une naissance ou une disparition en fonction du nombre de voisins et de l'�tat actuel
char lifeState(int nbNeighbours, char state);