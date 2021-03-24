 
// Include ISEN libraries

  #include <ISEN.h>
  #include <LabIsen-2009.h>
  #include <ISL12026.h>
  #include <MCP23X08.h>

// Include Arduino librariess

  #include <Wire.h>
  #include <LiquidCrystal.h>

  ISENLiquidCrystal lcd;
  IOstd io;

int value=0;
int analogPin = A3;

void setup() {

lcd.begin(16,2);

}

void loop() {

  //Cela va de 0 à 1023

  lcd.setCursor(2,0);

  value=analogRead(analogPin);
  value=value/204,6;
  lcd.setCursor(2,0);
  lcd.print(value);

  delay(50);

  lcd.clear();
  lcd.setCursor(2,0);

  for (int i=1; i<=value; i++){
    lcd.setCursor(i-1, 1);
    lcd.print("=");
  }

  

  
}
