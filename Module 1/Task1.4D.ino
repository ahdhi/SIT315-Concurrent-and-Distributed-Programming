// Multiple-Inputs Interrupt-driven Program with Button-Controlled Piezo

const int pirSensorPin = 2; // Pin for the PIR sensor
const int buttonPin = 3; // Pin for the button
const int piezoPin = 4; // Pin for the piezo
const int tempSensorPin = A0; // Analog pin for the TMP36 temperature sensor
const int ledPin = LED_BUILTIN; // Built-in LED pin
volatile bool motionDetected = false; // Volatile variable to store motion detection state
volatile bool soundDetected = false; // Volatile variable to store sound detection state

void setup() {
  pinMode(pirSensorPin, INPUT); // Set PIR sensor pin as input
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
  pinMode(piezoPin, OUTPUT); // Set piezo pin as output
  pinMode(tempSensorPin, INPUT); // Set temperature sensor pin as input
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Start serial communication

  // Attach interrupts to the sensor pins
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), motionISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), soundISR, CHANGE);
}

void loop() {
  // Read temperature sensor
  int tempReading = analogRead(tempSensorPin);
  float voltage = tempReading * (5.0 / 1023.0); // Convert analog reading to voltage
  float temperatureC = (voltage - 0.5) * 100.0; // Convert voltage to temperature in Celsius for TMP36

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Check if temperature is above 20°C
  if (temperatureC > 20) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Temperature above 20C detected, LED is ON");
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
    Serial.println("Temperature below 20C, LED is OFF");
  }

  // Check if motion or sound is detected
  if (motionDetected) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Motion detected, LED is ON");
  } else if (soundDetected) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Sound detected, LED is ON");
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
