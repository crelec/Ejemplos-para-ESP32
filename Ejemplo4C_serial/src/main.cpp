#include <Arduino.h>

#define D0 15
#define D1 2
#define D2 4
#define D3 16

// Variables para el control de tiempo
unsigned long Millis_Anterior = 0;
const unsigned long interval = 10;  // Intervalo en ms

void setup() {
  pinMode(D0,OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3,OUTPUT);
  Serial.begin(115200);
  
  // Estado inicial (todos los LEDs apagados)
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  Serial.println("Sistema iniciado. Esperando comando...");
  Serial.println("Enviar 'a' o 'd' para controlar LEDs");
}

byte ultimoComando = 0;  // Inicialmente no hay comando

void loop() {
  unsigned long Millis_Actual = millis();

  if (Millis_Actual - Millis_Anterior >= interval) {
    Millis_Anterior = Millis_Actual;

    if (Serial.available() > 0) {
      char dato = Serial.read(); // Lee un byte
  
      while(Serial.available() > 0) Serial.read(); //Limpio el buffer serial.

      if(dato=='a'){
        Serial.print("Recibido: ");
        Serial.println(dato);
        digitalWrite(D0, HIGH);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, HIGH);
        ultimoComando='a';
      }
      else if(dato=='d'){
      Serial.print("Recibido: ");
      Serial.println(dato);
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      ultimoComando='d';
      }
      else{
      Serial.println("Comando no valido. Use 'a' o 'd'");
    }
  }
  else{
    if(ultimoComando==0){
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
    }
  } 
}
}