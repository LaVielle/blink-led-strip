#include <Arduino.h>
#include <FastLED.h>

#ifndef _PIXEL_H_
#define _PIXEL_H_

struct ColorOnOff {
  CRGB on;
  CRGB off;
};


class Pixel {
  bool _isOn = false;
  ColorOnOff _colors;

  public:
    void setColors(ColorOnOff colors);
    
    void setIsOn(bool isOn);

    bool getIsOn();

    CRGB getColor();
};

#endif // _PIXEL_H_