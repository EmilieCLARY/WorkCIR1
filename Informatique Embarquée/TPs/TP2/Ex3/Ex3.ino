#define LED_ROUGE 8
#define LED_ORANGE 9
#define LED_VERTE  2

#include <ISEN.h> 
#include <LabIsen-2009.h> 
#include <ISL12026.h> 
#include <MCP23X08.h> 

#include <LiquidCrystal.h>
ISENLiquidCrystal lcd;


int SS1=0;
int SS2=0;
int MM1=0;
int MM2=0;
int HH1=0;
int HH2=0;
int C=0;
int boucle2=1;

void change() {
  lcd.clear();
     lcd.print(HH1);
     lcd.print(HH2);
     lcd.print(":");
     lcd.print(MM1);
     lcd.print(MM2);
     lcd.print(":");
     lcd.print(SS1);
     lcd.print(SS2);
     lcd.print(":");
     lcd.print(C);


}

void setup() {
  pinMode(LED_ROUGE, INPUT);
  pinMode(LED_ORANGE, INPUT);
  pinMode(LED_VERTE, INPUT);



  attachInterrupt(digitalPinToInterrupt(2), debut, FALLING);


    lcd.clear();
    lcd.begin(16,2);
}

void debut(){

  boucle2=1;
}

void arret(){
  boucle2=0;

}

void zero(){
  SS1=0;
  SS2=0;
  MM1=0;
  MM2=0;
  HH1=0;
  HH2=0;
  C=0;
}


void loop() {

  while (boucle2 == 1){
    
    C++;
    
    if (C == 10){
      C = 0;
      SS2++;
    }
    
    if (SS2 == 10){
      SS2 = 0;
      SS1++;
    }
    
    if (SS1 == 6){
      SS1 = 0;
      MM2++;
    }
    
    if (MM2 == 10){
      MM2 = 0;
      MM1++;
    }
    
    if (MM1 == 6){
      MM1 = 0;
      HH2++;
    }
    
    if (HH2 == 10){
      HH2 = 0;
      HH1++;
      
    }

    if (HH2 == 2 && HH1 == 4){
      zero();
    }
    
    delay(100);
    change();

    if(digitalRead(9) == LOW){
      arret();
    }
    
    if(digitalRead(8) == LOW){
      zero();
    }
    
  }



}
