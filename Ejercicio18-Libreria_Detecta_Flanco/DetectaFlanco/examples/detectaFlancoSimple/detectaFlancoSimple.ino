#include "DetectaFlanco.h"

#define PIN_BOTON_A 2
#define PIN_BOTON_B 3

DetectaFlanco DF1(PIN_BOTON_A), DF2(PIN_BOTON_B);

void setup() {
  Serial.begin(9600);
  DF1.inicio(INPUT_PULLUP);
  DF2.inicio(INPUT);
}

void loop() {
  if (DF1.comprueba() == -1) {
    Serial.println("Pulsado boton con resistencia de pullup");
  }

  if (DF2.comprueba() == 1) {
    Serial.println("Pulsado boton con resistencia de pulldown");
  }

  delay(50); //Evitar rebotes
}

