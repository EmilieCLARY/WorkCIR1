#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <time.h>


void rotationDroiteTab(int tab[100][50]) {

	for (int i = 0; i <= 100; i++) {

		for (int j=0 ; j <= 50 ; j++) {

			tab[i++][j] = tab[i][j];

			if (i==100) {
				tab[0][j] = tab[100][j];

			}
		}
	}
}



int main() {

	
	int tab1[100][50];
	srand(time(NULL));

	for (int i = 0; i <= 100; i++) {

		for (int j = 0; j <= 50; j++) {
			tab1[i][j] = rand() %5;
			printf("%d ", tab1[i][j]);
		}
	}


	rotationDroiteTab(tab1[100][50]);
	

}