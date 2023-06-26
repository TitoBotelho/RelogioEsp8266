#include "ClicadinhaLib.h"
#include "bibliotecaImagens.h"


ClicadinhaLib::ClicadinhaLib(int buttonPin)
  : buttonPin(buttonPin), lastButtonState(LOW), currentButtonState(LOW),
    contador(0), display(0x3c, 5, 4) {
}

void ClicadinhaLib::begin() {
  pinMode(buttonPin, INPUT);
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.display();
}

void ClicadinhaLib::update() {
  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.print("The button is pressed: ");
    contador = contador + 1;

    if (contador == 5) {
      contador = 1;
    }

    display.clear();
    display.display();

    if (contador == 1) {
      display.drawXbm(0, 0, 128, 64, RoboNormal);
    } else if (contador == 2) {
      display.drawXbm(0, 0, 128, 64, RoboPiscando);
    } else if (contador == 3) {
      display.drawXbm(0, 0, 128, 64, RoboBravo);
    } else if (contador == 4) {
      display.drawXbm(0, 0, 128, 64, RoboTriste);
    }

    display.display();
  }
}
