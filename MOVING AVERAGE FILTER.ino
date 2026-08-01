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
const float R = 127.3;   // Radius (cm)
const int N = 10;        // Number of measurements

//==============================
// Variables
//==============================
long duration;
float distance;
float thetaRad;
float thetaDeg;


//==================================================
// MOVING AVERAGE FILTER
//==================================================
float movingAverage()
{
    float sum = 0;

    for (int i = 0; i < N; i++)
    {
        // Trigger sensor
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);

        digitalWrite(trigPin, LOW);

        // Read echo
        long duration = pulseIn(echoPin, HIGH, 30000);

        // Convert time to distance
        float d = duration * 0.0343 / 2.0;

        // Add measurement
        sum = sum + d;

        delay(50);
    }

    // Calculate mean
    float mean = sum / N;

    return mean;
}


//==================================================
// SETUP
//==================================================
void setup()
{
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    scanner.attach(servoPin);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Ultrasonic");

    lcd.setCursor(0, 1);
    lcd.print("Initializing");

    delay(2000);

    lcd.clear();
}


//==================================================
// LOOP
//==================================================
void loop()
{
    //==============================
    // Get filtered distance
    //==============================
    distance = movingAverage();


    //==============================
    // Calculate angle
    //
    // s = R * theta
    //
    // theta = distance / R
    //==============================

    thetaRad = distance / R;

    // Convert radians to degrees
    thetaDeg = thetaRad * 180.0 / PI;

    // Limit servo angle
    thetaDeg = constrain(thetaDeg, 0, 180);


    //==============================
    // Move Servo
    //==============================
    scanner.write(thetaDeg);


    //==============================
    // LCD
    //==============================
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("D:");
    lcd.print(distance, 1);
    lcd.print(" cm");

    lcd.setCursor(0, 1);
    lcd.print("A:");
    lcd.print(thetaDeg, 1);
    lcd.print((char)223);


    //==============================
    // Serial Monitor
    //==============================
    Serial.print("Filtered Distance = ");
    Serial.print(distance, 2);

    Serial.print(" cm");

    Serial.print("    Angle = ");
    Serial.print(thetaDeg, 2);

    Serial.println(" deg");


    delay(500);
}
