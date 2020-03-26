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
        pixels[i].setIsOn(shouldBeOn);
        leds[i] = pixels[i].getColor();
    }
    FastLED.show();
}