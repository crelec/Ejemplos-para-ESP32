#include <Arduino.h>

int pin_out[] = {5, 17, 16, 4, 0, 2, 15};     // Pines conectados al display
int tabla[] = {254, 253, 251, 247, 239, 223, 191};  // Patrones para display de 7 segmentos
int i = 0;  // Índice del arreglo

const int botonAvanzar = 23;  // Botón para avanzar
const int botonRetroceder = 22;  // Botón para retroceder

bool estadoAnteriorAvanzar = HIGH;
bool estadoAnteriorRetroceder = HIGH;

// prototipos de funciones
void iniciar_out();
void escritura(int datoin);
void avanzar_o_retroceder();

void setup() {
  iniciar_out();
  escritura(255);  // Apagar todos los segmentos
  pinMode(botonAvanzar, INPUT_PULLUP);
  pinMode(botonRetroceder, INPUT_PULLUP);
}

void loop() {
  avanzar_o_retroceder();  // Control de recorrido según botón presionado
}

void iniciar_out() {
  for (int p = 0; p < 7; p++) {
    pinMode(pin_out[p], OUTPUT);
  }
}

void escritura(int datoin) {
  for (int a = 0; a < 7; a++) {
    digitalWrite(pin_out[a], bitRead(datoin, a));
  }
}

void avanzar_o_retroceder() {
  bool estadoActualAvanzar = digitalRead(botonAvanzar);
  bool estadoActualRetroceder = digitalRead(botonRetroceder);

  // Flanco de bajada para avanzar
  if (estadoAnteriorAvanzar == HIGH && estadoActualAvanzar == LOW) {
    i++;
    if (i >= 6) i = 0;
    escritura(tabla[i]);
    delay(300);  // Antirrebote básico
  }

  // Flanco de bajada para retroceder
  if (estadoAnteriorRetroceder == HIGH && estadoActualRetroceder == LOW) {
    i--;
    if (i < 0) i = 5;
    escritura(tabla[i]);
    delay(300);  // Antirrebote básico
  }

  estadoAnteriorAvanzar = estadoActualAvanzar;
  estadoAnteriorRetroceder = estadoActualRetroceder;
}
