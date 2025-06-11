#include <Arduino.h>

const int ledPin1 = 2;
const int ledPin2 = 5;

void Task_blinkLED1(void *parameter);
void Task_blinkLED2(void *parameter);

void setup() {
  // Inicializar el puerto serie
  Serial.begin(115200);
  Serial.println("Iniciando...!");

  // Crear tareas para parpadear los LEDs
  xTaskCreate(
    Task_blinkLED1,   // Función de la tarea
    "Blink LED 1",    // Nombre de la tarea
    1024,             // Tamaño de la pila en palabras
    NULL,             // Parámetro de entrada
    1,                // Prioridad de la tarea
    NULL              // Manejador de la tarea
  );

  xTaskCreate(
    Task_blinkLED2,   // Función de la tarea
    "Blink LED 2",    // Nombre de la tarea
    1024,             // Tamaño de la pila en palabras
    NULL,             // Parámetro de entrada
    1,                // Prioridad de la tarea
    NULL              // Manejador de la tarea
  );
}

void loop() {
  // El bucle principal está vacío porque las tareas se ejecutan en paralelo
}

void Task_blinkLED1(void *parameter) {
  // Configurar el pin del LED como salida
  pinMode(ledPin1, OUTPUT);

  while (true) {
    // Encender el LED
    digitalWrite(ledPin1, HIGH);
    // Esperar 500 ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
    // Apagar el LED
    digitalWrite(ledPin1, LOW);
    // Esperar 500 ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void Task_blinkLED2(void *parameter) {
  // Configurar el pin del LED como salida
  pinMode(ledPin2, OUTPUT);

  while (true) {
    // Encender el LED
    digitalWrite(ledPin2, HIGH);
    // Esperar 2000 ms
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    // Apagar el LED
    digitalWrite(ledPin2, LOW);
    // Esperar 2000 ms
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

//Una tarea sin vTaskDelay()
// nunca pasa a estado Blocked, por lo que no permite que tareas de menor prioridad se ejecuten.