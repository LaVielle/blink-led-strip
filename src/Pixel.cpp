# include "Pixel.h"

void Pixel::setColors(ColorMode colors) {
    _colors = colors;
};

void Pixel::setMode(String mode) {
    _colorMode = mode;
};

String Pixel::getMode() {
    return _colorMode;
};

CRGB Pixel::getColor() {
    if (_colorMode == "full") {
        return _colors.full;
    };
    if (_colorMode == "blink") {
        return _colors.blink;
    };
    if (_colorMode == "dark") {
        return _colors.dark;
    };
    return _colors.full;
};
