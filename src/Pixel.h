#include <Arduino.h>
#include <FastLED.h>

#ifndef _PIXEL_H_
#define _PIXEL_H_


class Pixel {
  bool _isOn = false;
  CRGB _color = CRGB(0, 0, 0); // black

  public:
    void setIsOn(bool isOn);

    bool getIsOn();

    CRGB getColor();

    CRGB colorOn = CRGB(70, 255, 0);
    CRGB colorOff = CRGB(0, 0, 0);
};

#endif // _PIXEL_H_