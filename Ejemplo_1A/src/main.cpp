#include <Arduino.h> 

// Declaración de las funciones de las tareas
void Task_Imprime1(void *parameter);
void Task_Imprime2(void *parameter);
void Task_ledParpadeo(void *parameter);

void setup(){
  Serial.begin(115200); // Inicializa la comunicación serie a 115200 baudios

  // Crea la tarea Task_Imprime1
  xTaskCreate(
    Task_Imprime1, // Función de la tarea
    "Imprime 1",   // Nombre de la tarea
    1024,          // Tamaño de la pila en palabras
    NULL,          // Parámetro de entrada
    1,             // Prioridad de la tarea
    NULL           // Puntero al manejador de la tarea
  );

  // Crea la tarea Task_Imprime2
  xTaskCreate(
    Task_Imprime2, // Función de la tarea
    "Imprime 2",   // Nombre de la tarea
    1024,          // Tamaño de la pila en palabras
    NULL,          // Parámetro de entrada
    1,             // Prioridad de la tarea
    NULL           // Puntero al manejador de la tarea
  );

  // Crea la tarea Task_ledParpadeo
  xTaskCreate(
    Task_ledParpadeo, // Función de la tarea
    "Parpadeo Led",   // Nombre de la tarea
    1024,             // Tamaño de la pila en palabras
    NULL,             // Parámetro de entrada
    1,                // Prioridad de la tarea
    NULL              // Puntero al manejador de la tarea
  );

  // Imprime un mensaje en el puerto serie
  Serial.write("Arranque el programa!.\n\r",24);
}

void loop() {
  // El loop está vacío ya que las tareas se ejecutan de manera independiente
}

void Task_Imprime1(void *parameter){
  while(true){
    Serial.write("Corre tarea 1!.\n\r",17); // Imprime un mensaje en el puerto serie
    vTaskDelay( 200 / portTICK_PERIOD_MS ); // Espera 200 ms
  }
}

void Task_Imprime2(void *parameter){
  while(true){
    Serial.write("Corre tarea 2!.\n\r",17); // Imprime un mensaje en el puerto serie
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // Espera 1000 ms
  }
}

void Task_ledParpadeo(void *parameter){
  pinMode(2,OUTPUT); // Configura el pin 2 como salida
  while(true){
    digitalWrite(2,HIGH); // Enciende el LED
    vTaskDelay( 1700 / portTICK_PERIOD_MS ); // Espera 1700 ms
    digitalWrite(2,LOW); // Apaga el LED
    vTaskDelay( 1700 / portTICK_PERIOD_MS ); // Espera 1700 ms
  }
}