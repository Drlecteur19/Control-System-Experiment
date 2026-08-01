//==============================
// HC-SR04 Ultrasonic Sensor
//==============================

// Pin definition
const int trigPin = 9;
const int echoPin = 10;

// Variables
long duration;
float distance;

void setup()
{
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    digitalWrite(trigPin, LOW);
}

void loop()
{
    // Clear Trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Generate 10 us pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure Echo pulse
    duration = pulseIn(echoPin, HIGH);

    // Calculate distance
    distance = duration * 0.0343 / 2.0;

    // Display result
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(200);
}
