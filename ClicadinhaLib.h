#ifndef ClicadinhaLib_h
#define ClicadinhaLib_h

#include <Arduino.h>
#include <Wire.h>
#include <SH1106Wire.h>

class ClicadinhaLib {
public:
  ClicadinhaLib(int buttonPin);

  void begin();
  void update();

private:
  int buttonPin;
  int lastButtonState;
  int currentButtonState;
  int contador;
  SH1106Wire display;
};

#endif

