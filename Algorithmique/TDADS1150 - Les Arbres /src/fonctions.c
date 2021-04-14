#include "fonctions.h"

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

/*int ProfondeurMax(noeud * tmp){
	int depth = -1;
	if (n != NULL) {
		if (deepestNode(n->lchild) > deepestNode(n->rchild)) {
			depth = deepestNode(n->lchild);
		}
		else
		{
			depth = deepestNode(n->rchild);
		}
		depth++;	
	}
	return depth;
}*/

int ValeurMax(noeud * tmp){

    int value = 0;

	if (tmp != NULL){
		
        value = tmp->data;
		
        if (tmp < ValeurMax(tmp->lchild)) {
			return ValeurMax(tmp->lchild);
		}
		else if (value < ValeurMax(tmp->rchild))
		{
			return ValeurMax(tmp->rchild);
		}
	}
	return(value);

}