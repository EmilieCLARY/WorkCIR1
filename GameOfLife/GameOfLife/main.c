#include "ConsoleTools.h"
#include "GameOfLife.h"

int main() {
	char* life1 = NULL;
	char* life2 = NULL;


	openConsole();
	initLife(&life1, LifeSizeX, LifeSizeY);
	initLife(&life2, LifeSizeX, LifeSizeY);

	for (int i = 0; i<11; i++){

		displayGen(life1, LifeSizeX, LifeSizeY);

		system("pause");

		nextGen(life1, life2, LifeSizeX, LifeSizeY);

		for (int j = 0; j < LifeSizeX * LifeSizeY; j++) {
			*(life1+j)=*(life2+j);
		}

	}
	

	
	return(EXIT_SUCCESS);
}
