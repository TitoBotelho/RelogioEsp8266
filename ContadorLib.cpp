#include "ContadorLib.h"

ContadorLib::ContadorLib(int buttonPin)
  : buttonPin(buttonPin), ledState(LOW), lastButtonState(LOW), currentButtonState(LOW),
    contadorLib(0), titulo("Contador:"), display(0x3c, 5, 4) {
}

void ContadorLib::begin() {

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER);

  currentButtonState = digitalRead(buttonPin);
}
void ContadorLib::update() {
  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.print("The button is pressed: ");

    contadorLib = contadorLib + 1;

    String contadorString = String(contadorLib);

    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(62, 5, titulo);
    display.setFont(ArialMT_Plain_24);
    display.drawString(62, 30, contadorString);
    display.display();
  }
}