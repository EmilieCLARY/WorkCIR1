#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int timesec = 0, nbrminutes, nbrheures;


//Question 1.1

//Doit afficher : Nombre_d_Heures : Nombre_de_Minutes : Nombre_de_Secondes

void displayHHMMSS(TimeInSeconds) {

	if (timesec < 0) {
		printf("Valeur incorrecte");
		return EXIT_FAILURE;
	}

	while (timesec >= 60) {

		nbrminutes += 1;
		timesec -= 60;

		if (nbrminutes >= 60) {

			nbrheures += 1;
			nbrminutes = 0;
		}
	}
	printf("%d : %d : %d", nbrheures, nbrminutes, timesec);
}

//Question 1.2

	int convertHHMMSStoSeconds(int hours, int minutes, int seconds) {

		int sec1, sec2, total;

		scanf_s("%d %d %d", &hours, &minutes, &seconds);

		if (minutes >= 60 || seconds >= 60 || hours < 0 || minutes < 0 || seconds < 0 ) {
			total = -1;
		}
		else
		{
			sec1 = hours * 3600;
			sec2 = minutes * 60;

			total = sec1 + sec2 + seconds;
		}


		printf("%d", total);
	}


//Question 1.3 

	int duration(int hours1, int minutes1, int seconds1, int hours2, int minutes2, int seconds2) {


		int total1, total2, totalF;
		total1 = convertHHMMSStoSeconds(hours1, minutes1, seconds1);
		total2 = convertHHMMSStoSeconds(hours2, minutes2, seconds2);

		if (total1 == -1 || total2 == -1) {
			return(-1);
		}

		if (total1 > total2)
			totalF = total1 - total2;
		else {
			totalF = total2 - total1;
		}

		return(totalF);
	}

		


int main() {

	//Question 1.1
//scanf_s("%d", &timesec);
//displayHHMMSS(timesec);




}