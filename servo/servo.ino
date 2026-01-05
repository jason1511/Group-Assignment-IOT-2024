#include <Servo.h>

Servo myservo;

int cm = 0;
unsigned long detectionStartTime = 0;
bool objectDetected = false;

// Function to read ultrasonic distance
long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH, 30000); // 30ms timeout
}

void setup() {
  pinMode(12, OUTPUT); // Set pin mode for pin 12 to OUTPUT
  digitalWrite(12, LOW);
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(0); // Initialize the servo position to closed (0 degrees)
  Serial.println("Setup complete.");
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.parseInt();
    Serial.print("Received command: ");
    Serial.println(command);
    handleCommand(command);
  }
  
  long duration = readUltrasonicDistance(6, 7);
  cm = 0.01723 * duration;

  if (duration == 0) {
    if (objectDetected) {
      unsigned long detectionEndTime = millis();
      unsigned long detectionDuration = detectionEndTime - detectionStartTime;
      Serial.print("Object detected for ");
      Serial.print(detectionDuration);
      Serial.println(" milliseconds.");
      moveServoSlowly(120, 0); // Close the gate slowly
      objectDetected = false; // Reset the detection flag
    }
    Serial.println("No object detected.");
    delay(1000); // Small delay to avoid spamming the serial monitor
    return; // Exit the loop function if no object is detected
  }

  if (cm >= 5 && cm <= 10) {
    if (!objectDetected) {
      detectionStartTime = millis();
      objectDetected = true; // Set the detection flag
      moveServoSlowly(0, 90); // Open the gate slowly to 90 degrees
    }
    Serial.print(cm);
    Serial.println(" cm");

    delay(1000); // Small delay to avoid spamming the serial monitor
  }
}

// Function to handle commands received via serial
void handleCommand(int command) {
  if (command == 9) { // Command to turn on the servo motor (open)
    moveServoSlowly(0, 90);
    Serial.println("Servo opened.");
  } else if (command == 19) { // Command to turn off the servo motor (close)
    moveServoSlowly(90, 0);
    Serial.println("Servo closed.");
  } else {
    Serial.print("Unknown command: ");
    Serial.println(command);
  }
}

// Function to move the servo slowly
void moveServoSlowly(int fromAngle, int toAngle) {
  int step = (toAngle > fromAngle) ? 1 : -1; // Determine the direction
  for (int pos = fromAngle; pos != toAngle; pos += step) {
    myservo.write(pos);
    delay(15); // Adjust delay to control the speed
  }
  myservo.write(toAngle); // Ensure the final position is set
}
