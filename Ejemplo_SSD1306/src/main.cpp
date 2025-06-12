#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definiciones para el display SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // Dirección I2C del display SSD1306

// Crear objeto display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variable para el contador
int contador = 0;

// Tarea periódica para incrementar el contador
void tareaContador(void * parameter) {
  while (1) {
    if (contador < 10) {
      contador++;
    } else {
      contador = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(500));  // Esperar 500ms
  }
}

// Tarea periódica para actualizar el display
void tareaDisplay(void * parameter) {
  while (1) {
    display.clearDisplay();
    display.setCursor(10, 0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.print("Contador");
    display.setCursor(50, 30);
    display.setTextSize(3);
    display.print(contador);
    display.display();
    vTaskDelay(pdMS_TO_TICKS(100));  // Esperar 100ms
  }
}

void setup() {
  // Inicializar el display SSD1306
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Detener la ejecución si no se puede inicializar el display
  }
  display.display();
  delay(2000);  // Pausa para mostrar el logo de Adafruit (opcional)
  display.clearDisplay();

// Mostrar el valor inicial del contador (0) antes de iniciar las tareas (opcional)
 /* display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.print("Contador:");
  display.setCursor(0, 30);
  display.setTextSize(3);
  display.print(contador);
  display.display();
*/

  // Crear tareas de FreeRTOS
  xTaskCreate(
    tareaContador,    // Función de la tarea
    "Contador",       // Nombre de la tarea
    10000,            // Tamaño del stack
    NULL,             // Parámetros de la tarea
    1,                // Prioridad de la tarea
    NULL              // Handle de la tarea
  );

  xTaskCreate(
    tareaDisplay,     // Función de la tarea
    "Display",        // Nombre de la tarea
    10000,            // Tamaño del stack
    NULL,             // Parámetros de la tarea
    1,                // Prioridad de la tarea
    NULL              // Handle de la tarea
  );
}

void loop() {
  // El loop está vacío porque las tareas se manejan en FreeRTOS
}