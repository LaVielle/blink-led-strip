#include <Arduino.h>
#include <FastLED.h>

#ifndef _PIXEL_H_
#define _PIXEL_H_

struct ColorMode {
  CRGB full;
  CRGB blink;
  CRGB dark;
};


class Pixel {
  String _colorMode = "dark";
  ColorMode _colors;

  public:
    void setColors(ColorMode colors);
    
    void setMode(String mode);

    String getMode();

    CRGB getColor();
};

#endif // _PIXEL_H_