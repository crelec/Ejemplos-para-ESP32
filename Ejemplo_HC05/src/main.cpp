#include <Arduino.h>

// Definir los pines de conexión
const int trigPin = 5;  // Pin de trigger
const int echoPin = 18; // Pin de echo

// Variable compartida para almacenar la distancia medida
volatile float distance = 0.0;

// Tarea para leer el sensor de distancia
void TareaDistancia(void *parameter) {
  while (1) {
    // Limpiar el pin de trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Enviar un pulso de 10 microsegundos al pin de trigger
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Leer el tiempo que tarda en llegar el eco
    long duration = pulseIn(echoPin, HIGH);

    // Calcular la distancia en centímetros
    distance = duration * 0.0343 / 2; // Actualizar la distancia

    // Esperar antes de la siguiente medición (100 ms)
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

// Tarea para imprimir la distancia por UART
void TareaImpresion(void *parameter) {
  while (1) {
    // Leer la distancia y mostrarla en el monitor serial
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Esperar antes de la siguiente impresión (500 ms)
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void setup() {
  // Iniciar la comunicación serial
  Serial.begin(115200);

  // Configurar los pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Crear las tareas de FreeRTOS
  xTaskCreate(
    TareaDistancia,   // Función de la tarea
    "Lee Distancia",    // Nombre de la tarea
    2048,               // Tamaño de la pila
    NULL,               // Parámetros de la tarea
    1,                  // Prioridad de la tarea
    NULL                // Handle de la tarea
  );

  xTaskCreate(
    TareaImpresion,  // Función de la tarea
    "Imprime Distancia",   // Nombre de la tarea
    2048,               // Tamaño de la pila
    NULL,               // Parámetros de la tarea
    1,                  // Prioridad de la tarea
    NULL                // Handle de la tarea
  );
}

void loop() {
  
}
