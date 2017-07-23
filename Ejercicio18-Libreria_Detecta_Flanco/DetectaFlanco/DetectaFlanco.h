/*
  DetectaFlanco.h - Library for detecting button state change.
  Created by aprendiendoarduino, 2017.
  Released into the public domain.
*/
#ifndef DetectaFlanco_h
#define DetectaFlanco_h

#include "Arduino.h"

class DetectaFlanco {
  private:
    int _pin;
    boolean _anterior_estado;
    boolean _estado;

  public:
    DetectaFlanco(int pin);
    void inicio(int input);	//INPUT or INPUT_PULLUP
    int comprueba();
};

#endif