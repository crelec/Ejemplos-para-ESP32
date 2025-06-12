#include <Arduino.h>

char men_in[10];  // Buffer para datos de entrada
unsigned long UltimoTiempo = 0;
const unsigned long Intervalo = 100;  // Intervalo de polling en ms
bool mensajeMostrado = false; 

void setup() {
  Serial.begin(115200);
  Serial.write("Arranque programa..\r\n",21);
}

//prototipo de la función
void cambiarVocal(char *str);

void loop() {
  if (!mensajeMostrado) {
    Serial.write("Por favor ingrese texto a convertir (vocales -> numeros):\r\n",59);
    mensajeMostrado = true;
  }

  // Polling no bloqueante usando millis()
  if (millis() - UltimoTiempo >= Intervalo) {
    UltimoTiempo = millis();
    
    if (Serial.available()) {
      memset(men_in, 0, sizeof(men_in));  // Limpiar buffer
      size_t bytesLeidos = Serial.readBytesUntil('\n', men_in, 9);
      men_in[bytesLeidos] = '\0';  // Asegurar terminador nulo
      
      cambiarVocal(men_in);
      char mensajeSalida[30];
      int len = snprintf(mensajeSalida, sizeof(mensajeSalida), "Texto convertido: %s\r\n", men_in);
      Serial.write(mensajeSalida, len);
      Serial.write("Ingrese nuevo texto:\r\n ", 22); 
    }
  }
}

void cambiarVocal(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    switch (str[i]) {
      case 'a': str[i] = '1'; break;
      case 'e': str[i] = '2'; break;
      case 'i': str[i] = '3'; break;
      case 'o': str[i] = '4'; break;
      case 'u': str[i] = '5'; break;
      case 'A': str[i] = '1'; break;
      case 'E': str[i] = '2'; break;
      case 'I': str[i] = '3'; break;
      case 'O': str[i] = '4'; break;
      case 'U': str[i] = '5'; break;
      default: break;
    }
  }
}