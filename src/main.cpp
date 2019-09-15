#include <Arduino.h>
#include <Servo.h>

Servo myservo;
// int angle = 1;
// int dir = 1;

const int angleOpen = 88;
const int angleClosed = 17;
const int openDelay = 2500;

const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

int buttonState = LOW;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  myservo.attach(7);
  myservo.write(angleClosed);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void moveServo() {
  myservo.write(angleOpen);
  delay(openDelay);
  myservo.write(angleClosed);
}

void loop() {

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        Serial.println("Button pressed");
        moveServo();
      }
    }
  }

  lastButtonState = reading;



}