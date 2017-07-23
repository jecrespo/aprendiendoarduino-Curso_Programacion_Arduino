#include <TimeLib.h> //https://github.com/PaulStoffregen/Time
#include <Timezone.h> //https://github.com/JChristensen/Timezone
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <simpleNTP.h>  //https://github.com/jecrespo/simpleNTP

simpleNTP ntp;  //simpleNTP object

//Spain Time Zone (Madrid) https://www.timeanddate.com/worldclock/spain/madrid
TimeChangeRule myDST = {"SDT", Last, Sun, Mar, 2, 120};    //Daylight time = UTC + 2 hours
TimeChangeRule mySTD = {"SST", Last, Sun, Oct, 2, 60};     //Standard time = UTC + 1 hours
Timezone myTZ(myDST, mySTD);

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x70, 0xYY};  //Sustituir YY por el numero de MAC correcto

String dia_semana[] = {"","domingo", "lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo"};

void setup() {
  Serial.begin(9600);

  //Inicializar Ethernet
  Serial.println("inicializando red...");

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP asignada por DHCP: ");
    Serial.println(Ethernet.localIP());
  }
  delay(500);

  Serial.println("Requesting Time...");
  unsigned long utc = ntp.readNTP();  //UTC time
  setTime(utc);
  Serial.print("Hora recibida: ");
  Serial.println(utc);
  digitalClockDisplay();

  utc = myTZ.toLocal(utc);
  setTime(utc);
  Serial.print("Hora corregida: ");
  Serial.println(utc);
  digitalClockDisplay();
}

void loop() {
  Serial.println("Hora interna en segundos (unix time): " + (String)now());
  digitalClockDisplay();
  delay(1000);

}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
  Serial.println("Hoy es " + dia_semana[weekday()]);
}

void printDigits(int digits) {
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
