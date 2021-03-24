#define LED_ROUGE 8
#define LED_ORANGE 9
#define LED_VERTE 2

void setup() {
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_ORANGE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);
}

void loop() {

  led(LED_VERTE, 5000);
  led(LED_ORANGE, 2000);
  led(LED_ROUGE, 5000);

}

void led(int led, int temps){
  digitalWrite(led, HIGH);
  delay(temps);
  digitalWrite(led, LOW);
}
