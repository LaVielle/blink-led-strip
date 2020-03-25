#include <Arduino.h>
#include <FastLED.h>

#ifndef _PIXEL_H_
#define _PIXEL_H_


class Pixel {
  bool _isOn = false;
  CRGB _color = CRGB(0, 0, 0); // black

  public:
    void setIsOn(bool isOn);

    CRGB getColor();
};

#endif // _PIXEL_H_