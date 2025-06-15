# Intelligent Obstacle Avoiding Robot with 4 DC Motors, Ultrasonic Scanning & Smart Logic

This project is an Arduino-based autonomous robot that avoids obstacles using an ultrasonic sensor mounted on a servo motor. It intelligently scans its surroundings and chooses the best direction to move. The robot is powered by 4 DC motors, and includes visual and audio indicators using LEDs and a buzzer.

## 🔧 Features
- 4 DC motor control via motor driver shield
- Ultrasonic distance sensing (HC-SR04)
- Smart direction selection using servo-mounted ultrasonic scanning (left, front, right)
- Obstacle detection and avoidance
- LED indicators:
  - Red: obstacle very close
  - Yellow: preparing to avoid
  - Green: safe to move
- Buzzer alert when obstacle is too close

## 📦 Components Used
- Arduino Uno
- L298P or Adafruit Motor Shield
- 4x DC motors
- 1x HC-SR04 ultrasonic sensor
- 1x Servo motor (SG90 or similar)
- LEDs (Red, Yellow, Green)
- Buzzer
- External battery (e.g., LiPo 2S)

## 🖥️ Code Overview
- Motors are controlled using the AFMotor library
- Ultrasonic sensor reads distance and uses smart logic to decide movement
- Servo rotates to scan left (150°), front (90°), and right (30°)
- If no safe path is found, the robot moves backward

