#include <FastLED.h>

#include "Pixel.cpp"

const int BUTTON_LEFT_PIN = 2;
const int BUTTON_RIGHT_PIN = 3;
int buttonLeftState = 0;
int buttonRightState = 0;

bool isLeftBlinking = false;
bool isRightBlinking = false;

unsigned long prevLedOnMillis = 0;
int nextLedOnIndex = 0;
const long intervalTurnOnNextLed = 250;

const int NUM_LEDS = 3;
const int LEFT_LED_PIN = 9;
const int RIGHT_LED_PIN = 10;

Pixel leftPixels[NUM_LEDS];
CRGB leftLeds[NUM_LEDS];

Pixel rightPixels[NUM_LEDS];
CRGB rightLeds[NUM_LEDS];

// SETUP ************************************************************

void setup() {
  Serial.begin(9600);

  // setup button pins
  pinMode(BUTTON_LEFT_PIN, INPUT);
  
  attachInterrupt(
    digitalPinToInterrupt(BUTTON_LEFT_PIN),
    toggleLeftSignal,
    RISING
  );
  
  pinMode(BUTTON_RIGHT_PIN, INPUT);

//  attachInterrupt(
//    digitalPinToInterrupt(BUTTON_RIGHT_PIN),
//    toggleRightSignal,
//    RISING
//  );

  // fill up array of leftPixels
  for (int i = 0; i < NUM_LEDS; i++) {
    Pixel p;
    leftPixels[i] = p;
    leftLeds[i] = p.color;

    rightPixels[i] = p;
    rightLeds[i] = p.color;
  }

  // setup LED strips pins
  FastLED.addLeds<WS2812B, LEFT_LED_PIN>(leftLeds, NUM_LEDS);
//  FastLED.addLeds<WS2812B, RIGHT_LED_PIN>(rightLeds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leftPixels[i].setIsOn(false);
    rightPixels[i].setIsOn(false);
  }

  FastLED.show();
}

// LOOP ************************************************************

void loop() {

  if (isLeftBlinking) {
    unsigned long currentMillis = millis();
    
    for (int i = 0; i < NUM_LEDS; i++) {
      const bool timeReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;
      const bool isCorrectIndex = i == nextLedOnIndex;
      
      if (timeReached && isCorrectIndex) {
        // turn on current led
        leftPixels[i].setIsOn(true);
        leftLeds[i] = leftPixels[i].color;

        // set turn on time and index for next led
        prevLedOnMillis = currentMillis;
        nextLedOnIndex = i + 1;
      }

    }

    const bool timeToResetReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;

    if (timeToResetReached && nextLedOnIndex >= NUM_LEDS) {
      // reset all leds
      for (int i = 0; i < NUM_LEDS; i++) {
        leftPixels[i].setIsOn(false);
        leftLeds[i] = leftPixels[i].color;
      }

      // next led on willbe the first in array
      prevLedOnMillis = currentMillis;
      nextLedOnIndex = 0;
    }
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leftPixels[i].setIsOn(false);
      leftLeds[i] = leftPixels[i].color;
    }
  }

//  if (isRightBlinking) {
//    unsigned long currentMillis = millis();
//    
//    for (int i = 0; i < NUM_LEDS; i++) {
//      const bool timeReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;
//      const bool isCorrectIndex = i == nextLedOnIndex;
//      
//      if (timeReached && isCorrectIndex) {
//        // turn on current led
//        rightPixels[i].setIsOn(true);
//        rightLeds[i] = rightPixels[i].color;
//
//        // set turn on time and index for next led
//        prevLedOnMillis = currentMillis;
//        nextLedOnIndex = i + 1;
//      }
//
//    }
//
//    const bool timeToResetReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;
//
//    if (timeToResetReached && nextLedOnIndex >= NUM_LEDS) {
//      // reset all leds
//      for (int i = 0; i < NUM_LEDS; i++) {
//        rightPixels[i].setIsOn(false);
//        rightLeds[i] = rightPixels[i].color;
//      }
//
//      // next led on willbe the first in array
//      prevLedOnMillis = currentMillis;
//      nextLedOnIndex = 0;
//    }
//  } else {
//    for (int i = 0; i < NUM_LEDS; i++) {
//      rightPixels[i].setIsOn(false);
//      rightLeds[i] = rightPixels[i].color;
//    }
//  }
  
  FastLED.show();
}

// FUNCTIONS ************************************************************

void toggleLeftSignal() {
  Serial.println("toggleLeftSignal");
  isLeftBlinking = !isLeftBlinking;
  prevLedOnMillis = 0;
  nextLedOnIndex = 0;
}

void toggleRightSignal() {
  Serial.println("toggleRightSignal");
  isRightBlinking = !isRightBlinking;
  prevLedOnMillis = 0;
  nextLedOnIndex = 0;
}
