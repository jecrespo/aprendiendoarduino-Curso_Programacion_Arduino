#include "Coche.h"

Coche::Coche(int pinMotor1, int pinMotor2){
	_pinMotor1 = pinMotor1;
	_pinMotor2 = pinMotor2;
}

boolean Coche::Arranca() {
  pinMode(_pinMotor1, OUTPUT);
  pinMode(_pinMotor2, OUTPUT);

  if (_gasolinaDeposito < 2) {
  	_estadoCoche = 1;
  	return 0;
  }
  else {
  	_estadoCoche = 0;
  	return 1;
  }
}

void Coche::Adelante(int velocidad) {
	velocidad = constrain(velocidad,0,100);
	analogWrite(_pinMotor1, velocidad);
  	analogWrite(_pinMotor2, velocidad);
  	_gasolinaDeposito -= velocidad * 0.1;
  	this -> compruebaCoche();
	Serial.println("Coche Adelante a velocidad: " + (String)velocidad);
}

void Coche::Derecha () {
	analogWrite(_pinMotor1, 0);
	Serial.println("Coche Gira a la Derecha");
}

void Coche::Izquierda() {
	analogWrite(_pinMotor2, 0);
	Serial.println("Coche Gira a la Izquierda");
}

void Coche::Atras(int velocidad) {
	velocidad = constrain(velocidad,0,10);
	analogWrite(_pinMotor1, -velocidad);
  	analogWrite(_pinMotor2, -velocidad);
  	_gasolinaDeposito -= velocidad * 0.1;
	Serial.println("Coche Atras a velocidad: " + (String)velocidad);
}

void Coche::Para() {
	analogWrite(_pinMotor1, 0);
  	analogWrite(_pinMotor2, 0);
	Serial.println("Coche Parado");
}

void Coche::EndiendeLuces(int pinLuces) {
	pinMode(pinLuces, OUTPUT);
	digitalWrite(pinLuces,HIGH);
	Serial.println("Enciendo Luces");
}

void Coche::ApagaLuces(int pinLuces) {
	digitalWrite(pinLuces,LOW);
	Serial.println("Apago Luces");
}

void Coche::Pita(int pinBuzzer, int tiempo) {
	tone(pinBuzzer, NOTE_BUZZER);
	delay(tiempo);
	noTone(pinBuzzer);
	Serial.println("Pito");
}

int Coche::LeeGasolina() {
	return _gasolinaDeposito;
}

int Coche::EcharGasolina(int litros) {
	_gasolinaDeposito += litros;
	_gasolinaDeposito = constrain(_gasolinaDeposito,0,LITROS_DEPOSITO);
	return _gasolinaDeposito;
}

boolean Coche::compruebaCoche() {
	return _estadoCoche;
}