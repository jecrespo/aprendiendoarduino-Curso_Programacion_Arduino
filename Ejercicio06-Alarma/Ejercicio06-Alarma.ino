#define PIN_BUZZER 8
#define PIN_TMP36 A2
#define UMBRAL 28
#define NOTE_C5  523  //Frecuencia de sonido del buzzer

boolean alarma_temperatura;

void setup() {
  Serial.begin(9600);
  if (lee_temperatura () > UMBRAL) {
    alarma_temperatura = true;
    tone(PIN_BUZZER, NOTE_C5);
    Serial.println("ALARMA!!");
  }
  else {
    alarma_temperatura = false;
    noTone(PIN_BUZZER);
  }
}

void loop() {
  if (lee_temperatura () > UMBRAL) {
    if (!alarma_temperatura) {
      alarma_temperatura = true;
      tone(PIN_BUZZER, NOTE_C5);
      Serial.println("ALARMA!!");
    }
  }
  else {
    if (alarma_temperatura) {
      alarma_temperatura = false;
      noTone(PIN_BUZZER);
      Serial.println("RECUPERACION ALARMA");
    }
  }
}

float lee_temperatura () {
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(PIN_TMP36);

  // converting that reading to voltage
  float voltage = reading * 5.0 / 1023.0;

  // now print out the temperature
  //converting from 10 mv per degree with 500 mV offset
  float temperatureC = (voltage - 0.5) * 100 ;

  return temperatureC;
}

