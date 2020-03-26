#include <Arduino.h>
#include <FastLED.h>

#include "Pixel.h"

#ifndef _SIGNAL_H_
#define _SIGNAL_H_


class Signal {
    bool _isBlinking = false;
    int _buttonPin;
    int _numLeds = 3;

    unsigned long _prevLedOnMillis = 0;
    int _nextLedOnIndex = 0;
    long _intervalTurnOnNextLed = 250;

    public:

        Signal(int buttonPin, int ledPin, int numLeds);

        Pixel pixels[3];
        CRGB leds[3];

        // unsigned long prevLedOnMillis = 0;
        // int nextLedOnIndex = 0;

        void toggleSignal();

        void setupButtonInterrupt(void (*userFunc)(void));

        void blink();

        // void setPrevLedOnMillis(unsigned long timestamp) {
        //     prevLedOnMillis = timestamp;
        // }

        // void setNextLedOnIndex(int index) {
        //     nextLedOnIndex = index;
        // }
};

#endif // _SIGNAL_H_