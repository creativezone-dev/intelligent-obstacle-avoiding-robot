#include <AFMotor.h>
#include <Servo.h>

// Motor DC
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// Servo untuk scanning
Servo scanServo;
int servoPin = 9;

// Ultrasonic sensor
const int trigPin = 6;
const int echoPin = 7;

// LED indikator
const int ledRed = 10;
const int ledYellow = 11;
const int ledGreen = 12;

// Buzzer
const int buzzerPin = 13;

void setup() {
  Serial.begin(9600);

  // Motor speed
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  scanServo.attach(servoPin);
  scanServo.write(90); // Tengah
}

void loop() {
  int front = getDistance(90);  // depan
  Serial.print("Front: "); Serial.println(front);

  if (front > 25) {
    setLED(HIGH, LOW, LOW); // Hijau: jalan aman
    digitalWrite(buzzerPin, LOW);
    moveForward();
  } else {
    setLED(LOW, HIGH, LOW); // Kuning: akan menghindar
    stopMotors();
    delay(300);
    digitalWrite(buzzerPin, HIGH); // Buzzer nyala
    delay(100);
    digitalWrite(buzzerPin, LOW);

    // Scan kiri & kanan
    int left = getDistance(150);
    delay(200);
    int right = getDistance(30);
    delay(200);

    // Pilih arah bebas
    if (left > right && left > 20) {
      setLED(LOW, LOW, HIGH); // Hijau: belok kiri
      turnLeft();
    } else if (right >= left && right > 20) {
      setLED(LOW, LOW, HIGH); // Hijau: belok kanan
      turnRight();
    } else {
      setLED(HIGH, LOW, LOW); // Merah: tidak aman
      moveBackward();
    }

    delay(500);
  }

  delay(100);
}

// Fungsi ambil jarak dengan servo posisi tertentu
int getDistance(int angle) {
  scanServo.write(angle);
  delay(250);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return constrain(distance, 0, 300);
}

// Fungsi gerakan
void moveForward() {
  motor1.run(FORWARD); motor2.run(FORWARD);
  motor3.run(FORWARD); motor4.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD); motor2.run(BACKWARD);
  motor3.run(BACKWARD); motor4.run(BACKWARD);
}

void turnLeft() {
  motor1.run(BACKWARD); motor2.run(FORWARD);
  motor3.run(BACKWARD); motor4.run(FORWARD);
}

void turnRight() {
  motor1.run(FORWARD); motor2.run(BACKWARD);
  motor3.run(FORWARD); motor4.run(BACKWARD);
}

void stopMotors() {
  motor1.run(RELEASE); motor2.run(RELEASE);
  motor3.run(RELEASE); motor4.run(RELEASE);
}

// LED helper
void setLED(bool red, bool yellow, bool green) {
  digitalWrite(ledRed, red);
  digitalWrite(ledYellow, yellow);
  digitalWrite(ledGreen, green);
}
