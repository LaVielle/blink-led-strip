#include <Arduino.h>
#include <FastLED.h>

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

// void tS(bool isBlinking) {
//     isBlinking = !isBlinking;
// }

class Signal {
    bool _isBlinking = false;
    int _buttonPin;

    public:

        Signal(int buttonPin, int ledPin, int numLeds);

        // unsigned long prevLedOnMillis = 0;
        // int nextLedOnIndex = 0;

        // Pixel pixels[3] = {};
        // CRGB leds[3] = {};

        // // void toggleSignal() {
        // //     tS(_isBlinking);
        // // }

        void toggleSignal();
        
        void setupButtonInterrupt(void (*userFunc)(void));

        // void setPrevLedOnMillis(unsigned long timestamp) {
        //     prevLedOnMillis = timestamp;
        // }

        // void setNextLedOnIndex(int index) {
        //     nextLedOnIndex = index;
        // }
};

#endif // _SIGNAL_H_