#include <Wire.h>
#include "SH1106Wire.h"

#include "ContadorLib.h"
#include "bibliotecaImagens.h"

// constants won't change
const int BUTTON_1 = 0;  // Connect the Button to pin 7 or change here
const int BUTTON_2 = 2;

// variables will change:
int lastButtonState1;     // the previous state of button
int currentButtonState1;  // the current state of button

// variables will change:
int lastButtonState2;     // the previous state of button
int currentButtonState2;  // the current state of button

int escolhaMenu = 0;  // the current state of button


//Declarar um array com os itens do Menu
const int NUM_ITEMS = 6;
char menuItems[NUM_ITEMS][20] = {
  { "Contador" },
  { "Filosofos" },
  { "Relógio" },
  { "Clicadinha" },
  { "quinto" },
  { "sexto" }
};

int contador = 0;
int anterior = NUM_ITEMS - 1;
int posterior = contador + 1;

//Instanciamento do objeto da biblioteca do display
SH1106Wire display(0x3c, 5, 4);

ContadorLib contadorLib(BUTTON_2);

//Declaração da função menu rotativo
void funcaoMenuRotativo() {
  if (lastButtonState1 == HIGH && currentButtonState1 == LOW) {
    contador = contador + 1;
    anterior = contador - 1;
    posterior = contador + 1;

    if (contador == 6) {
      contador = 0;
    }
    if (anterior < 0) {
      anterior = (NUM_ITEMS - 1);
    }
    if (posterior > (NUM_ITEMS - 1)) {
      posterior = 0;
    }

    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawString(10, 7, menuItems[anterior]);
    display.setFont(ArialMT_Plain_16);
    display.drawString(10, 25, menuItems[contador]);
    display.setFont(ArialMT_Plain_10);
    display.drawString(10, 47, menuItems[posterior]);
    display.display();
  }
};

void setup() {
  pinMode(BUTTON_1, INPUT);  // set arduino pin to input mode
  pinMode(BUTTON_2, INPUT);  // set arduino pin to input mode

  display.init();
  display.flipScreenVertically();

  contadorLib.begin();


  currentButtonState1 = digitalRead(BUTTON_1);
  currentButtonState2 = digitalRead(BUTTON_2);

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(10, 7, menuItems[anterior]);
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 25, menuItems[contador]);
  display.setFont(ArialMT_Plain_10);
  display.drawString(10, 47, menuItems[posterior]);
  display.display();
}
void loop() {
  lastButtonState1 = currentButtonState1;       // save the last state
  currentButtonState1 = digitalRead(BUTTON_1);  // read new state

  lastButtonState2 = currentButtonState2;  // save the last state
  currentButtonState2 = digitalRead(BUTTON_2);

  if (lastButtonState2 == HIGH && currentButtonState2 == LOW) {
    escolhaMenu = 1;
  }

  if (escolhaMenu == 0) {
    // Chamar a função menu rotativo
    funcaoMenuRotativo();
  } else if (escolhaMenu == 1) {
    display.clear();
    display.display();
    if (strcmp(menuItems[contador], "Contador") == 0) {
      contadorLib.update();
    } else {
      escolhaMenu = 0;
    }
  }
}