#include <Arduino.h>

#ifndef _TIMER_H_
#define _TIMER_H_

struct timerState {
  unsigned long prevLedOnMillis;
  int nextLedOnIndex;
};

class Timer {
  int _numLeds;

  unsigned long _prevLedOnMillis = 0;
  int _nextLedOnIndex = 0;
  unsigned long _intervalTurnOnNextLed = 250;

  public:
    Timer(int numLeds);

    timerState update();
    
    timerState reset();
};

#endif // _TIMER_H_