int IR1 = 13; // Use pin 13 for the XC4524 sensor
int val1;

void setup() {
  pinMode(IR1, INPUT);
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  val1 = digitalRead(IR1);
  Serial.println(val1);

  delay(1000); // Delay for stability
}
