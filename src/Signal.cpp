#include "Signal.h"

Signal::Signal(int buttonPin, int numLeds) {
    pinMode(buttonPin, INPUT);
    _buttonPin = buttonPin;

    for (int i = 0; i < numLeds; i++) {

        Pixel pFront;
        pFront.setColors({
            full: CRGB(255, 255, 255),
            blink: CRGB(255, 70, 0),
            dark: CRGB(0, 0, 0)
        });
        frontPixels[i] = pFront;
        frontLeds[i] = pFront.getColor();

        Pixel pBack;
        pBack.setColors({
            full: CRGB(255, 0, 0),
            blink: CRGB(255, 70, 0),
            dark: CRGB(0, 0, 0)
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
    if (_isBlinking) {
        for (int i = 0; i < _numLeds; i++) {
            const bool shouldBeOn = _isBlinking && timerState.nextLedOnIndex >= i;
            frontPixels[i].setMode(shouldBeOn ? "blink" : "dark");
            frontLeds[i] = frontPixels[i].getColor();

            backPixels[i].setMode(shouldBeOn ? "blink" : "dark");
            backLeds[i] = backPixels[i].getColor();
        }
    } else {
        for (int i = 0; i < _numLeds; i++) {
            frontPixels[i].setMode("full");
            frontLeds[i] = frontPixels[i].getColor();

            backPixels[i].setMode("full");
            backLeds[i] = backPixels[i].getColor();
        }
    }
    FastLED.show();
}