/*
   Ejercicio01 - Test del entrono de trabajo para el curso Programación con Arduino
   Web: http://www.aprendiendoarduino.com/programacion-arduino/
   Montaje: https://aprendiendoarduino.files.wordpress.com/2017/07/curso_programacion-montaje_bb.jpg
*/

//Librerías necesarias para Ethernet Shield
#include <Ethernet.h>
#include <SPI.h>

//Librería Servo
#include <Servo.h>

//PINES
#define PIN_BOTON_A 2
#define PIN_BOTON_B 3
#define PIN_LED_1 4
#define PIN_LED_2 5 //PWM
#define PIN_LED_3 6 //PWM
#define PIN_LED_4 7
#define PIN_BUZZER 8
#define PIN_SERVO 9
#define PIN_POT A0
#define PIN_LDR A1
#define PIN_TMP36 A2

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAA}; //Sustituir YY por el numero de KIT de Arduino

Servo miservo;

void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);

  //Inicializo Pines
  Serial.println("Inicializando pines digitales...");
  pinMode(PIN_BOTON_A, INPUT_PULLUP);
  pinMode(PIN_BOTON_B, INPUT);
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);

  //Inicializo Servo
  Serial.println("Inicializando servo...");
  miservo.attach(PIN_SERVO);

  //Inicializo Ethernet Shield
  Serial.println("Inicializando red...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Fallo en la configuracion Ethernet usando DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP asignada por DHCP: ");
    Serial.println(Ethernet.localIP());
  }
}

void loop() {
  muestraMenu();
  int respuesta = recogeRespuesta();

  switch (respuesta) {
    case 1:
      muestraIP();
      break;
    case 2:
      pruebaBotones();
      break;
    case 3:
      pruebaLEDs();
      break;
    case 4:
      pruebaPWM();
      break;
    case 5:
      pruebaPotenciometro();
      break;
    case 6:
      pruebaLDR();
      break;
    case 7:
      pruebaTemperatura();
      break;
    case 8:
      pruebaServo();
      break;
    case 9:
      pruebaBuzzer();
      break;
    case 10:
      pruebaClienteWeb();
      break;
    case 11:
      pruebaServidorWeb();
      break;
    default:
      Serial.println("Opcion incorrecta.\nVuelve a introducir test a realizar");
      break;
  }
}

void muestraMenu() {
  Serial.println("------------------------");
  Serial.println("MENU");
  Serial.println("Selecciona el test a ejecutar");
  Serial.println("Una vez dentro del test pulsar 'q' para salir.");
  Serial.println("1 - Muestra IP Arduino");
  Serial.println("2 - Prueba Botones (comprobar pulsaciones correctas)");
  Serial.println("3 - Prueba LEDs (Iluminación LEDs)");
  Serial.println("4 - Prueba PWM (No todos los LEDs son PWM)");
  Serial.println("5 - Prueba Potenciometro (comprobar que va de 0 a 1023)");
  Serial.println("6 - Prueba LDR (ver valores máximo y mínimo. Anotarlos)");
  Serial.println("7 - Sonda temperatura (comprueba valores)");
  Serial.println("8 - Test Servo (comprobar el movimiento completo)");
  Serial.println("9 - Test Buzzer (comprobar sonido)");
  Serial.println("10 - Test Cliente Web (comprobar respuesta del servidor)");
  Serial.println("11 - Test Servidor Web (comprobar servidor embebido en Arduino)");
  Serial.println("------------------------");
}

int recogeRespuesta() {
  int segundos = 0;
  String cadena_leida = "";

  while (Serial.available() == 0) {
    if (segundos > 10) {
      segundos = 0;
      Serial.println("\nEsperando respuesta...");
      muestraMenu();
    }
    Serial.print(".");
    segundos++;
    delay(1000);
  }

  if (Serial.available() > 0) {
    do {
      char caracter_leido = Serial.read();
      cadena_leida += caracter_leido;
      delay(5);
    }  while (Serial.available() > 0);

    Serial.print("He Leido la cadena: " + cadena_leida);

    int respuesta = cadena_leida.toInt();
    return respuesta;
  }
}

void muestraIP() {
  Serial.println("Muestra IP Arduino");
}

void pruebaBotones() {
  Serial.println("Prueba Botones");
}

void pruebaLEDs() {
  Serial.println("Prueba LEDs");
}

void pruebaPWM() {
  Serial.println("Prueba PWM");
}

void pruebaPotenciometro() {
  Serial.println("Prueba Potenciometro");
}

void pruebaLDR() {
  Serial.println("Prueba LDR");
}

void pruebaTemperatura() {
  Serial.println("Sonda temperatura");
}

void pruebaServo() {
  Serial.println("Test Servo");
}

void pruebaBuzzer() {
  Serial.println("Test Buzzer");
}

void  pruebaClienteWeb() {
  Serial.println("Test Cliente Web");
}

void  pruebaServidorWeb() {
  Serial.println("Test Servidor Web");
}
