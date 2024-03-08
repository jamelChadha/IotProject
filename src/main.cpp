// #include <Arduino.h>

// #include <WiFi.h>
// #include "DHTesp.h"
// #include "ThingSpeak.h"
// #include <LiquidCrystal_I2C.h>
// #define I2C_ADDR    0x27
// #define LCD_COLUMNS 20
// #define LCD_LINES   4
// const char* WIFI_NAME = "Wokwi-GUEST";
// const char* WIFI_PASSWORD = "";
// const int myChannelNumber = 2445450;
// const char* myApiKey = "JGHK8O4QWNHAYQUB";
// const char* server = "api.thingspeak.com";

// const int DHT_PIN = 15;

// DHTesp dhtSensor;
// WiFiClient client;
// LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

// void setup() {

//   Serial.begin(115200);
//   dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
//   lcd.init();
//   lcd.backlight();
//     // Connexion au WiFi
//   WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
//   Serial.print("Connecting to WiFi");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println("WiFi connected !");
//   Serial.println("Local IP: " + String(WiFi.localIP()));
//   ThingSpeak.begin(client);
//   lcd.begin(16, 2);
// }



// void loop() {

//   TempAndHumidity data = dhtSensor.getTempAndHumidity();
//   ThingSpeak.setField(1, data.temperature);
//   ThingSpeak.setField(2, data.humidity);
//   int x = ThingSpeak.writeFields(myChannelNumber, myApiKey);
//   Serial.println("Temp: " + String(data.temperature, 1) + "°C");
//   Serial.println("Humidity: " + String(data.humidity, 1) + "%");
//   Serial.println("---");
  
//   lcd.setCursor(0, 0);
//   lcd.print("  Temp: " + String(data.temperature, 1) + "\xDF"+"C  ");
//   lcd.setCursor(0, 1);
//   lcd.print(" Humidity: " + String(data.humidity, 1) + "% ");
//   lcd.print("Wokwi Online IoT");

//   delay(1000);
// }
#include <Arduino.h>
#include <WiFi.h>
#include "DHTesp.h"
#include "ThingSpeak.h"
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const int myChannelNumber = 2445450;
const char* myApiKey = "JGHK8O4QWNHAYQUB";
const char* server = "api.thingspeak.com";

const int DHT_PIN = 15;
const int LDR_PIN = 34; // Pin pour le capteur de luminosité (LDR)
const int ELECTRICITY_PIN = 35; // Pin pour le capteur d'électricité

DHTesp dhtSensor;
WiFiClient client;
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  lcd.init();
  lcd.backlight();
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected !");
  Serial.println("Local IP: " + String(WiFi.localIP()));
  ThingSpeak.begin(client);
  lcd.begin(16, 2);
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  int lightIntensity = analogRead(LDR_PIN);
  int electricityValue = analogRead(ELECTRICITY_PIN);
  ThingSpeak.setField(1, data.temperature);
  ThingSpeak.setField(2, data.humidity);
  ThingSpeak.setField(3, lightIntensity);
  ThingSpeak.setField(4, electricityValue);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myApiKey);
  Serial.println("Temp: " + String(data.temperature, 1) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("Light Intensity: " + String(lightIntensity)+"A");
  Serial.println("Electricity Value: " + String(electricityValue)+"C");
  Serial.println("---");
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 1) + "\xDF"+"C  ");
  lcd.setCursor(0, 1);
  lcd.print(" Humidity: " + String(data.humidity, 1) + "% ");
  lcd.setCursor(0, 2);
  lcd.print(" Light: " + String(lightIntensity)+"A");
  lcd.setCursor(0, 3);
  lcd.print(" Electricity: " + String(electricityValue)+"C");
   lcd.setCursor(0, 4);
  lcd.print("Wokwi Online IoT");

  delay(1000);
}
