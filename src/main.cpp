#include <Arduino.h>
#include <FastLED.h>

#include "Timer.h"
#include "Signal.h"

const int numLeds = 3;

Timer timer = Timer(numLeds);

const int leftButtonPin = 2;
const int leftFrontLedPin = 9;
const int leftBackLedPin = 10;

const int rightButtonPin = 3;
const int rightFrontLedPin = 11;
const int rightBackLedPin = 12;

unsigned long prevLedOnMillis = 0;
int nextLedOnIndex = 0;

Signal leftSignal = Signal(
  leftButtonPin,
  numLeds
);

Signal rightSignal = Signal(
  rightButtonPin,
  numLeds
);

void toggleLeftSignal() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) {
    leftSignal.toggleSignal();
  }

  last_interrupt_time = interrupt_time;
}

void toggleRightSignal() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) {
    rightSignal.toggleSignal();
  }
  
  last_interrupt_time = interrupt_time;
}

void setup() {
  Serial.begin(115200);

  leftSignal.setupButtonInterrupt(toggleLeftSignal);
  rightSignal.setupButtonInterrupt(toggleRightSignal);

  FastLED.addLeds<WS2812B, leftFrontLedPin, GRB>(leftSignal.frontLeds, numLeds);
  FastLED.addLeds<WS2812B, leftBackLedPin, GRB>(leftSignal.backLeds, numLeds);

  FastLED.addLeds<WS2812B, rightFrontLedPin, GRB>(rightSignal.frontLeds, numLeds);
  FastLED.addLeds<WS2812B, rightBackLedPin, GRB>(rightSignal.backLeds, numLeds);
}

void loop() {

  const bool anySignalBlinking = leftSignal.getIsBlinking() || rightSignal.getIsBlinking();

  timerState t;

  if (anySignalBlinking) {
    t = timer.update();
  } else {
    t = timer.reset();
  }

  leftSignal.blink(t);
  rightSignal.blink(t);
}

