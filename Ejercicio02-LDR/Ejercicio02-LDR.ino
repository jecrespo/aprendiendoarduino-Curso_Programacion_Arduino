#define PIN_LDR A1

int maximo = 0;
int minimo = 1023;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(PIN_LDR);
  maximo = max(maximo,sensorValue);
  minimo = min(minimo,sensorValue);
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.print(maximo);
  Serial.print(",");
  Serial.println(minimo);
  delay(500);
}
