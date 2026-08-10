# Control System Experiment: Distance-Based Servo Angle Control

## 📌 Project Overview

This project is a practical control and instrumentation experiment designed to explore the relationship between **distance measurement, signal processing, mathematical modeling, and servo motor control**.

The system combines:

- HC-SR04 ultrasonic distance sensor
- MG90S servo motor
- Arduino
- 16×2 I2C LCD
- Signal filtering techniques
- Mathematical modeling
- Feedback and control concepts

The project is developed progressively, starting from sensor characterization and measurement filtering, then moving toward actuator control and, eventually, closed-loop control.

The main objective is not only to build a working system, but also to understand the **engineering principles behind each stage**.

---

# 1. Arc-Length Model: Distance-to-Angle Relationship

The first experiment is based on the geometric relationship between the **arc length of a circle** and its angular displacement.

The fundamental equation is:

\[
D = R\theta
\]

where:

- \(D\) = arc length / displacement
- \(R\) = radius of the servo mechanism
- \(\theta\) = angular displacement in radians

Therefore:

\[
\theta = \frac{D}{R}
\]

Since the Arduino servo library requires the angle in degrees, the angle is converted from radians to degrees:

\[
\theta_{deg}
=
\frac{D}{R}
\frac{180}{\pi}
\]

### Example

For:

\[
R = 127.3\ cm
\]

and:

\[
D = 192.58\ cm
\]

we obtain:

\[
\theta =
\frac{192.58}{127.3}
\approx 1.512\ rad
\]

and therefore:

\[
\theta_{deg}\approx86.68^\circ
\]

The servo is then commanded to approximately:

```text
86.68°
