#include <Arduino.h>

#define LED_PIN 2

void setup() {
pinMode(LED_PIN,OUTPUT);
Serial.begin(115200);
}

void loop() {
digitalWrite(LED_PIN, HIGH);
Serial.write("Encendido\n\r",11);
//Serial.println("LED on");
delay(1000);
digitalWrite(LED_PIN, LOW);
Serial.println("LED off");
delay(1000);
}