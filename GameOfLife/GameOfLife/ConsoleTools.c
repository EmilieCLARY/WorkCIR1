#include "ConsoleTools.h"

/***********************************/
//	fichier ConsoleTools.c
//	Auteur : Pascal RICQ
//	version projet :  6.3
//  date 24-11-2020
//	remarque : développement … vocation pédagogique
//	fonctionne avec Visual Studio sous Windows.

SYSTEMTIME elapsedTime(bool reset) {

	SYSTEMTIME duration;
	FILETIME fcurrentTime, fduration;
	static ULARGE_INTEGER fprevTime64 = { 0,0 };
	ULARGE_INTEGER fcurrTime64, fduration64;
	if (reset) {
		fprevTime64.QuadPart = 0;

	}

	GetSystemTimeAsFileTime(&fcurrentTime);
	fcurrTime64.HighPart = fcurrentTime.dwHighDateTime;
	fcurrTime64.LowPart = fcurrentTime.dwLowDateTime;
	fduration64.QuadPart = fcurrTime64.QuadPart - fprevTime64.QuadPart;
	fduration.dwHighDateTime = fduration64.HighPart;
	fduration.dwLowDateTime = fduration64.LowPart;
	FileTimeToSystemTime(&fduration, &duration);
	fprevTime64 = fcurrTime64;


	return(duration);
}


char readChar(const char* filtre) {

	char car = -1;
	char* tmp;
	while (car == -1) {
		car = 0;
		while (car == 0) car = (char)_getch();

		if ((tmp = strchr(filtre, car)) != NULL) {
			car = *tmp;
		}
		else car = -1;
	};
	return car;
}


int openConsole() {

	// Seed the random-number generator with the current time so that
	// the numbers will be different every time we run.
	// srand((unsigned)time(NULL));
	// 
	// Nouvelle version : on observe que le 1er nombre envoyé par rand est souvent le même..

	SYSTEMTIME st;			// récupération de la date système
	GetSystemTime(&st);
	int time_ms = st.wMilliseconds;  // recupération des milliseconde de l'heure courante, 
									// cette valeur est plus volatile que les secondes

	// initialisation du générateur de nombres aléatoires
	srand(time_ms);

	// premier appel à rand afin de ne pas utiliser la 1ere valeur qui n'est pas très aléatoire ..
	// est-ce un bug du SDK ?
	int u = rand();


	// Get handles to STDIN and STDOUT. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdin == INVALID_HANDLE_VALUE ||
		hStdout == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
			MB_OK);
		return 1;
	}
	// Save the current text colors. 

	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"),
			TEXT("Console Error"), MB_OK);
		return 1;
	}

	wOldColorAttrs = csbiInfo.wAttributes;

	// Save the current consoleMode

	if (!GetConsoleMode(hStdout, &Mode))
	{
		MessageBox(NULL, TEXT("GetConsoleMode"),
			TEXT("Console Error"), MB_OK);
		return 1;
	}
	wOldMode = Mode;
	return(0);
}

int blink(COORD pos, DWORD length, DWORD heigth, DWORD duration) {
	WORD* oldAttrib;
	DWORD nbAttrib;
	WORD newAttrib;
	COORD pix = pos;
	// sauvegarde des attributs de chaque pixel
	oldAttrib = (WORD*)malloc(sizeof(WORD) * length * heigth);
	if (oldAttrib == NULL) return(1);
	for (unsigned int l = 0; l < heigth; l++)
	{
		for (unsigned int c = 0; c < length; c++)
		{
			int offset = (l * length + c);
			pix.X = pos.X + c; pix.Y = pos.Y + l;
			if (!ReadConsoleOutputAttribute(hStdout, oldAttrib + offset, 1, pix, &nbAttrib))
			{
				MessageBox(NULL, TEXT("ReadConsoleOutputAttribute"),
					TEXT("Console Error"), MB_OK);
				return 1;
			}
			else {
				newAttrib = *(oldAttrib + offset);
				newAttrib = newAttrib | COMMON_LVB_REVERSE_VIDEO;
				if (!WriteConsoleOutputAttribute(hStdout, &newAttrib, 1, pix, &nbAttrib))
				{
					MessageBox(NULL, TEXT("WriteConsoleOutputAttribute"),
						TEXT("Console Error"), MB_OK);
					return 1;
				}
			}
		}
	}

	Sleep(duration);
	pix = pos;
	for (unsigned int l = 0; l < heigth; l++)
	{
		for (unsigned int c = 0; c < length; c++)
		{
			int offset = (l * length + c);
			pix.X = pos.X + c; pix.Y = pos.Y + l;
			if (!WriteConsoleOutputAttribute(hStdout, oldAttrib + offset, 1, pix, &nbAttrib))
			{
				MessageBox(NULL, TEXT("WriteConsoleOutputAttribute"),
					TEXT("Console Error"), MB_OK);
				return 1;
			}

		}
	}
	free(oldAttrib);
	return 0;
}

void hideCursor(void) {
	CONSOLE_CURSOR_INFO lpConCurInfo;
	lpConCurInfo.bVisible = false;
	lpConCurInfo.dwSize = 1;
	SetConsoleCursorInfo(hStdout, &lpConCurInfo);
}
void showCursor(void) {
	CONSOLE_CURSOR_INFO lpConCurInfo;
	lpConCurInfo.bVisible = true;
	lpConCurInfo.dwSize = 1;
	SetConsoleCursorInfo(hStdout, &lpConCurInfo);
}
int setWriteColor(WORD col) {

	WORD colAttrib = 0;
	WORD wCurColorAttrs;

	switch (col)
	{
	case	0: // BLACK
		colAttrib = 0;
		break;
	case	1: // BLUE
		colAttrib = FOREGROUND_BLUE;
		break;
	case	2:	// GREEN
		colAttrib = FOREGROUND_GREEN;
		break;
	case	3: // CYAN
		colAttrib = FOREGROUND_BLUE | FOREGROUND_GREEN;
		break;
	case	4: // RED
		colAttrib = FOREGROUND_RED;
		break;
	case	5: // MAGENTA
		colAttrib = FOREGROUND_BLUE | FOREGROUND_RED;
		break;
	case	6: // YELLOW
		colAttrib = FOREGROUND_GREEN | FOREGROUND_RED;
		break;
	case	7: // GREY
		colAttrib = FOREGROUND_INTENSITY;
		break;
	case	8: // DARK GREY
		colAttrib = 0;
		break;
	case	9: // BRIGHT BLUE
		colAttrib = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case	10:	// BRIGHT GREEN
		colAttrib = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case	11: // BRIGHT CYAN
		colAttrib = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case	12: // BRIGHT RED
		colAttrib = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case	13: // BRIGHT MAGENTA
		colAttrib = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case	14: // BRIGHT YELLOW
		colAttrib = FOREGROUND_YELLOW;
		break;
	case	15: // WHITE
		colAttrib = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	default:
		colAttrib = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	}


	if (GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) {
		wCurColorAttrs = csbiInfo.wAttributes;

		wCurColorAttrs = wCurColorAttrs & 0xFFF0;
		wCurColorAttrs = wCurColorAttrs | colAttrib;

		if (!SetConsoleTextAttribute(hStdout, wCurColorAttrs))
		{
			MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
				TEXT("Console Error"), MB_OK);
			return 1;
		}
	}



	return 0;
}
int setBackGroundColor(WORD col) {

	WORD colAttrib = 0;
	WORD wCurColorAttrs;

	switch (col)
	{
	case	0: // BLACK
		colAttrib = 0;
		break;
	case	1: // BLUE
		colAttrib = BACKGROUND_BLUE;
		break;
	case	2:	// GREEN
		colAttrib = BACKGROUND_GREEN;
		break;
	case	3: // CYAN
		colAttrib = BACKGROUND_BLUE | BACKGROUND_GREEN;
		break;
	case	4: // RED
		colAttrib = BACKGROUND_RED;
		break;
	case	5: // MAGENTA
		colAttrib = BACKGROUND_BLUE | BACKGROUND_RED;
		break;
	case	6: // YELLOW
		colAttrib = BACKGROUND_GREEN | BACKGROUND_RED;
		break;
	case	7: // GREY
		colAttrib = BACKGROUND_INTENSITY;
		break;
	case	8: // DARK GREY
		colAttrib = 0;
		break;
	case	9: // BRIGHT BLUE
		colAttrib = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case	10:	// BRIGHT GREEN
		colAttrib = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case	11: // BRIGHT CYAN
		colAttrib = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case	12: // BRIGHT RED
		colAttrib = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case	13: // BRIGHT MAGENTA
		colAttrib = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case	14: // BRIGHT YELLOW
		colAttrib = BACKGROUND_YELLOW;
		break;
	case	15: // WHITE
		colAttrib = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	default:
		colAttrib = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	}


	if (GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) {
		wCurColorAttrs = csbiInfo.wAttributes;

		wCurColorAttrs = wCurColorAttrs & 0xFF0F;
		wCurColorAttrs = wCurColorAttrs | colAttrib;

		if (!SetConsoleTextAttribute(hStdout, wCurColorAttrs))
		{
			MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
				TEXT("Console Error"), MB_OK);
			return 1;
		}
	}



	return 0;
}
int closeConsole() {
	// Restore the original text colors. 

	SetConsoleTextAttribute(hStdout, wOldColorAttrs);
	return(0);
}


//COORD getConsoleSize() {
//	COORD Size;
//
//	Size.X = csbiInfo.dwSize.X;
//	Size.Y = csbiInfo.dwSize.Y;
//	return(Size);
//}

void moveCursor(unsigned short int X, unsigned short int Y) {

	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(hStdout, pos);

	return;
}
int plotChar(char SomeChar) {
	chBuffer[0] = SomeChar;
	chBuffer[1] = 0;
	cRead = 1;
	if (WriteFile(hStdout, chBuffer, cRead, &cWritten, NULL)) {
		return(0);
	}
	else {
		return(GetLastError());
	}
}

int rangedRand(int range_min, int range_max)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max

	int u = (int)((double)rand() / ((double)RAND_MAX + 1) * ((double)range_max - (double)range_min)) + range_min;
	return(u);
}



int clearScreen(void) {
	COORD consoleSize;

	//consoleSize = getConsoleSize();
	consoleSize.X = 120;
	consoleSize.Y = 60;
	// setWriteColor(GREY);
	// setBackGroundColor(BLACK);
	for (int i = 0; i < consoleSize.Y; i++)
	{
		for (int j = 0; j < consoleSize.X; j++)
		{

			moveCursor(j, i);
			plotChar(' ');
		}
	}

	return 0;
}

