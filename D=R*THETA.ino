#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//==============================
// LCD
//==============================
LiquidCrystal_I2C lcd(0x27, 16, 2);

//==============================
// Ultrasonic Sensor
//==============================
const int trigPin = 9;
const int echoPin = 10;

//==============================
// Servo
//==============================
Servo scanner;
const int servoPin = 6;

//==============================
// Parameters
//==============================
const float R = 127.3;

thetaRad = distance / R;
thetaDeg = thetaRad * 180.0 / PI;

scanner.write(thetaDeg);

//==============================
// Variables
//==============================
long duration;
float distance;
float thetaRad;
float thetaDeg;

void setup()
{
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    scanner.attach(servoPin);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0,0);
    lcd.print("Ultrasonic");
    lcd.setCursor(0,1);
    lcd.print("Initializing");
    delay(2000);
    lcd.clear();
}

void loop()
{
    //==============================
    // Send Trigger Pulse
    //==============================
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    //==============================
    // Read Echo Pulse
    //==============================
    duration = pulseIn(echoPin, HIGH);

    //==============================
    // Calculate Distance (cm)
    //==============================
    distance = duration * 0.0343 / 2.0;

    //==============================
    // Compute Angle
    // theta = distance / R
    // (Angle in radians)
    //==============================
    thetaRad = distance / R;

    // Convert radians to degrees
    thetaDeg = thetaRad * 180.0 / PI;

    // Servo limits
    thetaDeg = constrain(thetaDeg, 0, 180);

    //==============================
    // Move Servo
    //==============================
    scanner.write(thetaDeg);

    //==============================
    // LCD Display
    //==============================
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("D:");
    lcd.print(distance,1);
    lcd.print(" cm");

    lcd.setCursor(0,1);
    lcd.print("A:");
    lcd.print(thetaDeg,1);
    lcd.print((char)223);

    //==============================
    // Serial Monitor
    //==============================
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.print(" cm");

    Serial.print("    Angle = ");
    Serial.print(thetaDeg);
    Serial.println(" deg");

    delay(200);
}
