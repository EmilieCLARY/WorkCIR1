#include <ISEN.h>
#include <math.h>
#include <LabIsen-2009.h>
#include <ISL12026.h>
#include <MCP23X08.h>
#include <LiquidCrystal.h>
#include <Wire.h>

IOstd io;
ISENLiquidCrystal lcd;


int tab[8];
int n;
int p;


void setup(){
    lcd.begin(16,2);
    lcd.clear();
    io.begin();
    io.clear();
    for (int i = 0; i < 8; i++)
    {
        tab[i]=0;
    }
    
}

int puissance(int nombre, int puissance) {
    int result = 1;
    if (puissance==0) return 1;
     for (int i = 1; i <= puissance; i++)
     {
         result *= nombre;
     }
    return result;
}


int deci(int tab[], int len){
    int resultat = 0;
    for (int i = 0; i < len ; i++)
    {
        p=7-i;
        resultat += tab[i] * puissance(2,p);
    }
    return resultat;
}


void loop(){
  
    for(int i=5 ; i<=12 ; i++){

            if (io.digitalRead(i)==LOW) {
                if (tab[12-i]== 1) {
                    tab[12-i] = 0;
                    io.digitalWrite(i, LOW);
                    delay(200);
                    }
                    
                else {
                    tab[12-i]=1;
                    io.digitalWrite(i,HIGH);
                    delay(200);
                }
            }
            lcd.clear();

            for (int i=2; i<10; i++){
              lcd.setCursor(i, 0);
              lcd.print(tab[i-2]);
            }
              
            lcd.setCursor(10,0);
            lcd.print(" = ");
            lcd.print(deci(tab,8));
            
            delay(20);
        }
    }
