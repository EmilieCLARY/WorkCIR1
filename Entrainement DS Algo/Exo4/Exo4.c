#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>

#define FIGURE '*'
#define ESPACE ' '

int main() {

	int losange(int rayon, bool fill) {

		int size = rayon * 2 - 1; // à cause d'une erreur dans l'exemple de l'énoncé (3 au lieu de 5 )
		if (size % 2 == 0) return(-1);
		int milieu = size / 2;
		int col = 0;
		int bordGauche = 0;
		int bordDroit = 0;

		for (int ligne = 0; ligne < size; ligne++) {
			col = 0;
			if (ligne < milieu) {
				bordGauche = milieu - ligne;
				bordDroit = milieu + ligne;
			}
			else {
				if (ligne == milieu) {
					bordGauche = 0;
					bordDroit = size - 1;
				}
				else {
					bordGauche = ligne - milieu;
					bordDroit = milieu + (size - 1 - ligne);
				}
			}
			while (col < size) {
				if (!fill && ((col == bordDroit) || (col == bordGauche)) || (fill && (col >= bordGauche) && (col <= bordDroit))) {
					printf("%c", FIGURE);
				}
				else {
					printf("%c", ESPACE);
				}
				col++;
			}
			printf("\n");
		}
		return 0;
	}
}