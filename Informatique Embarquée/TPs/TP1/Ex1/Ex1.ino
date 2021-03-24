#define LED_ROUGE  8
#define LED_ORANGE 9
#define LED_VERTE  2


void setup(){
  
  //Définir les LEDs avec les bonnes entrées
  pinMode(LED_ROUGE,OUTPUT);
  pinMode(LED_ORANGE,OUTPUT);
  pinMode(LED_VERTE,OUTPUT);
}

void loop(){
  
  //Allumer les LEDs
  digitalWrite(LED_ROUGE,HIGH);
  digitalWrite(LED_ORANGE,HIGH);
  digitalWrite(LED_VERTE,HIGH);
  
  //Attendre 1000ms
  delay(1000);
  
  //Eteindre les LEDs
  digitalWrite(LED_ROUGE,LOW);
  digitalWrite(LED_ORANGE,LOW);
  digitalWrite(LED_VERTE,LOW);
  
  //Attendre 1000ms
  delay(1000);
 }
