#include "tri.h"


int TriSelection(int *tab, int tabsize){

    int tmp;
    int index;


    for (int i=0; i < (tabsize-1); i++) {
      index = i;
    
      for (int j=i + 1; j < tabsize; j++) {
        
        if (tab[index] > tab[j])
          index = j;
          
      }
    
      if (index != i) {
        tmp = tab[i];
        tab[i] = tab[index];
        tab[index] = tmp;
      }
      
    }

    printf("Tableau trié par sélection ordinaire :\n");
    
    for (int k=0; k<tabsize; k++){
        printf("| ");
        printf("%d ", tab[k]);
    }
    printf("|");

    printf("\n\n");

}




int TriInsertionSequentiel(int *tab, int tabsize){

    int tmp;

    for (int i=1; i< tabsize; i++){
      if (tab[i]<tab[i-1]){

        int j=0;
        while (tab[j]< tab[i]){
          j++;
        }

        tmp = tab[j];

        for (int a=i-1; a>=j; a--){
          tab[a+1]=tab[a];
          tab[j]=tmp;

        }

      }
      

    }

    printf("Tableau trié par insertion séquentielle:\n");
    
    for (int k = 0; k < tabsize; k++){
        printf("| ");
        printf("%d ", tab[k]);
    }
    printf("|");

    printf("\n\n");


    
}
