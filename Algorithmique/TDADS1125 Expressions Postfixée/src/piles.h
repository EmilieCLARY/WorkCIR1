#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct ElementListe{
  char *donnee;
  struct ElementListe *suivant;
} Element;

typedef struct ListeRepere{
  Element *debut;
  int taille;
} Pile;


/* initialisation */
void initialisation (Pile *tas);

/* EMPILER*/
int empiler (Pile *tas, int *donnee);

/* DEPILER*/
int depiler (Pile *tas);

/* Affichage de élément en haut de la pile (LastInFirstOut) */
#define pile_donnee(tas)  tas->debut->donnee

/* Affiche la pile */
void affiche (Pile *tas);

/***********************\

 * pile_function.h     *
\***********************/

void initialisation (Pile * tas){
  tas->debut = NULL;
  tas->taille = 0;
}

/* empiler (ajouter) un élément dans la pile */
int empiler (Pile * tas, int *donnee){
  Element *nouveau_element;
  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
    return -1;
  if ((nouveau_element->donnee = (int *) malloc (50 * sizeof (int)))
      == NULL)
    return -1;
  strcpy (nouveau_element->donnee, donnee);
  nouveau_element->suivant = tas->debut;
  tas->debut = nouveau_element;
  tas->taille++;
}

/* depiler (supprimer un élément de la pile */
int depiler (Pile * tas){
  Element *supp_element;
  if (tas->taille == 0)
    return -1;
  supp_element = tas->debut;
  tas->debut = tas->debut->suivant;
  free (supp_element->donnee);
  free (supp_element);
  tas->taille--;
  return 0;
}

/* affichage de la pile */
void affiche (Pile * tas){
  Element *courant;
  int i;
  courant = tas->debut;

  for(i=0;i<tas->taille;++i){
    printf("\t\t%s\n", courant->donnee);
    courant = courant->suivant;
  }
}