#include <FastLED.h>

#include "Pixel.cpp"
const Pixel pix = Pixel();

const int SOLO_LED_PIN = 8;

const int BUTTON_LEFT_PIN = 9;
const int BUTTON_RIGHT_PIN = 10;
int buttonLeftState = 0;
int buttonRightState = 0;

bool isLeftBlinking = false;
bool isRightBlinking = false;

unsigned long prevLedOnMillis = 0;
int nextLedOnIndex = 0;
const long intervalTurnOnNextLed = 250;

const int NUM_LEDS = 3;
const int LED_PIN = 2;

Pixel pixels[NUM_LEDS];
CRGB leds[NUM_LEDS];

const CRGB ON = CRGB(255, 255, 0);
const CRGB OFF = CRGB(0, 0, 0);

void blinkLed() {
  digitalWrite(SOLO_LED_PIN, HIGH);
  delay(50);
  digitalWrite(SOLO_LED_PIN, LOW);
}

// SETUP ************************************************************

void setup() {
  Serial.begin(9600);
  
  // setup solo LED pin
  pinMode(SOLO_LED_PIN, OUTPUT);

  // setup button pins
  pinMode(BUTTON_LEFT_PIN, INPUT);
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

//void loop() {
//
//  buttonLeftState = digitalRead(BUTTON_LEFT_PIN);
//
//  if (buttonLeftState == HIGH) {
//    if (isLeftBlinking == true){
//      isLeftBlinking = false;
//    } else {
//      isLeftBlinking = true;
//    }
//    
//  }
//
//  if (isLeftBlinking == true){
//    
//    for (int i = 0; i < NUM_LEDS; i++) {
//      // turn on current led
//      pixels[i].setIsOn(true);
//      leds[i] = pixels[i].color;
//      FastLED.show();
//      delay(intervalTurnOnNextLed);
//    }
//
//    for (int i = 0; i < NUM_LEDS; i++) {
//      pixels[i].setIsOn(false);
//      leds[i] = pixels[i].color;
//    }
//    FastLED.show();
//    delay(intervalTurnOnNextLed);
//  }
//}

void loop() {

  buttonLeftState = digitalRead(BUTTON_LEFT_PIN);

  if (buttonLeftState == HIGH) {
    if (isLeftBlinking == true){
      isLeftBlinking = false;
    } else {
      isLeftBlinking = true;
    }
    
  }

  Serial.print("isLeftBlinking: ");
  Serial.println(isLeftBlinking);
  Serial.println("************");

  if (isLeftBlinking == true){
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
  }
  
  FastLED.show();
}
