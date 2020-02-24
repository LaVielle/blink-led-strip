#include <FastLED.h>

#include "Pixel.cpp"
const Pixel pix = Pixel();

const int SOLO_LED_PIN = 8;

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
const int LED_PIN = 9;

Pixel pixels[NUM_LEDS];
CRGB leds[NUM_LEDS];

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

  // fill up array of pixels
  for (int i = 0; i < NUM_LEDS; i++) {
    Pixel p;
    pixels[i] = p;
    leds[i] = p.color;
  }

  // setup LED strips pins
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    pixels[i].setIsOn(false);
  }

  FastLED.show();
}

// LOOP ************************************************************

void loop() {

  if (isLeftBlinking == true) {
    unsigned long currentMillis = millis();
    
    for (int i = 0; i < NUM_LEDS; i++) {
      const bool timeReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;
      const bool isCorrectIndex = i == nextLedOnIndex;
      
      if (timeReached && isCorrectIndex) {
        // turn on current led
        pixels[i].setIsOn(true);
        leds[i] = pixels[i].color;

        // set turn on time and index for next led
        prevLedOnMillis = currentMillis;
        nextLedOnIndex = i + 1;
      }

    }

    const bool timeToResetReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;

    if (timeToResetReached && nextLedOnIndex >= NUM_LEDS) {
      // reset all leds
      for (int i = 0; i < NUM_LEDS; i++) {
        pixels[i].setIsOn(false);
        leds[i] = pixels[i].color;
      }

      // next led on willbe the first in array
      prevLedOnMillis = currentMillis;
      nextLedOnIndex = 0;
    }
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      pixels[i].setIsOn(false);
      leds[i] = pixels[i].color;
    }
  }
  
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
  isRightBlinking = !isRightBlinking;
}
