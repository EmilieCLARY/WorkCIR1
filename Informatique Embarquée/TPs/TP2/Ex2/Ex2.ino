// Include ISEN libraries

#include <ISEN.h>
#include <LabIsen-2009.h>
#include <ISL12026.h>
#include <MCP23X08.h>

// Include Arduino libraries
#include <LiquidCrystal.h>

  ISENLiquidCrystal lcd;

  int i=0;
  
void setup() {

  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(2), count, FALLING);

}

void loop() {

  lcd.setCursor(7,1);
  lcd.print(i);

}

void count() {
  i++;
}
