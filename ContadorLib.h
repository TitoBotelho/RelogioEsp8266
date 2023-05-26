#ifndef ContadorLib_h
#define ContadorLib_h

#include <Wire.h>
#include "SH1106Wire.h"

class ContadorLib {
public:
  ContadorLib(int buttonPin);

  void begin();
  void update();

private:
  int buttonPin;
  int ledState;
  int lastButtonState;
  int currentButtonState;
  int contadorLib; // Renomeada para evitar conflito de nomes
  String titulo;
  SH1106Wire display;
};

#endif
