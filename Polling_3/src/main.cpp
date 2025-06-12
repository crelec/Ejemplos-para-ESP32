#include <Arduino.h>

#define segA 23
#define segB 22
#define segC 21
#define segD 19
#define segE 18
#define segF 5
#define segG 17

const byte tabla[]={
 0b11000000, // 0 - ABCDEF (0), G (1)
  0b11111001, // 1 - BC (0)
  0b10100100, // 2 - ABGED (0)
  0b10110000, // 3 - ABGCD (0)
  0b10011001, // 4 - FBGC (0)
  0b10010010, // 5 - AFGCD (0)
  0b10000010, // 6 - AFGECD (0)
  0b11111000, // 7 - ABC (0)
  0b10000000, // 8 - Todos (0)
  0b10010000, // 9 - ABFGCD (0)
  0b10001000, // A - ABFGC (0)
  0b10000011, // b - FGECD (0)
  0b11000110, // C - AFED (0)
  0b10100001, // d - EGCD (0)
  0b10000110, // E - AFGED (0)
  0b10001110  // F - AFGE (0)
};

void Imprimir (int digito);

void setup() {
  pinMode(segA,OUTPUT);
  pinMode(segB,OUTPUT);
  pinMode(segC,OUTPUT);
  pinMode(segD,OUTPUT);
  pinMode(segE,OUTPUT);
  pinMode(segF,OUTPUT);
  pinMode(segG,OUTPUT);
}

int contador=0;

void loop() {
Imprimir(contador % 16);
delay(500);
contador ++;  
}

void Imprimir (int digito){

byte patron= tabla[digito];

digitalWrite(segA, patron & 0x01);
digitalWrite(segB, (patron>> 1) & 0x01);
digitalWrite(segC, (patron>> 2) & 0x01);
digitalWrite(segD, (patron>> 3) & 0x01);
digitalWrite(segE, (patron>> 4) & 0x01);
digitalWrite(segF, (patron>> 5) & 0x01);
digitalWrite(segG, (patron>> 6) & 0x01);
}