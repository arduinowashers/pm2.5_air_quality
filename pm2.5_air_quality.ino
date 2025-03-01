#include <DHT.h>

int ledPin = 4;    // Контролен пин за LED в сензора
int sensorPin = A0; // Аналогов вход за измерване на прах

#define DHTPIN 11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  dht.begin();
}

float readDustLevel() {
  digitalWrite(ledPin, LOW);  
  delayMicroseconds(280);  

  int sensorValue = analogRead(sensorPin);  

  digitalWrite(ledPin, HIGH);  
  delayMicroseconds(40);  

  float voltage = sensorValue * (5.0 / 1024.0);  
  float dustDensity = 170 * voltage - 0.1;  

  return dustDensity;
}

void loop() {
  float dustLevel = readDustLevel();
  float temp = dht.readTemperature(); // Чете температура (по Целзий)
  float hum = dht.readHumidity();     // Чете влажност
  Serial.print("Dust Density: ");        
  Serial.print(dustLevel);
  Serial.println(" µg/m³");
  

  delay(3000); // Намаляваме забавянето


if (isnan(temp) || isnan(hum)) {
    Serial.println("Error");
    return;
  }

  Serial.print("TEMP: ");
  Serial.print(temp);
  Serial.print("°C | HUM: ");
  Serial.print(hum);
  Serial.println("%");

   delay(1000); // Чака 2 секунди между измерванията
}