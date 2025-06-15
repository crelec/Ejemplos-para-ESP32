#include <Arduino.h>

// Declaración de la función de la tarea
void Task_Serial1(void *parameter);

// Configuración inicial
void setup() {

  // Inicializa la comunicación serial a 115200 baudios
  Serial.begin(115200);

  // Crea una tarea para la comunicación serial
  xTaskCreate(
    Task_Serial1,  // Función de la tarea
    "Serial 1",    // Nombre de la tarea
    1024,          // Tamaño de la pila
    NULL,          // Parámetro de la tarea
    1,             // Prioridad de la tarea
    NULL           // Identificador de la tarea
  );

}

// Bucle principal
void loop() {
  // El bucle principal está vacío
}

// Función de la tarea para la comunicación serial
void Task_Serial1(void *parameter){

  // Inicializa el contador
  int contador=0;
  // Buffer para el mensaje
  char mensaje[20]={0};

  // Bucle infinito de la tarea
  while(true){
  
    // Si el contador es menor o igual a 10
    if(contador<=10)
    {
      // Formatea el mensaje con el valor del contador
      sprintf(mensaje,"Contador:%d\n\r",contador);
      // Envía el mensaje por el puerto serial
      Serial.write(mensaje,strlen(mensaje));
      // Incrementa el contador
      contador++;
    }
    else
    {
      // Reinicia el contador
      contador=0;
    }
    // Retrasa la tarea 500 milisegundos
    vTaskDelay( 500 / portTICK_PERIOD_MS );
  }
}
