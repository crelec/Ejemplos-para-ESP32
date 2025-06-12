#include <Arduino.h>

#define segA 23
#define segB 22
#define segC 21
#define segD 19
#define segE 18
#define segF 5
#define segG 17

#define anod1 27 
#define anod2 26 
#define anod3 25 
#define anod4 33 

//Variables Globales
int contador = 1235;

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
};

// Prototipos de funciones
void mostrarNumero(int numero);
void encenderDisplay(int numDisplay);
void apagarDisplays();
void mostrarDigito(int digito);

void setup() {
  pinMode(segA,OUTPUT);
  pinMode(segB,OUTPUT);
  pinMode(segC,OUTPUT);
  pinMode(segD,OUTPUT);
  pinMode(segE,OUTPUT);
  pinMode(segF,OUTPUT);
  pinMode(segG,OUTPUT);
  pinMode(anod1,OUTPUT);
  pinMode(anod2,OUTPUT);
  pinMode(anod3,OUTPUT);
  pinMode(anod4,OUTPUT);

  apagarDisplays();
}

void loop() {

  // Mostrar el número en los displays
  mostrarNumero(contador);
}

void mostrarNumero(int numero) {
int digitos[4];

// Extraer cada dígito
digitos[3] = numero % 10; //int unidades
digitos[2] = (numero / 10) % 10; //int decenas
digitos[1] = (numero / 100) % 10;//int centenas
digitos[0] = numero / 1000; //int millares

// Mostrar cada dígito en su display correspondiente
for (int i = 0; i < 4; i++) {
  apagarDisplays();
  encenderDisplay(i);
  mostrarDigito(digitos[i]);
  delay(1000); //ojo tiempo presentacion
  }
}

void encenderDisplay(int numDisplay) {
  switch(numDisplay) {
    case 0: digitalWrite(anod1, HIGH); break; // Millares
    case 1: digitalWrite(anod2, HIGH); break; // Centenas
    case 2: digitalWrite(anod3, HIGH); break; // Decenas
    case 3: digitalWrite(anod4, HIGH); break; // Unidades
  }
}

void apagarDisplays() {
  digitalWrite(anod1, LOW);
  digitalWrite(anod2, LOW);
  digitalWrite(anod3, LOW);
  digitalWrite(anod4, LOW);
}

void mostrarDigito(int digito) {
  
  byte patron = tabla[digito];
  
  digitalWrite(segA, patron & 0X01);
  digitalWrite(segB, (patron>>1) & 0X01);
  digitalWrite(segC, (patron>>2) & 0X01);
  digitalWrite(segD, (patron>>3) & 0X01);
  digitalWrite(segE, (patron>>4) & 0X01);
  digitalWrite(segF, (patron>>5) & 0X01);
  digitalWrite(segG, (patron>>6) & 0X01);
}