#include <Arduino.h>
#include <BluetoothSerial.h>

// Crear una instancia de BluetoothSerial
BluetoothSerial SerialBT;

// Búfer para almacenar palabras recibidas
String inputBuffer = "";
String outBuffer = "";
void setup() {
  // Inicia el puerto serial para depuración
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); // Nombre del dispositivo Bluetooth
  Serial.println("Bluetooth iniciado. Nombre: ESP32_BT");
}

void loop() {
   // Verifica si hay datos recibidos por Bluetooth
  while (SerialBT.available()) {
    // Lee un carácter recibido
    char received = SerialBT.read();

    // Si el carácter es un delimitador (por ejemplo, '\n' , '\r'), se procesa la palabra
    if (received == '\n' || received == '\r') {
      if (inputBuffer.length() > 0) {
        Serial.print("Palabra recibida: ");
        Serial.println(inputBuffer);

        inputBuffer.toUpperCase();
        outBuffer =inputBuffer; 
        SerialBT.print("Palabra enviada: ");
        SerialBT.println(outBuffer);
        
        // Limpia el búfer para la siguiente palabra
        inputBuffer = "";
      }
    } else {
      // Agrega el carácter al búfer
      inputBuffer += received;
    }
  }
  // Pequeña pausa para evitar saturar el procesador
  delay(200);
}