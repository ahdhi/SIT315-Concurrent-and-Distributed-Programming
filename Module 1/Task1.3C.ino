// Multiple-Inputs Interrupt-driven Program with Button-Controlled Piezo

const int pirSensorPin = 2; // Pin for the PIR sensor
const int buttonPin = 3; // Pin for the button
const int piezoPin = 4; // Pin for the piezo
const int ledPin = LED_BUILTIN; // Built-in LED pin
volatile bool motionDetected = false; // Volatile variable to store motion detection state
volatile bool soundDetected = false; // Volatile variable to store sound detection state

void setup() {
  pinMode(pirSensorPin, INPUT); // Set PIR sensor pin as input
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
  pinMode(piezoPin, OUTPUT); // Set piezo pin as output
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Start serial communication

  // Attach interrupts to the sensor pins
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), motionISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), soundISR, CHANGE);
}

void loop() {
  // Check if motion or sound is detected
  if (motionDetected) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Motion detected, LED is ON");
  } else if (soundDetected) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Sound detected, LED is ON");
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
    Serial.println("No motion or sound, LED is OFF");
  }
  delay(1000); // Wait for a second before next check
}

// Interrupt Service Routine (ISR) for motion detection
void motionISR() {
  motionDetected = digitalRead(pirSensorPin) == HIGH;
}

// Interrupt Service Routine (ISR) for sound detection
void soundISR() {
  soundDetected = digitalRead(buttonPin) == LOW;
  digitalWrite(piezoPin, soundDetected ? HIGH : LOW); // Control the piezo based on button state
}
