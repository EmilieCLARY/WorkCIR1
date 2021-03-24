#define LED_ROUGE  8
#define LED_ORANGE 9
#define LED_VERTE  2


void setup(){
  
  //Définir les LEDs avec les bonnes entrées
  pinMode(LED_ROUGE,OUTPUT);
  pinMode(LED_ORANGE,OUTPUT);
  pinMode(LED_VERTE,OUTPUT);
}


void loop() {

  clignotant(LED_ORANGE, 500, 500, 5);

  digitalWrite(LED_ORANGE,HIGH);
  delay(2000);
  digitalWrite(LED_ORANGE,LOW);


  digitalWrite(LED_ROUGE,HIGH);
  delay(5000);
  digitalWrite(LED_ROUGE,LOW);

}

void clignotant(int led, int tempson, int tempsoff, int nbcycle){
  for (i=0; i<nbcycle; i++) {
    digitalWrite(led,HIGH);
    delay(tempson);
    digitalWrite(LED_ORANGE,LOW);
    delay(tempsoff);
  }
  
}
