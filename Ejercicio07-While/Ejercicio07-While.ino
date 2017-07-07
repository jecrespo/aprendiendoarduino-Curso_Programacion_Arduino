#define PIN_LED_1 4
#define PIN_LED_2 5 //PWM
#define PIN_LED_3 6 //PWM
#define PIN_LED_4 7

void setup() {
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);

  Serial.begin(9600);

  while (true) {
    static int i = 0;
    i++;
    if (i % 2 == 0)
      continue;

    if (i > 100)
      break;

    Serial.println(i);
  }
  Serial.println("Inicio parpadeo");
}

void loop() {
  for (int i = PIN_LED_1; i <= PIN_LED_4; i++) {
    digitalWrite(i, HIGH);
  }
  delay(1000);
  for (int i = PIN_LED_1; i <= PIN_LED_4; i++) {
    digitalWrite(i, LOW);
  }
  delay(1000);
}
