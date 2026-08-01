#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address (commonly 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0,0);
    lcd.print("Ultrasonic");
    delay(1500);
    lcd.clear();
}

void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.0343 / 2;

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Distance:");

    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.print(" cm");

    delay(300);
}
