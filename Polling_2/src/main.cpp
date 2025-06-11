#include <Arduino.h>

#define D0 15
#define D1 2
#define D2 4
#define D3 16
#define BT1 22

void setup() {
  pinMode(D0,OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(BT1, INPUT);
  Serial.begin(115200);
}

int contador=0;
int anterior_boton=1;
int nuevo_boton;

void loop() {
nuevo_boton = digitalRead(BT1);
  if ((nuevo_boton==0) && (anterior_boton==1)) contador++;
    digitalWrite(D0,contador & 0x01); 
    digitalWrite(D1,(contador >>1) & 0x01);
    digitalWrite(D2,(contador >>2) & 0x01); 
    digitalWrite(D3,(contador >>3)& 0x01); 
    Serial.println(contador);
    anterior_boton = nuevo_boton; 
    delay(300); // OJO NO 
}