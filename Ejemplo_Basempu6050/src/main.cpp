#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
Serial.begin(115200);
Wire.begin(21,22); // SDA, SCL
if (!mpu.begin()) {
    Serial.println("chip MPU6050 No encontrado.");
    while (1) {
      delay(10);
    }
  }
Serial.println("chip MPU6050 encontrado!");
}

void loop() {

sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);

Serial.print("Temperatura: ");
Serial.print(temp.temperature);
Serial.println(" °C");

//9.81 = gravedad

Serial.print("Acceleration X: ");
Serial.print(a.acceleration.x/9.81); 
Serial.println(" g");

Serial.print("Acceleration Y: ");
Serial.print(a.acceleration.y/9.81);
Serial.println(" g");

Serial.print("Acceleration Z: ");
Serial.print(a.acceleration.z/9.81);
Serial.println(" g");

// 57.2958 = 180/pi

Serial.print("Giroscopio X: ");
Serial.print(g.gyro.x*57.2958);
Serial.println(" °/s");

Serial.print("Giroscopio Y: ");
Serial.print(g.gyro.y*57.2958);
Serial.println(" °/s");

Serial.print("Giroscopio Z: ");
Serial.print(g.gyro.z*57.2958);
Serial.println(" °/s");

Serial.println("...............");
delay(2000);
}