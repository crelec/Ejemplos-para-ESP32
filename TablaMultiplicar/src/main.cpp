#include <Arduino.h>

// Definición de pines de entrada
const int pinD2 = 15; // LSB
const int pinD3 = 2;
const int pinD4 = 4;
const int pinD5 = 16; // MSB

int cuenta = 1;
int numeroAnterior = -1;
char mensaje[40] = {0};

void setup() {
  pinMode(pinD2, INPUT);
  pinMode(pinD3, INPUT);
  pinMode(pinD4, INPUT);
  pinMode(pinD5, INPUT);

  Serial.begin(115200);
  Serial.write("Lectura de número binario desde interruptores...\r\n", 51);
}

void loop() {
  int bit0 = !digitalRead(pinD2);
  int bit1 = !digitalRead(pinD3);
  int bit2 = !digitalRead(pinD4);
  int bit3 = !digitalRead(pinD5);

  int numero = (bit3 << 3) | (bit2 << 2) | (bit1 << 1) | bit0;

  if (numero != numeroAnterior) {
    numeroAnterior = numero;
    cuenta = 1;
    
    memset(mensaje, 0, sizeof(mensaje));
    int len = snprintf(mensaje, sizeof(mensaje), "Numero Ingresado: %d\r\n", numero);
    Serial.write(mensaje, len);

    if (numero == 0) {
      Serial.write("El numero ingresado es 0. No se imprime la tabla.\r\n", 52);
    } else {
      Serial.write("Tabla de multiplicar:\r\n", 23);
    }
  }

  if ((cuenta < 11) && (numero > 0)) {
    memset(mensaje, 0, sizeof(mensaje));
    int len = snprintf(mensaje, sizeof(mensaje), "%d x %d = %d\r\n", numero, cuenta, numero * cuenta);
    Serial.write(mensaje, len);
    cuenta++;
  } else {
    delay(300);
  }
}
/*
snprintf() => devuelve el número de caracteres escritos (excluyendo el null-terminator)
memset() => Limpiar el buffer
*/