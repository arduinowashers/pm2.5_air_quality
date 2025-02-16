int ledPin = 7;  // Контролен пин за LED в сензора
int sensorPin = A0;  // Аналогов вход за измерване на прах

int redPin = 9;   // Червен канал
int greenPin = 10; // Зелен канал
int bluePin = 11;  // Син канал

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
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

void updateLED(float dustLevel) {
  if (dustLevel < 50) {      
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);  // Зелено
  } 
  else if (dustLevel < 100) { 
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);  // Жълто
  } 
  else if (dustLevel < 150) { 
    analogWrite(redPin, 255);
    analogWrite(greenPin, 165);
    analogWrite(bluePin, 0);  // Оранжево
  } 
  else {                      
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);  // Червено
  }
}

void loop() {
  float dustLevel = readDustLevel();
  Serial.print("Dust Density: ");
  Serial.print(dustLevel);
  Serial.println(" µg/m³");

  updateLED(dustLevel);  

  delay(1000);
}
