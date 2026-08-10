# Control System Experiment: Distance-Based Servo Angle Control

## 📌 Project Overview

This project is a practical control and instrumentation experiment focused on the relationship between **distance measurement, signal filtering, mathematical modeling, and servo motor control**.

The system uses an **HC-SR04 ultrasonic sensor** to measure distance and an **MG90S servo motor** to generate an angular response based on the measured distance.

The project is developed progressively, starting with sensor characterization and measurement filtering, followed by mathematical modeling and actuator control. Closed-loop control and PID control will be investigated in later stages.

### Main Components

- Arduino
- HC-SR04 Ultrasonic Sensor
- MG90S Servo Motor
- 16×2 I2C LCD
- Signal filtering techniques
- Mathematical modeling
- Control-system concepts

---

# 1. Arc-Length Model: Distance-to-Angle Relationship

The first experiment is based on the geometric relationship between the arc length of a circle and its angular displacement.

The fundamental equation is:

\[
D = R\theta
\]

where:

- \(D\) = arc length / displacement
- \(R\) = radius of the mechanism
- \(\theta\) = angular displacement in radians

Therefore:

\[
\theta = \frac{D}{R}
\]

Since the Arduino servo library uses degrees, the angle is converted from radians to degrees:

\[
\theta_{deg}
=
\frac{D}{R}
\frac{180}{\pi}
\]

For example, using:

\[
R = 127.3\ cm
\]

and a measured distance of:

\[
D = 192.58\ cm
\]

the resulting servo angle is approximately:

\[
\theta_{deg}=86.68^\circ
\]

---

# 2. System Architecture

The basic signal flow is:

```text
        HC-SR04
           │
           ▼
   Raw Distance Measurement
           │
           ▼
    Signal Filtering
           │
           ▼
    Filtered Distance
           │
           ▼
      D / R = θ
           │
           ▼
    Radians → Degrees
           │
           ▼
       MG90S Servo
\theta_{deg}\approx86.68^\circ
\]

The servo is then commanded to approximately:

```text
86.68°
