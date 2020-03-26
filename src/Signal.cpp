#include "Signal.h"

Signal::Signal(int buttonPin, int ledPin, int numLeds) {
    pinMode(buttonPin, INPUT);
    _buttonPin = buttonPin;

    for (int i = 0; i < numLeds; i++) {
        Pixel p;
        pixels[i] = p;
        leds[i] = p.getColor();
    }    
};

void Signal::setupButtonInterrupt(void (*userFunc)(void)) {
    Serial.println("Signal::setupButtonInterrupt");
    attachInterrupt(
        digitalPinToInterrupt(_buttonPin),
        userFunc,
        RISING
    );
}

void Signal::toggleSignal(){
    _isBlinking = !_isBlinking;
    Serial.println("Signal::toggleSignal");
}

void Signal::blink(){

    if (_isBlinking) {
        unsigned long currentMillis = millis();
            
        for (int i = 0; i < _numLeds; i++) {

            const bool timeReached = currentMillis - _prevLedOnMillis >= _intervalTurnOnNextLed;
            const bool isCorrectIndex = i == _nextLedOnIndex;

            if (timeReached && isCorrectIndex) {
                // turn on current led
                pixels[i].setIsOn(true);
                leds[i] = pixels[i].getColor();

                // set turn on time and index for next led
                _prevLedOnMillis = currentMillis;
                _nextLedOnIndex = i + 1;
            }
        }

        const bool timeToResetReached = currentMillis - _prevLedOnMillis >= _intervalTurnOnNextLed;
        
        if (timeToResetReached && _nextLedOnIndex >= _numLeds) {
            for (int i = 0; i < _numLeds; i++) {
                pixels[i].setIsOn(false);
                leds[i] = pixels[i].getColor();
            }

            _prevLedOnMillis = currentMillis;
            _nextLedOnIndex = 0;
        }
    } else {
        _nextLedOnIndex = 0;
        
        for (int i = 0; i < _numLeds; i++) {
            pixels[i].setIsOn(false);
            leds[i] = pixels[i].getColor();
        }
    }

    FastLED.show();
}