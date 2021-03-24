// Include ISEN libraries

#include <ISEN.h>
#include <LabIsen-2009.h>
#include <ISL12026.h>
#include <MCP23X08.h>

// Include Arduino libraries
#include <LiquidCrystal.h>

  ISENLiquidCrystal lcd;

void setup() {
  lcd.begin(16,2);

}

void loop() {
  lcd.setCursor(3,0);
  lcd.print("Hello");
  lcd.setCursor(3,1);
  lcd.print("World !");

  //Cela appartient à la catégorie de langage du C++
  
}
