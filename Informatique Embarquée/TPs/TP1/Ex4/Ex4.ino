#define LED_ROUGE  8
#define BOUTON_ORANGE 9
#define LED_VERTE  2
#define LED_BLEUE 3

void setup(){
  pinMode(LED_ROUGE,OUTPUT);    //Configuration de la sortie
  pinMode(BUTTON_ORANGE,INPUT);
  pinMode(LED_VERTE,OUTPUT);
  pinMode(LED_BLEUE,OUTPUT);
}

void sequence(bool sens){
  
  if(sens == HIGH){
    digitalWrite(LED_BLEUE,HIGH);
    delay(500);
    digitalWrite(LED_BLEUE,LOW);
    digitalWrite(LED_VERTE,HIGH);
    delay(500);
    digitalWrite(LED_VERTE,LOW);
    digitalWrite(LED_ROUGE,HIGH);
    delay(500);
    digitalWrite(LED_ROUGE,LOW);
  }
  
  else{
    digitalWrite(LED_ROUGE,HIGH);
    delay(500);
    digitalWrite(LED_ROUGE,LOW);
    digitalWrite(LED_VERTE,HIGH);
    delay(500);
    digitalWrite(LED_VERTE,LOW);
    digitalWrite(LED_BLEUE,HIGH);
    delay(500);
    digitalWrite(LED_BLEUE,LOW);
  }
}

bool var = 0;
void loop(){
  if(digitalRead(BUTTON_ORANGE)==LOW){
    var = !var;
    
  }
  sequence(var);
 }
