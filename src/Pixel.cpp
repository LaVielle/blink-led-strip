# include "Pixel.h"

void Pixel::setColors(ColorOnOff colors) {
    _colors = colors;
};

void Pixel::setIsOn(bool isOn) {
    _isOn = isOn;
};

bool Pixel::getIsOn() {
    return _isOn;
};

CRGB Pixel::getColor() {
    if (_isOn) {
        return _colors.on;
    }
    return _colors.off;
};
