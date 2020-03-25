#include "Signal.h"

Signal::Signal(int buttonPin, int ledPin, int numLeds) {
    pinMode(buttonPin, INPUT);
    _buttonPin = buttonPin;

    // _numLeds = numLeds;

    // for (int i = 0; i < numLeds; i++) {
    //     Pixel p;
    //     pixels[i] = p;
    //     leds[i] = p.color;
    // }

    // FastLED.addLeds<WS2812B, 2, RGB>(leds, numLeds);
    
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