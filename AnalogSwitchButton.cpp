/*
 * AnalogSwitchButton.cpp - Basic switch button library
 * for analog readings.
 * Created by Halil İbrahim İvedi, August 15, 2023.
 * */

#include "Arduino.h"
#include "AnalogSwitchButton.h"

AnalogSwitchButton::AnalogSwitchButton(uint8_t pin, uint16_t bias) {
  buttonPin = pin;
  bias = bias;
  pressed = false;
  released = true;
  _currentState = false;
  _lastFlickerableState = false;
  _lastSteadyState = false;
  _lastDebounceTime = 0;
}

bool AnalogSwitchButton::update(uint8_t debounceTime) {
  bool stateChanged = false;
  // read the state of the pin
  uint16_t currentVoltage = analogRead(buttonPin);
  _currentState = currentVoltage > bias;

  // check to see if you just pressed enough the button
  // and you've waited long enough
  // since the last press to ignore any noise:
  
  // If the button changed, due to noise or presssing:
  if (_currentState != _lastFlickerableState) {
    // reset the bouncing timer
    _lastDebounceTime = millis();
    // save the last flickerable state
    _lastFlickerableState = _currentState;
  }

  if((millis() - _lastDebounceTime) > debounceTime) {
    // whatever the reading is at, it's been there for longer than
    // debounce delay, so take it as the actual current state:

    // if the button has changed:
    if (_lastSteadyState == false && _currentState == true) {
      pressed = true;
      released = false;
      stateChanged = true;
    } else if (_lastSteadyState == true && _currentState == false) {
      pressed = false;
      released = true;
      stateChanged = true;
    }

    // save the last steady state
    _lastSteadyState = _currentState;
  }

  return stateChanged;
}
