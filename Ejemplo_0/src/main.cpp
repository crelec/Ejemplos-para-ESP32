#include <Arduino.h>

void setup() {
pinMode(2,OUTPUT);
Serial.begin(115200);
}

void loop() {
digitalWrite(2, HIGH);
Serial.write("Encendido\n\r",11);
//Serial.println("LED on");
delay(1000);
digitalWrite(2, LOW);
Serial.println("LED off");
delay(1000);
}