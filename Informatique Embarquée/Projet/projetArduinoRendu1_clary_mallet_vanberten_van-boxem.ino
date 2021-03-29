#include <ISEN.h> 
#include <LabIsen-2009.h> 
#include <ISL12026.h> 
#include <MCP23X08.h> 

#include <LiquidCrystal.h>
ISENLiquidCrystal lcd;

#define LED_ROUGE  8

bool etat = false;
bool etat_menu = true;
bool etat_lanceur = false;
int i = 0;

void interrupt(){
  i++;
  etat = true;
  etat_menu = false;
  if(i<=1){
    etat_lanceur = true;  
  }
}


int chemin[16] = {0};


/*******************************************/
/*            Fonction de saut             */
/*******************************************/

void saut(){
  
  lcd.setCursor(2,1);
  lcd.write(2);
  delay(300);
  lcd.setCursor(2,1);
  lcd.write(3);
  delay(300);
  lcd.setCursor(2,1);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.write(5);
  delay(300);
  lcd.setCursor(2,1);
  lcd.write(6);
  lcd.setCursor(2,0);
  lcd.write(1);
}


/*******************************************/
/*            Fonction de chute            */
/*******************************************/

void chute() {

  delay(300);
  lcd.setCursor(2,0);
  lcd.write(3);
  delay(300);
  lcd.setCursor(2,0);
  lcd.write(5);
  lcd.setCursor(2,1);
  lcd.write(4);
  delay(300);
  lcd.setCursor(2,0);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.write(2);
  delay(300);
  lcd.setCursor(2,1);
  lcd.write(1);
  delay(300);
}


void setup() {
  
  lcd.begin(16,2);

//Différents états du personnage
  byte smiley1[8]={B01100, B01100, B00000, B01110, B11100, B01100, B11010, B10011};
  byte smiley2[8]={B01100, B01100, B00000, B01100, B01100, B01100, B01100, B01110};
  byte smiley3[8]={B01100, B01100, B00000, B11110, B01101, B11111, B10000, B00000};
  byte smiley4[8]={B11110, B01101, B11111, B10000, B00000, B00000, B00000, B00000};
  byte smiley5[8]={B00000, B00000, B00000, B00000, B00000, B01100, B01100, B00000};
  byte smiley6[8]={B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};

//Fourche
  byte ennemi1[8]={B10101, B10101, B11111, B00100, B00100, B00100, B00100, B00100};
//Tour
  byte ennemi2[8]={B10101, B10101, B11111, B01110, B01010, B01010, B01110, B01110};

  lcd.createChar(1, smiley1);
  lcd.createChar(2, smiley2);
  lcd.createChar(3, smiley3);
  lcd.createChar(4, smiley4);
  lcd.createChar(5, smiley5);
  lcd.createChar(6, smiley6);
  
  lcd.createChar(7, ennemi1);
  lcd.createChar(8, ennemi2);

  attachInterrupt(digitalPinToInterrupt(2), interrupt, FALLING);
  pinMode(LED_ROUGE,OUTPUT);
}


/**********************************************************************/
/*                   Création et affichage du menu                    */
/**********************************************************************/

void menu(void) {
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AREA's Runner ");
  lcd.setCursor(4, 1);
  lcd.print("Start");

  //Saut
  
  lcd.setCursor(14,1);
  lcd.write(2);
  delay(300);
  lcd.setCursor(14,1);
  lcd.write(3);
  delay(300);
  lcd.setCursor(14,1);
  lcd.write(4);
  lcd.setCursor(14,0);
  lcd.write(5);
  delay(300);
  lcd.setCursor(14,1);
  lcd.write(6);
  lcd.setCursor(14,0);
  lcd.write(1);

  //Chute

  delay(300);
  lcd.setCursor(14,0);
  lcd.write(3);
  delay(300);
  lcd.setCursor(14,0);
  lcd.write(5);
  lcd.setCursor(14,1);
  lcd.write(4);
  delay(300);
  lcd.setCursor(14,0);
  lcd.write(6);
  lcd.setCursor(14,1);
  lcd.write(2);
  delay(300);
  lcd.setCursor(14,1);
  lcd.write(1);
  delay(300);
}

// Fonction pour afficher successivement 3 points avec délai.

void points(){
  for (int i = 0; i < 4; i++){
    lcd.setCursor(7 + i, 1);
    lcd.print(".");
    delay(200);
  }
}


void loop() {
  while (etat_menu) {
    menu();
  };

  if(etat_lanceur==true){
    lcd.clear();
    
    lcd.setCursor(8,0);
    lcd.print("3");
    points();
  
    lcd.clear();
    
    lcd.setCursor(8,0);
    lcd.print("2");
    points();
  
    lcd.clear();
    
    lcd.setCursor(8,0);
    lcd.print("1");
    points();
  
    lcd.clear();
    etat_lanceur=false;
  }

  lcd.clear();

 
  lcd.setCursor(2,1);
  
  lcd.write(1);
  delay(300);
  
  lcd.setCursor(2,1);
  lcd.write(2);
  delay(300);
  
  obstacle (chemin, 16);

  if (etat == true) {
    saut();

    chute();
    etat = false;
  }
}

/**********************************************************************/
/*  Gestion du tableau concernant les obstacles et affichage          */
/**********************************************************************/

void ennemi_string (int placement, int valeur) {
  lcd.setCursor(placement, 1);
  switch (valeur) {
    case 1 :
      lcd.write(7);
    case 2 :
      lcd.write(8);
  }
}

void obstacle (int tab[], int screen) {
  int ennemis = 0;
  for (size_t i = 0; i < screen; i++) { // Pour le nombre de case dans le tableau
    tab[i] = tab[i + 1];
    ennemis = random(5);    // Nombre aléatoire entre 0  à 5
    if (ennemis <= 1) {     // Si le nombre aléatoire est plus petit que 3
      tab[screen - 1] = ennemis + 1;  // Ajouter un ennemi au tableau
    } else {                // Sinon :
      tab[screen - 1] = 0;  // Ne pas ajouter d'ennemi
    }
  }

  for (size_t i = 0; i < screen; i++) {
    lcd.setCursor(i,1);
    if (chemin[i] != 0) ennemi_string(i, tab[i]);
    else lcd.write(" ");
  }
}


