#include <Arduino.h>

#define LED_PIN 15
#define BUTTON_PIN 2

void setup() {
  pinMode(LED_PIN,OUTPUT);
  pinMode(2,INPUT);
}

void loop() {
  if(digitalRead(BUTTON_PIN)){
    digitalWrite(LED_PIN,LOW); 
  }
  else
  digitalWrite(LED_PIN,HIGH);
  delay(300);
  digitalWrite(LED_PIN,LOW); 
  delay(300);
}
