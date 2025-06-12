#include <Arduino.h>

#define D0 15
#define D1 2
#define D2 4
#define D3 16

// Buffer para recepción de comandos
const byte TAM_BUFFER = 20;
char buffer[TAM_BUFFER];
String comandoRecibido = "";
String ultimoEstadoValido = "";

// Temporización
unsigned long Millis_Anterior = 0;
const unsigned long interval = 10;

//Prototipos de funciones
void procesarComando(char* datos);
void resetLEDs(); 
  
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  resetLEDs();
  Serial.println("Sistema iniciado. Envie 'adelante' o 'atras'...");
}

void loop() {
  unsigned long Millis_Actual = millis();
  
  if (Millis_Actual - Millis_Anterior >= interval) {
    Millis_Anterior = Millis_Actual;
    
    if (Serial.available() > 0) {
      // Limpiar buffer y variables
      memset(buffer, 0, TAM_BUFFER); //función de la biblioteca estándar de C (<string.h>) que se utiliza para llenar un bloque de memoria con un valor específico.
      comandoRecibido = "";
      
      // Leer datos disponibles
      size_t bytesLeidos = Serial.readBytesUntil('\n', buffer, TAM_BUFFER-1);
      
      if (bytesLeidos > 0) {
        procesarComando(buffer);
      }
    }
  }
}

void procesarComando(char* datos) {
  comandoRecibido = String(datos);
  comandoRecibido.toLowerCase();
  comandoRecibido.trim(); //método de la clase String en Arduino que se utiliza para eliminar espacios en blanco y otros caracteres de control del inicio y final de una cadena de texto.
  
  if (comandoRecibido == "adelante") {
    Serial.println("Modo: Adelante");
    digitalWrite(D0, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    ultimoEstadoValido = "adelante";
  } 
  else if (comandoRecibido == "atras") {
    Serial.println("Modo: Atras");
    digitalWrite(D0, LOW);
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    ultimoEstadoValido = "atras";
  }
  else if (ultimoEstadoValido == "") {
    resetLEDs();
  }
}

void resetLEDs() {
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
}