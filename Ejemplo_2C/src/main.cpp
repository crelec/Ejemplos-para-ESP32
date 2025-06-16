#include <Arduino.h>

// Definición de pines para el Motor A
int IN1 = 15; 
int IN2 = 2; 

// Definición de pines para el Motor B
int IN3 = 4;
int IN4 = 16;

void Task_Serial1(void *parameter);

void setup() {
  // Inicializa la comunicación serial a 115200 baudios
  Serial.begin(115200);
  
  // Configura los pines de los motores como salidas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Crea una tarea para la comunicación serial
  xTaskCreate(
    Task_Serial1,  // Función de la tarea
    "Serial 1",    // Nombre de la tarea
    1024,          // Tamaño de la pila
    NULL,          // Parámetro de la tarea
    1,             // Prioridad de la tarea
    NULL           // Identificador de la tarea
  );
  Serial.println("Iniciando...:");
}

void loop() {
  // Código principal que se ejecuta repetidamente
}

// Función de la tarea para la comunicación serial
void Task_Serial1(void *parameter){
  String dato;

  // Bucle infinito de la tarea
  while(true){
    if(Serial.available()>0){
      // Lee la palabra de la comunicación serial
      dato = Serial.readStringUntil('\n');
      
      // Convierte la palabra a minúscula
      dato.toLowerCase();

      // Verifica la palabra y realiza la acción correspondiente
      if (dato == "izquierda") {
        // Motor A hacia adelante
        digitalWrite(IN1, HIGH);       
        digitalWrite(IN2, LOW); 
        // Motor B detenido
        digitalWrite(IN3, LOW);  
        digitalWrite(IN4, LOW);
        Serial.println("izquierda");
      } else if (dato == "derecha") {
        // Motor A detenido
        digitalWrite(IN1, LOW);       
        digitalWrite(IN2, LOW); 
        // Motor B hacia adelante
        digitalWrite(IN3, HIGH);  
        digitalWrite(IN4, LOW);
        Serial.println("derecha");
      } else if (dato == "arriba") {
        // Motor A hacia adelante
        digitalWrite(IN1, HIGH);       
        digitalWrite(IN2, LOW); 
        // Motor B hacia adelante
        digitalWrite(IN3, HIGH);  
        digitalWrite(IN4, LOW);       
        Serial.println("arriba");
      } else if (dato == "abajo") {
        // Motor A hacia atrás
        digitalWrite(IN1, LOW);       
        digitalWrite(IN2, HIGH); 
        // Motor B hacia atrás
        digitalWrite(IN3, LOW);  
        digitalWrite(IN4, HIGH);     
        Serial.println("abajo");
      } else {
        // Ambos motores detenidos
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);    
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, LOW);
        Serial.println("detener");
      }
    }
    // Retrasa la tarea 200 milisegundos
    vTaskDelay( 200 / portTICK_PERIOD_MS );
  }
}