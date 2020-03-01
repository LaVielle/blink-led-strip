#ifndef _SIGNAL_H_
#define _SIGNAL_H_

void tS(bool isBlinking) {
    isBlinking = !isBlinking;
}

class Signal {
    bool _isBlinking = false;
    int _numLeds = 3;

    public: 

        unsigned long prevLedOnMillis = 0;
        int nextLedOnIndex = 0;

        Pixel pixels[3] = {};
        CRGB leds[3] = {};

        void toggleSignal() {
            tS(_isBlinking);
        }

        Signal(int buttonPin, int ledPin, int numLeds) {
            pinMode(buttonPin, INPUT);

            attachInterrupt(
                digitalPinToInterrupt(buttonPin),
                tS(_isBlinking),
                RISING
            );

            _numLeds = numLeds;

            for (int i = 0; i < numLeds; i++) {
                Pixel p;
                pixels[i] = p;
                leds[i] = p.color;
            }

            FastLED.addLeds<WS2812B, 2, RGB>(leds, numLeds);
            
        }

        void setPrevLedOnMillis(unsigned long timestamp) {
            prevLedOnMillis = timestamp;
        }

        void setNextLedOnIndex(int index) {
            nextLedOnIndex = index;
        }
};

#endif // _SIGNAL_H_