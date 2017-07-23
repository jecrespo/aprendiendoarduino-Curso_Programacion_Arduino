#include "Coche.h"

#define PIN_LED_4 7
#define PIN_BUZZER 8

Coche MiCoche(6, 7);

void setup() {
  Serial.begin(9600);
  MiCoche.Arranca();
}

void loop() {
  char valor = leeBluetooth();
  if (valor != 0) {
    switch (valor) {
      case 'F':
        MiCoche.Adelante(50);
        break;
      case 'R':
        MiCoche.Derecha();
        break;
      case 'L':
        MiCoche.Izquierda();
        break;
      case 'B':
        MiCoche.Atras(10);
        break;
      case 'S':
        MiCoche.Para();
        break;
      case 'E':
        MiCoche.EndiendeLuces(PIN_LED_4);
        break;
      case 'A':
        MiCoche.ApagaLuces(PIN_LED_4);
        break;
      case 'P':
        MiCoche.Pita(PIN_BUZZER, 2000);
        break;
      case 'G':
        Serial.println("El deposito tiene " + (String)MiCoche.LeeGasolina() + " litros");
        break;
      case 'D':
        MiCoche.EcharGasolina(10);
        break;
      default:
        Serial.println("Opcion incorrecta");
    }
  }
}

char leeBluetooth() {
  if (Serial.available() > 0) {
    char caracter_leido = Serial.read();
    delay(5);
    while (Serial.available() > 0) {
      Serial.read();  //Vacio Buffer
      delay(5);
    }
    return caracter_leido; //Solo devuelvo el primer caracter
  }
  else
    return 0;
}

