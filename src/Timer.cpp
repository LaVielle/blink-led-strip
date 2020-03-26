#include "Timer.h"

Timer::Timer(int numLeds) {
  _numLeds = numLeds;
};

timerState Timer::update() {
  unsigned long currentMillis = millis();

  const bool timeReached = currentMillis - _prevLedOnMillis >= _intervalTurnOnNextLed;
  if (timeReached) {
    _prevLedOnMillis = currentMillis;
    _nextLedOnIndex += 1;

    if (_nextLedOnIndex >= _numLeds) {
      _nextLedOnIndex = -1;
    }
  }

  Serial.print("_nextLedOnIndex: ");
  Serial.println(_nextLedOnIndex);

  return {
    prevLedOnMillis: _prevLedOnMillis,
    nextLedOnIndex: _nextLedOnIndex,
  };
};

timerState Timer::reset() {
  _prevLedOnMillis = 0;
  _nextLedOnIndex = -1;

  return {
    prevLedOnMillis: _prevLedOnMillis,
    nextLedOnIndex: _nextLedOnIndex,
  };
};