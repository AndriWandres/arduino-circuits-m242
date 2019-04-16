/*
 * This program programmatically toggles a blinking LED lamp 
 * on the breadboard via a push button.
 */

const int buttonPin = 2;
const int ledPin = 3;

byte ledState = HIGH;
byte buttonState;
byte lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);

  // Register I/O Pins
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Set initial state of LED to OFF
  digitalWrite(ledPin, ledState);
}

void loop() {
  // Get button state
  byte reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  // Debounce button press
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Toggle LED state
      if (buttonState == HIGH) {
        ledState = !ledState;
        Serial.println("Pressed!");
      }
    }
  }
  
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
