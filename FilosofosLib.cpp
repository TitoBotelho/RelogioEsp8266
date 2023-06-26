#include "FilosofosLib.h"
#include "bibliotecaImagens.h"


FilosofosLib::FilosofosLib(int buttonPin)
  : buttonPin(buttonPin), lastButtonState(LOW), currentButtonState(LOW),
    contador(0), display(0x3c, 5, 4) {
}

void FilosofosLib::begin() {
  pinMode(buttonPin, INPUT);
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.display();
}

void FilosofosLib::update() {
  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.print("The button is pressed: ");
    contador = contador + 1;

    if (contador == 4) {
      contador = 1;
    }

    display.clear();
    display.display();

    if (contador == 1) {
      display.drawXbm(0, 0, 128, 64, marx);
    } else if (contador == 2) {
      display.drawXbm(0, 0, 128, 64, nietzsche);
    } else if (contador == 3) {
      display.drawXbm(0, 0, 128, 64, freud);
    }

    display.display();
  }
}
