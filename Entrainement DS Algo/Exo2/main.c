#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <time.h>

#define TAILLE 100
#define JOURS 365


int main() {

	//Question 2.1
	int tab[TAILLE];

	srand(time(NULL));

	for (int i = 0; i < TAILLE;  i++) {
		tab[i] = rand() % 21;
		printf("%d / ", tab[i]);
	}


	printf("\n\n\n\n\n\n");
	//Question 2.2

	int sunnyDays[JOURS]; //Comme dans le nord lol
	int NbrJoursS = 0;

	srand(time(NULL));

	for (int i = 0; i < JOURS; i++) {

		sunnyDays[i] = rand() % 2;
		printf("%d", sunnyDays[i]);

		if (sunnyDays[i] == 1)
			NbrJoursS++;
	}

	printf("\n\nIl a fait beau %d jours dans l'annee.\n\n", NbrJoursS);

	system("PAUSE");
}