#include <Arduino.h>
#include "BluetoothSerial.h"

// Crear una instancia de BluetoothSerial
BluetoothSerial SerialBT;

int contador = 0;

void setup() {
  
  // Inicia el puerto serial para depuración
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");// Nombre bluetooth
  Serial.println("Bluetooth iniciado. Nombre: ESP32_BT");
}

void loop() {
  if(contador <= 10){
    SerialBT.print("Contador:");
    SerialBT.println(contador);
    contador ++;
  }
  else{
    contador = 0;
  }
  delay(500);
}