#include "fonctions.h"


int main(){

    //Création des noeuds

    noeud* noeud0 = CreateNode(5);
    noeud* noeud1 = CreateNode(12);
    noeud* noeud2 = CreateNode(15);
    noeud* noeud3 = CreateNode(7);

    //Création des liens entre les noeuds

    noeud0->lchild = noeud1;
    noeud0->rchild = noeud2;
    noeud2->rchild = noeud3;
    noeud2->lchild = CreateNode(21);

    //Création de l'arbre : Lien sur la racine

    arbre Arbre1 = {noeud0};
    //AfficherArbre(noeud0, 2);

    //printf("\n");

    //DisplayTree(Arbre1);


    // Création du deuxième arbre

    // Création des noeuds

    noeud * noeud10 = CreateNode(12);
    noeud * noeud11 = CreateNode(11);
    noeud * noeud12 = CreateNode(15);
    noeud * noeud13 = CreateNode(8);
    noeud * noeud14 = CreateNode(9);
    noeud * noeud15 = CreateNode(6);

    // Création des liens

    noeud10->rchild = noeud12;
    noeud10->lchild = noeud11;
    noeud11->rchild = noeud14;
    noeud12->lchild = noeud13;
    noeud13->lchild = noeud15;

    // Création de l'arbre

    arbre Arbre2 = {noeud10};

    printf("\n\nDeuxième Arbre\n\n");

    AfficherArbre(noeud10, 2);

    printf("\n");

    //DisplayTree(Arbre2);

    // Test Fonction Affichage Sans < 10

    //printf("\n\nSans 10\n\n");

    //AfficherSans10(noeud0);

    printf("%d \n\n", NodeCounter(noeud10));

    Multiplicateur2Affichage(noeud10, 3);
}