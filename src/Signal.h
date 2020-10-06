#include <Arduino.h>
#include <FastLED.h>

#include "Timer.h"
#include "Pixel.h"

#ifndef _SIGNAL_H_
#define _SIGNAL_H_


class Signal {
    bool _isBlinking = false;
    int _buttonPin;
    int _numLeds = 10;

    public:

        Signal(int buttonPin, int numLeds);

        Pixel frontPixels[10];
        CRGB frontLeds[10];

        Pixel backPixels[10];
        CRGB backLeds[10];

        bool getIsBlinking();

        void toggleSignal();

        void blink(timerState timerState);
};

#endif // _SIGNAL_H_