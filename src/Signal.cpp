#include "Signal.h"

Signal::Signal(int buttonPin, int numLeds) {
    pinMode(buttonPin, INPUT);
    _buttonPin = buttonPin;

    for (int i = 0; i < numLeds; i++) {

        Pixel pFront;
        pFront.setColors({
            on: CRGB(255, 70, 0),
            off: CRGB(255, 255, 255)
        });
        frontPixels[i] = pFront;
        frontLeds[i] = pFront.getColor();

        Pixel pBack;
        pBack.setColors({
            on: CRGB(255, 70, 0),
            off: CRGB(255, 0, 0)
        });
        backPixels[i] = pBack;
        backLeds[i] = pBack.getColor();
    }    
};

bool Signal::getIsBlinking() {
    return _isBlinking;
}

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

void Signal::blink(timerState timerState){
    for (int i = 0; i < _numLeds; i++) {
        const bool shouldBeOn = _isBlinking && timerState.nextLedOnIndex >= i;
        frontPixels[i].setIsOn(shouldBeOn);
        frontLeds[i] = frontPixels[i].getColor();

        backPixels[i].setIsOn(shouldBeOn);
        backLeds[i] = backPixels[i].getColor();
    }
    FastLED.show();
}