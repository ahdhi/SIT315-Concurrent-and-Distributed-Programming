// Interrupt-driven Sense-Think-Act Program

const int pirSensorPin = 2; // Pin for the PIR sensor
const int ledPin = LED_BUILTIN; // Built-in LED pin
volatile bool motionDetected = false; // Volatile variable to store motion detection state

void setup() {
  pinMode(pirSensorPin, INPUT); // Set PIR sensor pin as input
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Start serial communication

  // Attach interrupt to the PIR sensor pin
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), motionISR, CHANGE);
}

void loop() {
  // Check if motion is detected
  if (motionDetected) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Motion detected, LED is ON");
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
    Serial.println("No motion, LED is OFF");
  }
  delay(1000); // Wait for a second before next check
}

// Interrupt Service Routine (ISR) for motion detection
void motionISR() {
  motionDetected = digitalRead(pirSensorPin) == HIGH;
}
