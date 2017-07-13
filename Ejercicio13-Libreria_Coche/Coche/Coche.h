#ifndef Coche_h
#define Coche_h

#define LITROS_DEPOSITO 60 //litros
#define NOTE_BUZZER  523

#include "Arduino.h"

class Coche {
  
  private:
    int _pinMotor1;
    int _pinMotor2;
    int _gasolinaDeposito = 10;
    boolean _estadoCoche; //0 averiado 1 OK
	boolean compruebaCoche();

  public:
    Coche(int pinMotor1, int pinMotor2);
    boolean Arranca();  // 1 OK, 0 no arranca
    void Adelante(int velocidad); //Cada paso quita 0.1 litros
    void Derecha ();
    void Izquierda();
    void Atras(int velocidad);
    void Para();
    void EndiendeLuces(int pinLuces);
    void ApagaLuces(int pinLuces);
    void Pita(int pinBuzzer, int tiempo);
    int LeeGasolina();
    int EcharGasolina(int litros);
};

#endif