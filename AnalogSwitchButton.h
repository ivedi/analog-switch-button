/*
 * AnalogSwitchButton.h - Basic switch button library
 * for analog readings.
 * Created by Halil İbrahim İvedi, August 15, 2023.
 * */
#ifndef AnalogSwitchButton_h
#define AnalogSwitchButton_h

#include "Arduino.h"

class AnalogSwitchButton
{
  public:
    AnalogSwitchButton(byte buttonPin, uint12_t bias);
    byte buttonPin;
    bool pressed;
    bool released;
    void begin();
    bool update(byte debounceTime = 50);
  private:
    int _currentState;
    int _lastFlickerableState;
    int _lastSteadyState;
    unsigned long _lastDebounceTime;
};

#endif
