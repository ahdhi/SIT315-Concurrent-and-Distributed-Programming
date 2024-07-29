// Simple Sense-Think-Act Program

const int pirSensorPin = 2; // Pin for the PIR sensor
const int ledPin = LED_BUILTIN; // Built-in LED pin

void setup() {
  pinMode(pirSensorPin, INPUT); // Set PIR sensor pin as input
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Start serial communication
}

void loop() {
  int sensorValue = digitalRead(pirSensorPin); // Read the PIR sensor value
  
  if (sensorValue == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Motion detected, LED is ON");
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
    Serial.println("No motion, LED is OFF");
  }
  delay(1000); // Wait for a second before next reading
}
