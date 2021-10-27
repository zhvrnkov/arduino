#include "MQ135.h"
#include <LCD_I2C.h>
#include <DHT.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define SPEAKER A1
#define PERIOD_SEC 10

DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

MQ135 gasSensor = MQ135(A0);
LCD_I2C lcd(0x27);

float hum;
float temp;
float ppm;
float rzero;
unsigned int time = 0;

bool shouldScream(float ppm) {
  return ppm > 1200.0f;
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  if (time % (PERIOD_SEC * 1000) == 0) {
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    ppm = gasSensor.getCorrectedPPM(temp, hum);
    rzero = gasSensor.getCorrectedRZero(temp, hum);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("C:");
    lcd.print(int(ppm));
    lcd.print(" ");
    lcd.print("R:");
    lcd.print(int(rzero));
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(int(temp));
    lcd.print(" ");
    lcd.print("H:");
    lcd.print(int(hum));
  }
  
  if (shouldScream(ppm)) {
    tone(SPEAKER, max(0.1, abs(sinf(((float)time) / 1000.0f))) * 512);
  }
  else {
    noTone(SPEAKER);
  }

  time = millis();
}
