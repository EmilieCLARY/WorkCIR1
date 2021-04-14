#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct noeud{
    int data;
    struct noeud *rchild;
    struct noeud *lchild;
} noeud;


typedef struct arbre{
    noeud *root;
} arbre;

noeud* CreateNode(int valeur);

void AfficherArbre(noeud * tmp, int profondeur);

void DisplayTree(arbre t);

void AfficherSans10(noeud * tmp);

int NodeCounter(noeud * tmp);

void AffichageSimple(noeud * tmp);

void Multiplicateur2Affichage(noeud * tmp, int profondeur);

int ProfondeurMax(noeud * tmp);

int ValeurMax(noeud * tmp, int valeur);