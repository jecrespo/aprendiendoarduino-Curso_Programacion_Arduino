#include <DetectaFlanco.h>
#include <Ethernet.h>
#include <SPI.h>

#define PIN_BOTON_A 2
#define PIN_BOTON_B 3

#define MENSAJE_A "Mensaje_A"
#define MENSAJE_B "Mensaje_B"
#define TELEFONO "600000000"

#define NUM_ARDUINO "XX"  //Sustituir XX por el numero de Arduino correcto

#define PIN "0000"

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xYY}; //Sustituir YY por el numero de KIT de Arduino
char url[] = "www.aprendiendoarduino.com";

EthernetClient client;

DetectaFlanco DF1(PIN_BOTON_A), DF2(PIN_BOTON_B);

void setup() {
  Serial.begin(9600);

  DF1.inicio(INPUT_PULLUP);
  DF2.inicio(INPUT);

  //Inicializo Ethernet Shield
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
  if (DF1.comprueba() == -1) {
    Serial.println("Pulsado boton con resistencia de pullup");
    MandaSMS(TELEFONO, MENSAJE_A);
  }

  if (DF2.comprueba() == 1) {
    Serial.println("Pulsado boton con resistencia de pulldown");
    MandaMensaje(NUM_ARDUINO, MENSAJE_B);
  }

  delay(50); //Evitar rebotes
}

void MandaMensaje(String nombre, String mensaje) {
  Serial.println("enviando mensaje... ");
  Serial.println("connecting to server...");
  if (client.connect(url, 80)) {
    Serial.println("connected");
    client.print("GET /servicios/mensajes/grabaMensajes.php?nombre=");
    client.print(nombre);
    client.print("&mensaje=");
    client.print(mensaje);
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

void MandaSMS(String telefono, String mensaje) {
  Serial.println("enviando mensaje... ");

  Serial.println("connecting to server...");
  if (client.connect(url, 80)) {
    Serial.println("connected");
    client.print("GET /servicios/SMS/saveSMS.php?telefono=");
    client.print(telefono);
    client.print("&mensaje=");
    client.print(mensaje);
    client.print("&pin=");
    client.print((String)PIN);
    client.println(" HTTP/1.1");
    client.println("Host: www.aprendiendoarduino.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("connection failed");
    return;
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
