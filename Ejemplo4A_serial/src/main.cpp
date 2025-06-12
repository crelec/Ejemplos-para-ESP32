#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
int dato=65;

// Versión con String (objeto)
String mensajeStr = "Hola Serial";

// Versión con array de char (puntero)
const char* mensajeChar = "\nAdiós Serial";

// Buffer de ejemplo (bytes en hexadecimal)
uint8_t buffer1[] = {0x48, 0x6F, 0x6C, 0x61,0x0A}; // "Hola \n" en ASCII

// Parte de un string (solo los primeros 7 bytes)
const char* buffer2 = "Cesar Romero";

Serial.println("Caso Uno.");
Serial.println(dato);
Serial.write(dato); 

Serial.println("\nCaso Dos.");
Serial.write(mensajeStr.c_str()); // Envía la cadena sin conversión
Serial.write(mensajeChar); // Envía la cadena literal

Serial.println("\nCaso Tres.");
Serial.write(buffer1, sizeof(buffer1)); // Envía 5 bytes exactos
Serial.write(buffer2, 7); // Envía "Cesar R" 
Serial.write("\n........");
delay(1000);
}