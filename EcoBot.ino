#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN A0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int airQuality = analogRead(MQ135_PIN);

  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("Portable EcoBot");

  display.setCursor(0, 15);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");

  display.setCursor(0, 30);
  display.print("Humidity: ");
  display.print(humidity);
  display.print(" %");

  display.setCursor(0, 45);
  display.print("Air AQ: ");
  display.print(airQuality);

  display.display();

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("C  Humidity: ");
  Serial.print(humidity);
  Serial.print("%  AirQuality: ");
  Serial.println(airQuality);

  delay(2000);
}
