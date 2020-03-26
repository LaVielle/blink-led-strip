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

        const bool timeReached = currentMillis - _prevLedOnMillis >= _intervalTurnOnNextLed;

        if (timeReached) {
            Serial.println("time reached");

            _prevLedOnMillis = currentMillis;
            
            for (int i = 0; i < _numLeds; i++) {
                Pixel p = pixels[i];
                bool isOn = p.getIsOn();
                p.setIsOn(!isOn);

                pixels[i] = p;

                leds[i] = p.getColor();
            }
        }

        FastLED.show();
    }
}