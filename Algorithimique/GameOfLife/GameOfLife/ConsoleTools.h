#pragma once

#include <windows.h> 
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

//************************
// fichier : ConsoleTools.h
//	Auteur : Pascal RICQ
//	version projet :  6.3
//  date 24-11-2020
//	remarque : développement … vocation pédagogique
//	fonctionne avec Visual Studio sous Windows.
//************************

HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
WORD wOldColorAttrs;

CHAR chBuffer[256];
DWORD cRead, cWritten, fdwMode, fdwOldMode;
DWORD Mode;
DWORD wOldMode;

#define BACKGROUND_YELLOW 0xE0
#define FOREGROUND_YELLOW 0x0E
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define YELLOW 6
#define GREY 7
#define DARKGREY 8
#define BRIGHTBLUE 9
#define BRIGHTGREEN 10
#define BRIGHTCYAN 11
#define BRIGHTRED 12
#define BRIGHTMAGENTA 13
#define BRIGHTYELLOW 14
#define WHITE 15

// renvoie le temps écoulé depuis le dernier appel
// si le paramètre est vrai, renvoie l'heure système actuelle
// SYSTEMTIME tps = elaspedTime(false);
// Sleep(500);
// tps = elaspedTime(false);
// printf("\ntemps écoulé %d:%d:%d,%03d hh:mm:ss,ms", tps.wHour, tps.wMinute, tps.wSecond, tps.wMilliseconds);
SYSTEMTIME elapsedTime(bool reset);

// attend la frappe d'une touche parmi celles spécifiées en paramètre
// ex: car =  readChar("onON");
char readChar(const char* filtre);

// permet d'utiliser les fonctions moveCursor et PlotChar (un seul appel en début de programme)
int openConsole();

// CloseConsole() doit être appelée après la dernière utilisation de moveCursor et PlotChar
int closeConsole();

// renvoie la taille de la console
//COORD getConsoleSize();
// déplace le curseur en X,Y position du prochain affichage
void moveCursor(unsigned short int X, unsigned short int Y);

// affiche un caractère à la position du curseur
int plotChar(char SomeChar);

// renvoie une valeur entière aléatoire rang_min<= x < rang_max
int rangedRand(int range_min, int range_max);

// affiche un inversé vidéo de la zone de la taille (lenght x height) en postion pos pdt le tps duration en ms
int blink(COORD pos, DWORD length, DWORD height, DWORD duration);

// masque le curseur
void hideCursor(void);

//affiche le curseur
void showCursor(void);

// change la couleur d'écriture des caractères
int setWriteColor(WORD col);

// change la couleur de fond des caractères
int setBackGroundColor(WORD col);

// nettoie l'écran
int clearScreen(void);