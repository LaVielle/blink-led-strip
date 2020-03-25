# include "Pixel.h"

void Pixel::setIsOn(bool isOn) {
    _isOn = isOn;
};

CRGB Pixel::getColor() {
    return _color;
};
