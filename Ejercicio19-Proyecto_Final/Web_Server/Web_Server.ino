#include <Ethernet.h>
#include <SPI.h>
#include <Servo.h>

#define PIN_LED_1 4
#define PIN_LED_2 5 //PWM
#define PIN_LED_3 6 //PWM
#define PIN_LED_4 7
#define PIN_SERVO 9

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xYY}; //Sustituir YY por el numero de KIT de Arduino
EthernetServer server = EthernetServer(80);

Servo miservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Inicializo Pines
  Serial.println(F("Inicializando pines digitales..."));
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);

  Serial.println(F("Inicializando servo..."));
  miservo.attach(PIN_SERVO);

  Serial.println(F("Inicializando red..."));

  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Fallo en la configuracion Ethernet usando DHCP. Continuando resto de Tests"));
  }
  else {
    Serial.print(F("IP asignada por DHCP: "));
    Serial.println(Ethernet.localIP());
  }
}

void loop() {
  EthernetClient client = server.available();
  if (client > 0) {
    String peticion_web = "";

    while (client.available() > 0) {
      char inChar = client.read();
      peticion_web += inChar;
    }

    Serial.println("El servidor ha recibido: " +  peticion_web);
    if (peticion_web.startsWith("GET / HTTP"))
      muestraWeb(client);
    else if (peticion_web.startsWith("POST /led"))
      cambioLed(client);
    else if (peticion_web.startsWith("POST /servo"))
      cambioServo(client);
    else {
      client.println(F("HTTP/1.1 200 OK"));
      client.println(F("Content-Type: text/html\r\n"));
      client.println();
      client.println(F("Peticion no registrada"));
      client.stop();  //Cierro el cliente
    }
  }
}

void muestraWeb(EthernetClient client_web) {
  client_web.println(F("HTTP/1.0 200K"));
  client_web.println();
  client_web.println("<!DOCTYPE html>");
  client_web.println("<html>");
  client_web.println("<body>");
  client_web.print(F("<p>Servidor embebido del Arduino con IP: "));
  client_web.print(Ethernet.localIP());
  client_web.println("</p>");
  client_web.print(F("<p>Led 1"));
  client_web.println("<form action=\"led\" method=\"post\">");
  client_web.println("<input type=\"submit\" value=\"Cambia Led\" />");
  client_web.println("</form>");
  client_web.println("</p>");
  client_web.println("</p>");
  client_web.print(F("<p>Servo"));
  client_web.println("<form action=\"servo\" method=\"post\">");
  client_web.println("<input type=\"submit\" value=\"Cambia servo\" />");
  client_web.println("</form>");
  client_web.println("</p>");
  client_web.println("</body>");
  client_web.println("</html>");
  client_web.println();
  client_web.stop();
}

void cambioLed(EthernetClient client_web) {
  int estadoLed = digitalRead(PIN_LED_1);
  digitalWrite(PIN_LED_1, !estadoLed);
  Serial.println("Pongo el led a " + (String)!estadoLed);
  muestraWeb(client_web);
}

void cambioServo(EthernetClient client_web) {
  int angulo = miservo.read();
  angulo += 10;
  if (angulo >= 170)
    miservo.write(10);
  else
    miservo.write(angulo);

  Serial.println("Muevo el servo a " + (String)angulo);
  muestraWeb(client_web);
}

