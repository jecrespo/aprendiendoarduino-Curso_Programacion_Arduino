#include <Ethernet.h>
#include <SPI.h>
#include "Timer.h"

#define PIN_LDR A1
#define PIN_TMP36 A2

#define NUM_ARDUINO XX  //Sustituir XX por el numero de Arduino correcto

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x70, 0xYY};  //Sustituir YY por el numero de Arduino correcto
char url[] = "www.aprendiendoarduino.com";

EthernetClient client;
Timer t;

void setup() {

  Serial.begin(9600);

  //Inicializo Ethernet Shield
  Serial.println(F("Inicializando red..."));

  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Fallo en la configuracion Ethernet usando DHCP. Continuando resto de Tests"));
  }
  else {
    Serial.print(F("IP asignada por DHCP: "));
    Serial.println(Ethernet.localIP());
  }

  Serial.println("Iniciando datalogger...");
  delay(1000);
  t.every(5000, grabaDatos);
}

void loop() {
  t.update();
}

void grabaDatos() {
  Serial.println("leyendo dato temperatura... ");
  int sensorVal = analogRead(PIN_TMP36);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100; //Sonda temperatura kit Arduino
  Serial.print("Temperatura Leida: ");
  Serial.println(temperature);
  mandaRequest(temperature, NUM_ARDUINO);

  Serial.println("leyendo dato LDR... ");
  int LDRVal = analogRead(PIN_LDR);
  Serial.print("Valor Leido: ");
  Serial.println(LDRVal);
  mandaRequest(LDRVal, NUM_ARDUINO + 100);
}

void mandaRequest(float dato, int nodo) {
  Serial.println("connecting to server...");
  if (client.connect(url, 80)) {
    Serial.println("connected");
    client.print("GET /servicios/datos/grabaDatos.php?arduino=" + (String)nodo + "&dato=");
    client.print(dato);
    client.println(" HTTP/1.1");
    client.println("Host: www.aprendiendoarduino.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("connection failed");
    return 0;
  }

  while (client.available() == 0) {
    static int contador = 0;
    delay(10);
    contador ++;
    if (contador > 500) //5 segundos
      break;
  }

  if (client.available()) {
    String webString = "";
    Serial.println("Respuesta del Servidor---->");
    while (client.available()) {
      char c = client.read();
      webString += c;
    }
    Serial.println(webString);
    if (webString.indexOf("GRABADOS") > 0) Serial.println("Datos guardados correctamente");
    else Serial.println("Error al guardar los datos");

    client.stop();
  }
  else
    Serial.println("No hay respuesta del servidor");
}
