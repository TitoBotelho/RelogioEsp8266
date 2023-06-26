#ifndef FilosofosLib_h
#define FilosofosLib_h

#include <Arduino.h>
#include <Wire.h>
#include <SH1106Wire.h>

class FilosofosLib {
public:
  FilosofosLib(int buttonPin);

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

