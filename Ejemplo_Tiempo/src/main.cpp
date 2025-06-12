#include <Arduino.h>

unsigned long prevMillis = 0;
unsigned long prevMicros = 0;
const long intervalMillis = 1000;  // Intervalo objetivo: 1000 ms (1 segundo)
const unsigned int intervalMicros = 500000;  // 500000 Intervalo objetivo: 500 ms 
                                            // OJO Mostrar problema para 10000 objetivo 10ms
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Iniciando...: ");
}

void loop() {
  // 1. Temporización con millis() (mide el tiempo REAL transcurrido)
  unsigned long MillisActual = millis();
  if (MillisActual - prevMillis >= intervalMillis) {
    unsigned long MillisCalculado = MillisActual - prevMillis;  // Tiempo real medido
    prevMillis = MillisActual;  // Reiniciamos el contador

    Serial.print("Intervalo real MILLIS: ");
    Serial.print(MillisCalculado);
    Serial.println(" ms");

    // Opcional: Parpadear LED cada segundo
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  // 2. Temporización con micros() (mide el tiempo REAL transcurrido)
  unsigned long MicrosActual = micros();
  if (MicrosActual - prevMicros >= intervalMicros) {
    unsigned long MicrosCalculado = MicrosActual - prevMicros;  // Tiempo real medido
    prevMicros = MicrosActual;  // Reiniciamos el contador

    Serial.print("Intervalo real MICROS: ");
    Serial.print(MicrosCalculado);
    Serial.println(" μs");
  }
}