#include <Arduino.h>
#include <FastLED.h>

#include "Timer.h"
#include "Pixel.h"

#ifndef _SIGNAL_H_
#define _SIGNAL_H_


class Signal {
    bool _isBlinking = false;
    int _buttonPin;
    int _numLeds = 3;

    public:

        Signal(int buttonPin, int numLeds);

        Pixel frontPixels[3];
        CRGB frontLeds[3];

        Pixel backPixels[3];
        CRGB backLeds[3];

        bool getIsBlinking();

        void toggleSignal();

        void setupButtonInterrupt(void (*userFunc)(void));

        void blink(timerState timerState);
};

#endif // _SIGNAL_H_