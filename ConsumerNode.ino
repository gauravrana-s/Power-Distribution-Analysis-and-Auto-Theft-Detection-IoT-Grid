#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define RELAY 3
#define REED 2

float threshold = 20;   // lower for better demo

void setup() {
  pinMode(RELAY, OUTPUT);
  pinMode(REED, INPUT);

  digitalWrite(RELAY, HIGH);

  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {

    float linePower = Serial.parseFloat();

    int c = analogRead(A0);
    float loadCurrent = (c - 512) * (5.0 / 1023.0) / 0.066;
    float loadPower = 230 * loadCurrent;

    float powerDiff = linePower - loadPower;

    // Current lost (approx)
    float currentLost = powerDiff / 230.0;

    lcd.clear();

    // Line 1: Current Lost + Power Diff
    lcd.setCursor(0, 0);
    lcd.print("CL:");
    lcd.print(currentLost, 2);
    lcd.print(" PD:");
    lcd.print(powerDiff, 1);

    // Line 2: Status
    lcd.setCursor(0, 1);

    if (powerDiff > threshold || digitalRead(REED) == HIGH) {
      digitalWrite(RELAY, LOW);
      lcd.print("STATUS:THEFT!");
    } else {
      digitalWrite(RELAY, HIGH);
      lcd.print("STATUS:NORMAL");
    }

    // Send to ESP32
    Serial.print(currentLost);
    Serial.print(",");
    Serial.println(powerDiff);
  }
}