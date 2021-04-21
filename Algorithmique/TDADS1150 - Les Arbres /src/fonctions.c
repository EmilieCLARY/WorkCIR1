#include "fonctions.h"
#include "genericStackAndQueue.h"

// Fonctions Arbres

noeud* CreateNode(int valeur){

    noeud* tmp;
	tmp = (noeud*)malloc(sizeof(noeud));

    if (tmp != NULL) {
		tmp->data = valeur;
		tmp->lchild = NULL;
        tmp->rchild = NULL;
	}

	return(tmp);
}


void AfficherArbre(noeud * tmp, int profondeur) {

    if (tmp != NULL){

        AfficherArbre(tmp->rchild, profondeur+1); // Fils Droit

        for (int i = 0; i < profondeur; i++){
            printf(" ");
        }
        
        printf("%d \n", tmp->data); // Noeud Courant

        AfficherArbre(tmp->lchild, profondeur+1); // Fils Gauche

    }
}

void DisplayTree(arbre t){
    AfficherArbre(t.root, 0);
}

void AffichageSimple(noeud * tmp){
    
    if (tmp != NULL){

        AffichageSimple(tmp->rchild); // Fils Droit
        
        printf("%d \n", tmp->data); // Noeud Courant

        AffichageSimple(tmp->lchild); // Fils Gauche

    }
}

void AfficherSans10(noeud * tmp){

    if (tmp != NULL){

        AfficherSans10(tmp->rchild); // Fils Droit
        
        if (tmp->data > 10){
            printf("%d \n", tmp->data); // Noeud Courant
        }

        AfficherSans10(tmp->lchild); // Fils Gauche

    }

}

int NodeCounter(noeud * tmp){
    
    int count = 0;
    
    if (tmp != NULL) {
        count = NodeCounter(tmp->lchild) + NodeCounter(tmp->rchild);
        count++;
    }
    return count;
}

void Multiplicateur2Affichage(noeud * tmp, int profondeur){
    
    if (tmp != NULL){

        Multiplicateur2Affichage(tmp->rchild, profondeur+1); // Fils Droit

        for (int i = 0; i < profondeur; i++){
            printf(" ");
        }
        
        tmp->data = tmp->data * 2;
        printf("%d \n", tmp->data); // Noeud Courant

        Multiplicateur2Affichage(tmp->lchild, profondeur+1); // Fils Gauche
    }
}

int ProfondeurMax(noeud * tmp){
	
    int prof = -1;
	if (tmp != NULL) {
		if (ProfondeurMax(tmp->lchild) > ProfondeurMax(tmp->rchild)) {
			prof= ProfondeurMax(tmp->lchild);
		}
		else
		{
			prof = ProfondeurMax(tmp->rchild);
		}
		prof++;	
	}
	return prof;
}

int ValeurMax(noeud * tmp){

    int value = 0;

    if (tmp != NULL){

        value = tmp->data;

        int left = ValeurMax(tmp->lchild);
        int right = ValeurMax(tmp->rchild);
        
        if (value < left) {
            value = left;
        }
        else if (value < right)
        {
            value = right;
        }
    }
    return(value);
}

void ParcoursLargeur(arbre tr) {

    Queue* file;
    NewQueue(&file, 6);
    noeud* currentNode = tr.root;
    queue(file, currentNode);

    while (!isQueueEmpty(file)) {
        deQueue(file, &currentNode);

        if (currentNode->lchild != NULL) {
            queue(file, currentNode->lchild);
        }

        if (currentNode->rchild != NULL) {
            queue(file, currentNode->rchild);
        }

        printf("%d ", currentNode->data);
    }
}

void ParcoursProfondeur(arbre tr) {

    Stack* pile;
    NewStack(&pile, 6);
    noeud* currentNode = tr.root;
    push(pile, currentNode);

    while (!isStackEmpty(pile)) {

        pull(pile, &currentNode);

        if (currentNode->rchild != NULL) {
            push(pile, currentNode->rchild);
        }

        if (currentNode->lchild != NULL) {
            push(pile, currentNode->lchild);
        }

        printf("%d ", currentNode->data);
    }
}