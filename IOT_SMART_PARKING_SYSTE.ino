#include <Servo.h>

const int sensor1Pin = 2;  // IR sensor 1 pin (entry sensor)
const int sensor2Pin = 3;  // IR sensor 2 pin (exit sensor)
const int servoPin = 9;    // Servo motor pin
const int ledPin = 4;      // Red LED pin

Servo parkingGate;

// Parking spaces state
const int totalSpaces = 4;
int occupiedSpaces = 0;

void setup() {
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  parkingGate.attach(servoPin);
  parkingGate.write(0);  // Initialize gate to closed position
  Serial.begin(9600);    // Initialize Serial Monitor for debugging
}

void loop() {
  bool entryDetected = digitalRead(sensor1Pin) == LOW;
  bool exitDetected = digitalRead(sensor2Pin) == LOW;

  // Debugging: Print sensor status to the Serial Monitor
  Serial.print("Entry Sensor: ");
  Serial.print(entryDetected ? "Detected" : "Not Detected");
  Serial.print(" | Exit Sensor: ");
  Serial.println(exitDetected ? "Detected" : "Not Detected");

  // LED behavior when the parking lot is full
  if (occupiedSpaces >= totalSpaces) {
    blinkLED();  // Blink LED to indicate full parking
  } else {
    digitalWrite(ledPin, HIGH);  // Steady on when spaces are available
  }

  // Handle entry
  if (entryDetected && occupiedSpaces < totalSpaces) {
    parkingGate.write(90);  // Open gate
    digitalWrite(ledPin, LOW);  // Turn off LED when gate is open
    delay(2000);  // Keep the gate open for 2 seconds
    parkingGate.write(0);  // Close gate
    occupiedSpaces++;  // Update occupied spaces
    delay(1000);  // Debounce delay
  }

  // Handle exit
  if (exitDetected && occupiedSpaces > 0) {
    parkingGate.write(90);  // Open gate
    digitalWrite(ledPin, LOW);  // Turn off LED when gate is open
    delay(2000);  // Keep the gate open for 2 seconds
    parkingGate.write(0);  // Close gate
    occupiedSpaces--;  // Update occupied spaces
    delay(1000);  // Debounce delay
  }

  delay(500);  // Check every 500 milliseconds
}

// Function to blink LED when parking is full
void blinkLED() {
  digitalWrite(ledPin, HIGH);  // Turn on LED
  delay(500);  // Wait for 500ms
  digitalWrite(ledPin, LOW);  // Turn off LED
  delay(500);  // Wait for 500ms
}
