#include <Arduino.h>

// Declaración de la tarea Serial1
void Task_Serial1(void *parameter);

void setup() {
  // Inicialización de la comunicación serial
  Serial.begin(115200);
  // Configuración del pin 4 como entrada
  pinMode(4, INPUT);
  // Configuración del pin 2 como salida
  pinMode(2, OUTPUT);

  // Creación de la tarea Serial1
  xTaskCreate(
    Task_Serial1,  // Función de la tarea
    "Serial 1",    // Nombre de la tarea
    1024,          // Tamaño de la pila
    NULL,          // Parámetro de la tarea
    1,             // Prioridad de la tarea
    NULL           // Puntero al manejador de la tarea
  );
}

void loop() {
  // Bucle vacío
}

void Task_Serial1(void *parameter) {
  while (true) {
    // Lectura del estado del botón
    int estadoBoton = digitalRead(4);

    if (estadoBoton == HIGH) {
      // Si el botón no está presionado, enviar "Apagado" y apagar el LED
      Serial.write("Apagado  \n\r", 11);
      digitalWrite(2, LOW);
    } else {
      // Si el botón está presionado, enviar "Encendido" y encender el LED
      Serial.write("Encendido\n\r", 11);
      digitalWrite(2, HIGH);
    }
    // Retraso de 250 ms
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}
