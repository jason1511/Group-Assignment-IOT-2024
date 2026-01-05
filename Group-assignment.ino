#include <Adafruit_Sensor.h>
#include "DHT.h"
#include "MQUnifiedsensor.h"

#define DHTPIN 2     // what digital pin the DHT sensor is connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define FLAME_SENSOR_PIN 3 // Flame sensor output connected to Arduino pin 3
#define MQ135_PIN A0 // Define the A0 pin as the MQ135 sensor input
#define BUZZER_PIN 5  // Buzzer connected to digital pin 5
#define GAS_THRESHOLD 300  // Set the threshold for gas concentration
#define MOTOR_PIN 9 // DC Motor connected to digital pin 9 through a transistor

#define TEMP_THRESHOLD 50  // Set the threshold for temperature
#define HUMIDITY_THRESHOLD 80  // Set the threshold for humidity

// RGB LED pins
#define RED_PIN 6
#define GREEN_PIN 7
#define BLUE_PIN 8


void alarm(){
  setColor(HIGH, LOW, LOW);  // Set LED to red
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(MOTOR_PIN, LOW);  // Turn on the DC motor
}

void alarmOff(){
  setColor(LOW, HIGH, LOW);  // Set LED to red
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(MOTOR_PIN, HIGH);  // Turn on the DC motor
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);

  // Set RGB LED pins as output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void setColor(int red, int green, int blue) {
  digitalWrite(RED_PIN, red);
  digitalWrite(GREEN_PIN, green);
  digitalWrite(BLUE_PIN, blue);
}

void loop() {
  // Reading from the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Reading from the flame sensor
  int flameSensorState = digitalRead(FLAME_SENSOR_PIN);

  // Reading from the MQ-135 gas sensor
  int gasSensorValue = analogRead(MQ135_PIN);   // Convert the analog value to a gas concentration using a custom calibration equation
  float ppm = map(gasSensorValue, 0, 1023, 0, 5000); // Adjust the range based on your sensor calibration
  
  // Check if flame is detected, gas concentration is above the threshold, or temperature/humidity are too high
  if (flameSensorState == LOW || ppm > GAS_THRESHOLD || temperature > TEMP_THRESHOLD || humidity > HUMIDITY_THRESHOLD) {
    alarm();
  } else {
    alarmOff();
  }

  // Read from serial port
  if (Serial.available()) {
    String command = Serial.readString();

    if (command == "LED ON") {
      setColor(HIGH, LOW, LOW);  // Set LED to red
    } else if (command == "LED OFF") {
      setColor(LOW, HIGH, LOW);  // Set LED to green
    } else if (command == "BUZZER ON") {
      digitalWrite(BUZZER_PIN, HIGH);
    } else if (command == "BUZZER OFF") {
      digitalWrite(BUZZER_PIN, LOW);
    } else if (command == "MOTOR ON") {
      digitalWrite(MOTOR_PIN, HIGH);  // Turn on the DC motor
    } else if (command == "MOTOR OFF") {
      digitalWrite(MOTOR_PIN, LOW);  // Turn off the DC motor
    }
  }
  
  // Print the sensor readings
  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.print(" *C\t");
  Serial.print("Flame: "); 
  if (flameSensorState == HIGH) {
    Serial.print("Flame Detected");
  } else {
    Serial.print("No Flame Detected");
  }
  Serial.print("\t");
  Serial.print("Gas/Smoke Level: "); 
  Serial.print(ppm);
  Serial.println(" PPM");
  
  delay(3000);
}

void print(){
  
}
