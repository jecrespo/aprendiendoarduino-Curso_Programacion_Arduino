#include <DetectaFlanco.h>

DetectaFlanco Dhola1(pin1);
DetectaFlanco Dhola2(pin2);

void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int flanco1 = Dhola1.flanco();
  int flanco2 = Dhola2.flanco();

  if (flanco1 == 1)
    Serial.println("Flanco asc A");
  if (flanco1 == -1)
    Serial.println("Flanco desc A");
  if (flanco2 == 1)
    Serial.println("Flanco asc B");
  if (flanco2== -1)
    Serial.println("Flanco asc B");
}
