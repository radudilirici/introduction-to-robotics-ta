const int buttonPin = 2;
const int ledPin = 13;

volatile bool possiblePress = false;
volatile bool shouldStartCounter = false;

unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

bool ledState = LOW;
bool buttonState = HIGH;
bool buttonReading = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, FALLING);
}

void loop() {
  if (possiblePress) {
    if (shouldStartCounter) {
      lastDebounceTime = millis();
      shouldStartCounter = false;
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
      buttonReading = digitalRead(buttonPin);
      if (buttonReading != buttonState) {
        if (buttonReading == LOW) {
          ledState = !ledState;
          digitalWrite(ledPin, ledState);
        }
      } // Else, false alarm
      possiblePress = false;
    }
  }
}

void handleInterrupt() {
  possiblePress = true;
  shouldStartCounter = true;
}
