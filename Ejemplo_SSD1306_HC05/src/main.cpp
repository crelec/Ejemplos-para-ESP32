#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definiciones para el display SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // Dirección I2C del display SSD1306

// Definir los pines de conexión para el sensor HC-SR04
const int trigPin = 5;  // Pin de trigger
const int echoPin = 18; // Pin de echo

// Variable compartida para almacenar la distancia medida
volatile float distance = 0.0;

// Crear objeto display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

// Tarea para mostrar la distancia en el display SSD1306
void TareaDisplay(void *parameter) {
  while (1) {
    // Limpiar el display
    display.clearDisplay();

    // Mostrar el título
    display.setCursor(10, 0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.print("Distancia");

    // Mostrar la distancia medida
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.print(distance);
    display.print(" cm");

    // Actualizar el display
    display.display();

    // Esperar antes de la siguiente actualización (200 ms)
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void setup() {
  // Iniciar la comunicación serial
  Serial.begin(115200);

  // Configurar los pines del sensor HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializar el display SSD1306
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Detener la ejecución si no se puede inicializar el display
  }
  display.display();
  delay(2000);  // Pausa para mostrar el logo de Adafruit (opcional)
  display.clearDisplay();

  // Crear las tareas de FreeRTOS
  xTaskCreate(
    TareaDistancia,   // Función de la tarea
    "Lee Distancia",  // Nombre de la tarea
    2048,             // Tamaño de la pila
    NULL,             // Parámetros de la tarea
    1,                // Prioridad de la tarea
    NULL              // Handle de la tarea
  );

  xTaskCreate(
    TareaDisplay,     // Función de la tarea
    "Muestra Display",// Nombre de la tarea
    4096,             // Tamaño de la pila (mayor para gráficos)
    NULL,             // Parámetros de la tarea
    1,                // Prioridad de la tarea
    NULL              // Handle de la tarea
  );
}

void loop() {
  // El loop está vacío porque las tareas se ejecutan en paralelo
}