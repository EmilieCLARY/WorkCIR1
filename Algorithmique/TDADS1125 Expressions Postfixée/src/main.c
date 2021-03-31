#include "piles.h"
#define _countof(array) (sizeof(array) / sizeof(array[0]))

int main ()
{

  Pile *tas;
  char *nom;

  int i = 0;
  char* chaine = "12 5  + 3 4 + *";
  char nb[20];
  int indice = 0;

  //Test
  if ((tas = (Pile *) malloc (sizeof (Pile))) == NULL)
    return -1;
  if ((nom = (char *) malloc (50 * sizeof (char))) == NULL)
    return -1;
  initialisation (tas);

    //Code du Pseudo Language
    for (int i = 0; i<strlen(chaine); i++){
        printf("%s", chaine[i]);
      if (chaine[i] <= '9' && chaine[i] >= '0'){
          nb[i] = chaine[i];
      }
      else{
          if (_countof(nb)>=1){
              atoi(nb);
              empiler(tas, nb);
          }
          int a = depiler(tas);
          int b = depiler(tas);
          int c;
          switch (chaine[i])
          {
          case '-' :
              c = a - b;
              break;
          
          case '+' :
              c = a + b;
              break;

          case '*' :
              c = a * b;
              break;

          case '/' :
              c = a / b;
              break;


          default:
              return(-1);
              break;
          }            
          empiler(tas, &c);

      }
    }

  affiche(tas);
  return 0;
}

//Traitement en Pseudo Language

/*
Traitement : 

    Pour i allant de 0 à size :
        Si le caractère ASCII entré est égal à celui d'un chiffre : 
        Alors :
            Place dans un tableau
        Fin Alors
        Sinon : Si tableau > 1
                    Transformation en entier
                    Empile
                Fin Si
                Si le caractère ASCII entré est égal à celui d'un opérateur :
                    
                Alors :
                    Dépile caractère[i] et caractère[i-1] / 2 fois
                    On applique l'opérateur a caractère[i] et caractère[i-1]
                    On empile le résultat dans la pile
                Fin Alors
                Sinon :
                    Retourne ERREUR
                Fin Sinon
                Fin Si
        Fin Sinon
        Fin Si
    Fin Pour

    Affiche la Pile



*/