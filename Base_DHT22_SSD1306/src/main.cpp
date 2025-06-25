#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

//Definiciones para DHT22
#define DTHPIN 23     //Defino el pin 23 para obtener los datos del sensor DTH22
#define DHTTYPE DHT22 // Defino el Tipo de sensor a utilizar uso:DHT22

// Definiciones para el display SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // Dirección I2C del display SSD1306


DHT dht(DTHPIN, DHTTYPE);  //Configuro o inicializo pin de micro y tipo de sensor a usar

// Crear objeto display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  dht.begin();                  //Inicio (star) al sensor DHT22
  // Inicializar el display SSD1306
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Detener la ejecución si no se puede inicializar el display
  }
  display.display();
}

void loop() {
float temperatura = dht.readTemperature(); // realizo lectura de temperatura y guardo el valor en una variable tipo flotante
float humedad = dht.readHumidity();       // realizo lectura de humedad y guardo el valor en una variable tipo flotante

display.clearDisplay();  
// Mostrar medidas
display.setCursor(0,0);
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.print("T:");
display.print(String(temperatura));
display.print("C");  
display.setCursor(0,30);
display.print("H:");
display.print(String(humedad));
display.print("%");  
// Actualizar el display
display.display();

delay(1000); //espera de un segundo del tipo bloqueante.
}