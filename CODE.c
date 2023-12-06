#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

DHT dht(DHTPIN, DHTTYPE);

int relay1Pin = 8; // Pin connected to the first relay module
int relay2Pin = 9; // Pin connected to the second relay module

void setup() {
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("DHT11");
  lcd.setCursor(0, 1);
  lcd.print("Humidity/Temp.");

  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
}

void loop() {
  delay(2000);
  float H = dht.readHumidity();
  float T = dht.readTemperature();

  if (isnan(H) || isnan(T)) {
    lcd.clear();
    lcd.print("Failed to read from DHT sensor!");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.print(H);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp.:");
  lcd.print(T);
  lcd.print((char)223);
  lcd.print("C");

  if (T >= 32.00) {
    digitalWrite(relay1Pin, LOW); // Turn on first relay module
  } else if (T <= 31.50) {
    digitalWrite(relay1Pin, HIGH); // Turn off first relay module
  }

  if (T >=31.00) {
    digitalWrite(relay2Pin, HIGH); // Turn on second relay module
  } else if(T<=31.20) {
    digitalWrite(relay2Pin, LOW); // Turn off second relay module
  }
}
