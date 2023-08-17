#include <AnalogSwitchButton.h>

// define which pin to use as analog switch button:
#define BUTTON_PIN 13

// determine voltage bias to switch button state:
uint16_t switchPoint = 2048; // Note: 4096 is max value for 3.3V analogRead on ESP32 microcontroller

// initialize analog-switch-button:
AnalogSwitchButton button = AnalogSwitchButton(BUTTON_PIN, switchPoint);

void setup() {
  // initialize serial communication at 115200 bits per second to debug:
  Serial.begin(115200);
}

void loop() {
  // update the button's state
  if (button.update()) {
    if (button.pressed) {
      Serial.println("Button is pressed...");
    } else if (button.released) {
      Serial.println("Button is released...");
    }
  }
}
