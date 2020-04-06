int ledPin = 13;
int switchPin = 2;
byte switchState = 1;
byte lastState = 1;
word shortDuration = 1000;
word longDuration = 3000;
unsigned long switchTime = 0;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  switchState = digitalRead(switchPin);

  if (!switchState && lastState) {  // just pressed
    lastState = switchState;
    switchTime = millis(); // start timer
  }
  if (switchState && !lastState) {   // just released
    if (((millis() - switchTime) <= shortDuration) && ((millis() - switchTime) <= longDuration)) { // short press
      digitalWrite(ledPin, HIGH);
      delay(shortDuration);
      digitalWrite(ledPin, LOW);
      lastState = switchState;
    }
    if ((millis() - switchTime) > longDuration) { // long press
      digitalWrite(ledPin, HIGH);
      delay(longDuration);
      digitalWrite(ledPin, LOW);
      lastState = switchState;
    }
  }
}
