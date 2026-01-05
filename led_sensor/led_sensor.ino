int led1 = 3;

void setup() {
  pinMode(led1, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == '1') {
      digitalWrite(led1, HIGH); // Turn on the LED
    } else if (receivedChar == '0') {
      digitalWrite(led1, LOW); // Turn off the LED
    }
  }
}
