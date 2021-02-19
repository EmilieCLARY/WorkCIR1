#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bool_mat.h>

//Tri par sélection ordinaire

int TriSelection(int *tab, int tabsize);


//Tri par insertion séquentielle

int TriInsertionSequentiel(int *tab, int tabsize);


//Tri par insertion Dichotomique

int rang(int *tab, int indmin, int indmax, int valeur);

int TriInsertionDichotomique(int *tab, int tabsize);


