# include "Pixel.h"

void Pixel::setIsOn(bool isOn) {
    _isOn = isOn;
    _color = isOn ? colorOn : colorOff;
};

bool Pixel::getIsOn() {
    return _isOn;
};

CRGB Pixel::getColor() {
    return _color;
};
