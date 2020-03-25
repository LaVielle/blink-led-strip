#include <Arduino.h>
#include <FastLED.h>

#include "Signal.h"

const int numLeds = 3;
const int leftButtonPin = 2;
const int leftLedPin = 9;

Signal signal = Signal(
  leftButtonPin,
  leftLedPin,
  numLeds
);

void toggleSignal() {
  signal.toggleSignal();
}

void addLeds(int ledPin, CRGB leds[]) {
  FastLED.addLeds<WS2812B, leftLedPin, RGB>(leds, numLeds);
}

void setup() {
  Serial.begin(115200);

  signal.setupButtonInterrupt(toggleSignal);
}

void loop() {

}

// #include "Signal.h"

// const int numLeds = 3;

// const int leftButtonPin = 2;
// const int rightButtonPin = 3;

// const int leftLedPin = 9;
// const int rightLedPin = 10;

// bool isLeftBlinking = false;
// bool isRightBlinking = false;

// unsigned long leftPrevLedOnMillis = 0;
// int leftNextLedOnIndex = 0;
// unsigned long rightPrevLedOnMillis = 0;
// int rightNextLedOnIndex = 0;

// CRGB colorOn = CRGB(70, 255, 0); // orange
// CRGB colorOff = CRGB(0, 0, 0); // black

// CRGB leftLeds [numLeds];
// CRGB rightLeds [numLeds];

// const long intervalTurnOnNextLed = 250;

// // FUNCTIONS ************************************************************

// void toggleLeftSignal() {
//   isLeftBlinking = !isLeftBlinking;
//   leftPrevLedOnMillis = 0;
//   leftNextLedOnIndex = 0;
// }

// void toggleRightSignal() {
//   isRightBlinking = !isRightBlinking;
//   rightPrevLedOnMillis = 0;
//   rightNextLedOnIndex = 0;
// }

// void setAllLedsToColor(CRGB arr[], CRGB color) {
//   for (int i = 0; i < numLeds; i++) {
//     arr[i] = color;
//   }
// }

// struct blinkTroughtStripReturn {
//   unsigned long prevLedOnMillis;
//   int nextLedOnIndex;
// };

// blinkTroughtStripReturn blinkTroughtStrip (CRGB arr[], unsigned long prevLedOnMillis, int nextLedOnIndex) {

//   Serial.println("blinkTroughtStrip");

//   Serial.print("prevLedOnMillis: ");
//   Serial.println(prevLedOnMillis);

//   Serial.print("nextLedOnIndex: ");
//   Serial.println(nextLedOnIndex);

//   unsigned long currentMillis = millis();

//   for (int i = 0; i < numLeds; i++) {

//     Serial.println("blinkTroughtStrip loop 1");

//     const bool timeReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;
//     const bool isCorrectIndex = i == nextLedOnIndex;

//     Serial.print("timeReached: ");
//     Serial.println(timeReached);

//     Serial.print("isCorrectIndex: ");
//     Serial.println(isCorrectIndex);

//     if (timeReached && isCorrectIndex) {
//       // turn on current led
//       arr[i] = colorOn;
//       Serial.println(arr[i]);

//       // set turn on time and index for next led
//       prevLedOnMillis = currentMillis;
//       nextLedOnIndex = i + 1;
//     }
//   }

//   const bool timeToResetReached = currentMillis - prevLedOnMillis >= intervalTurnOnNextLed;

//   if (timeToResetReached && nextLedOnIndex >= numLeds) {
//     for (int i = 0; i < numLeds; i++) {
//       arr[i] = colorOff;
//     }

//     prevLedOnMillis = currentMillis;
//     nextLedOnIndex = 0;
//   }

//   blinkTroughtStripReturn newValues;
//   newValues.prevLedOnMillis = prevLedOnMillis;
//   newValues.nextLedOnIndex = nextLedOnIndex;

//   return newValues;
// }

// // SETUP ************************************************************

// void setup() {
//   // Serial.begin(115200);
//   Serial.begin(9600);

//   pinMode(leftButtonPin, INPUT);

//   attachInterrupt(
//     digitalPinToInterrupt(leftButtonPin),
//     toggleLeftSignal,
//     RISING
//   );

//   pinMode(rightButtonPin, INPUT);

//   attachInterrupt(
//     digitalPinToInterrupt(rightButtonPin),
//     toggleRightSignal,
//     RISING
//   );

//   setAllLedsToColor(leftLeds, colorOff);
//   setAllLedsToColor(rightLeds, colorOff);

//   FastLED.addLeds<WS2812B, leftLedPin, RGB>(leftLeds, leftLedPin);
//   FastLED.addLeds<WS2812B, rightLedPin, RGB>(rightLeds, rightLedPin);

//   FastLED.show();
  
//   Serial.println("setup complete");
// }

// // LOOP ************************************************************

// void loop() {

//   if (isLeftBlinking){
//     blinkTroughtStripReturn newLedValues = blinkTroughtStrip(leftLeds, leftPrevLedOnMillis, leftNextLedOnIndex);
//     leftPrevLedOnMillis = newLedValues.prevLedOnMillis;
//     leftNextLedOnIndex = newLedValues.nextLedOnIndex;
//   }

//   if (isRightBlinking){
//     blinkTroughtStripReturn newLedValues = blinkTroughtStrip(rightLeds, rightPrevLedOnMillis, rightNextLedOnIndex);
//     rightPrevLedOnMillis = newLedValues.prevLedOnMillis;
//     rightNextLedOnIndex = newLedValues.nextLedOnIndex;
//   }

//   FastLED.show();
// }

