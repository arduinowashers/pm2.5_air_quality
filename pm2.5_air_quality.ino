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
  if (dustLevel < 15) {      
    analogWrite(redPin, 0);
    analogWrite(greenPin, 63);
    analogWrite(bluePin, 0);
    Serial.println("Excellent");  
  } 
  else if (dustLevel < 40) { 
    analogWrite(redPin, 63);
    analogWrite(greenPin, 15);
    analogWrite(bluePin, 0); 
    Serial.println("Good");   
  } 
  else if (dustLevel < 65) { 
    analogWrite(redPin, 63);
    analogWrite(greenPin, 5);
    analogWrite(bluePin, 0); 
    Serial.println("Mild");  
  } 
  else if (dustLevel < 150) {                      
    analogWrite(redPin, 63);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);  
    Serial.println("Moderate");
  }
  else if (dustLevel < 250) {                      
    analogWrite(redPin, 63);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 20);
    Serial.println("Severe");
  }
  else {                      
    analogWrite(redPin, 6);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 2);
    Serial.println("Serious");
  }
}
void loop() {
  float dustLevel = readDustLevel();
  Serial.print("Dust Density: ");
  Serial.print(dustLevel);
  Serial.println(" µg/m³");

  updateLED(dustLevel);  

  delay(3000);
}
