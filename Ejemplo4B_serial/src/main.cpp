#include <Arduino.h>

#define D0 15
#define bt1 2

int contador=0;
bool estadoAnterior= HIGH;
unsigned long ultimoTiempoRebote = 0;
const unsigned long tiempoDebounce = 50; // ms para antirrebote

void setup() {
  pinMode(D0,OUTPUT);
  pinMode(bt1,INPUT);
  Serial.begin(115200);
  Serial.println("Sistema iniciado. Esperando pulsaciones...");
}

void loop() {
  bool estadoActual = digitalRead(bt1);
  unsigned long tiempoActual = millis();

  if(estadoActual ==LOW && estadoAnterior == HIGH && tiempoActual-ultimoTiempoRebote > tiempoDebounce){
  ultimoTiempoRebote=tiempoActual;
  contador++;
  digitalWrite(D0,HIGH);
  Serial.print("Pulsacion Detectada. Contador: ");
  Serial.println(contador);
}
  else{
  digitalWrite(D0,LOW);
  }
  estadoAnterior=estadoActual;
  delay(10); //OJO NO
}