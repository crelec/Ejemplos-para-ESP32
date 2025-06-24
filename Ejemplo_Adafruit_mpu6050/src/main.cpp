#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>

// ****** Credenciales WiFi y Adafruit IO ******
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "ceroma175"
#define AIO_KEY         "aio_Ibcq74plXhMrfCrjhSIaDFt2Dh1X"

// ****** Objetos globales ******
Adafruit_MPU6050 mpu;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// ****** Publicadores MQTT ******
Adafruit_MQTT_Publish _mpuMqttTemperatura = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sensormpu", MQTT_QOS_1);
Adafruit_MQTT_Publish _mpuMqtt_ACX = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/aceleracion-x", MQTT_QOS_1);
Adafruit_MQTT_Publish _mpuMqtt_ACY = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/aceleracion-y", MQTT_QOS_1);
Adafruit_MQTT_Publish _mpuMqtt_ACZ = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/aceleracion-z", MQTT_QOS_1);

// ****** Variables de tiempo ******
unsigned long previousMillis = 0;
const long intervalo = 60000;  // constante para lectura y publicacion en milisegundos
                                // este caso 1 minutos (1min * 60seg * 1000ms)=60000

// ****** Prototipos ******
void initSerial();
void initWiFi();
void conectar_broker();

void setup() {
  initSerial();
  initWiFi();
  conectar_broker();

  if (!mpu.begin()) {
    Serial.println("MPU6050 No encontrado.");
    while (1);
  }

  Serial.println("..MPU6050 encontrado..");
}

void loop() {
  if (!mqtt.connected()) {
    conectar_broker();
  }

  mqtt.processPackets(1500);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo) {
    previousMillis = currentMillis;

    // Obtener datos del sensor
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Mostrar por consola
    // 9.81 es la aceleración de la gravedad en m/s²
    Serial.print("Temperatura: "); Serial.print(temp.temperature); Serial.println(" °C");
    Serial.print("Aceleración X: "); Serial.print(a.acceleration.x/9.81); Serial.println(" g");
    Serial.print("Aceleración Y: "); Serial.print(a.acceleration.y/9.81); Serial.println(" g");
    Serial.print("Aceleración Z: "); Serial.print(a.acceleration.z/9.81); Serial.println(" g");
    Serial.println("-----------------------");

    // Publicar en Adafruit IO
    if (!_mpuMqttTemperatura.publish(temp.temperature)) {
      Serial.println("Fallo al enviar Temperatura.");
    }
    if (!_mpuMqtt_ACX.publish(a.acceleration.x/9.81)) {
      Serial.println("Fallo al enviar Aceleración X.");
    }
    if (!_mpuMqtt_ACY.publish(a.acceleration.y/9.81)) {
      Serial.println("Fallo al enviar Aceleración Y.");
    }
    if (!_mpuMqtt_ACZ.publish(a.acceleration.z/9.81)) {
      Serial.println("Fallo al enviar Aceleración Z.");
    }
  }
}

// ****** Inicializar el puerto serial ******
void initSerial() {
  Serial.begin(115200);
  delay(10);
}

// ****** Conexión WiFi ******
void initWiFi() {
  Serial.print(".Conectando a la red: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado exitosamente a WiFi.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

// ****** Conectar con Adafruit MQTT Broker ******
void conectar_broker() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.println("Conectando al broker MQTT...");

  uint8_t intentos = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.print("Error de conexión: ");
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Reintentando en 5 segundos...");
    mqtt.disconnect();
    delay(5000);
    intentos--;
    if (intentos == 0) {
      Serial.println("No fue posible conectarse. Reiniciando...");
      ESP.restart();
    }
  }
  Serial.println("Conectado exitosamente al broker MQTT.");
}