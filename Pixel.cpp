#include <FastLED.h>

class Pixel {
  public:
    bool isOn = false;
      
    CRGB colorOn = CRGB(70, 255, 0); // orange
    CRGB colorOff = CRGB(0, 0, 0); // black
    CRGB color = this->colorOff;

    void setIsOn(bool isOn) {
      if (isOn) {
        this->isOn = true;
        this->color = this->colorOn;
      } else {
        this->isOn = false;
        this->color = this->colorOff;
      }
    }
    
    CRGB show() {
      return this->color;
    }
};
