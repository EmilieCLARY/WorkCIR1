#include "GameOfLife.h"
int initLife(char** life, int sizeX, int sizeY) {
	*life = (int*)malloc(sizeX * sizeY * sizeof(char));

	if (*life != NULL) {
		for (int i = 0; i < sizeX * sizeY; i++) {
			(*(*life + i)) = Dead;
		}
		srand(time(NULL));
		int i = 0;
		while (i <= NBLIVES) {
			int x = rand() % sizeX;
			int y = rand() % sizeY;
			if (*(*life + x * sizeX + y) != Alive) {
				*(*life + x * sizeX + y) = Alive;
				i++;
			}
		}

	}
	else {
		printf("Mémoire insuffisante");
		return(-1);
	}
}


void displayGen(char* life, int sizeX, int sizeY) {
	for (int i = 0; i<sizeX; i++) {
		for (int j = 0; i<sizeY; j++){
			moveCursor(i, j);
			if ((*life + i * sizeX + j) == Alive){
				plot(Alive);
			}
			else{
				plot(Dead);
			}
		}
	}
}


/*
// calcul de la génération suivante

int nextGen(char* gen1, char* gen2, int sizeX, int sizeY) {
	int nbLives = 0;
	// on crée dans gen2 les êtres vivants à partir de l'état du tableau Gen1
	for (int l = 0; l < sizeY; l++) { // les variables l et c représentent la position d’une case en (ligne, colonne)
		for (int c = 0; c < sizeX; c++) {
			*(gen2 + (l * sizeX + c)) = lifeState(countNeighbours(gen1, sizeX, sizeY, c, l), *(Gen2 + (l * sizeX + c)));
			if (*(gen2 + (l * sizeX + c)) == Alive) nbLives++;
		}
	}
	return(nbLives);
}




char lifeState(int nbNeighbours, char state) {

	int newState;

	newState=state;

		if (state == Alive && (nbNeighbours > 3 || nbNeighbours < 2)) {
			newState = Dead;
		}

		if (state == Alive && (nbNeighbours == 3)) {
			newState = Alive;
		}

		return(newState); //A VERIFIER
}

int countNeighbours(char* life, int sizeX, int sizeY, int posX, int posY) {

//	cas 1 life[posx-1][posy-1]
//	cas 2 life[posx-1][posy]
//	cas 3 life[posx-1][posy+1]

//	cas 4 life[posx][posy-1]
//	cas 5 life[posx][posy] A EXCLURE
//	cas 6 life[posx][posy+1]

//	cas 7 life[posx+1][posy-1]
//	cas 8 life[posx+1][posy]
//	cas 9 life[posx+1][posy+1]

	int compte = 0;

	for (int i = posX - 1; i < posX + 1; i++) {
		for (int j = posY - 1; j < posY + 1; j++) {

			if (i >=0 && j >=0 && i<sizeX && j<sizeY &&!(i==posX &j==posY)) {

				if (life+(i*LifeSizeX+j)==Alive) { //Adresse life + i* la taille d'une ligne + j
					compte += 1;
				}
			}


		}
	}


}
*/

