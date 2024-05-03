#include <AFMotor.h>
#include <NewPing.h>

// Define pin numbers for sensors and motors
#define TRIGGER_PIN_FRONT A0
#define ECHO_PIN_FRONT A1
#define TRIGGER_PIN_BACK A2
#define ECHO_PIN_BACK A3
#define IR_PIN_LEFT A4
#define IR_PIN_RIGHT A5

// Define motor objects
AF_DCMotor motorFrontLeft(1);
AF_DCMotor motorFrontRight(2);
AF_DCMotor motorBackLeft(3);
AF_DCMotor motorBackRight(4);
#define MAX_DISTANCE 15
// Define sensor objects
NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE);
NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK, MAX_DISTANCE);

// Constants for distance and speed thresholds
#define FOLLOW_DISTANCE 20 // Follow distance in centimeters
#define CAUTION_DISTANCE 10 // Caution distance for slowing down
#define SPEED_NORMAL 150 // Normal speed for motors
#define SPEED_SLOW 100 // Speed for cautious movements

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(IR_PIN_LEFT, INPUT);
  pinMode(IR_PIN_RIGHT, INPUT);
}

void loop() {
  // Read distance from ultrasonic sensors
  int distanceFront = sonarFront.ping_cm();
  int distanceBack = sonarBack.ping_cm();

  // Read IR sensor inputs
  int irLeft = digitalRead(IR_PIN_LEFT);
  int irRight = digitalRead(IR_PIN_RIGHT);

  // Debugging output
  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm | Back Distance: ");
  Serial.print(distanceBack);
  Serial.print(" cm | IR Left: ");
  Serial.print(irLeft);
  Serial.print(" | IR Right: ");
  Serial.println(irRight);

  // Control motor actions based on sensor inputs
  if (distanceFront > 0 && distanceFront <= FOLLOW_DISTANCE) {
    // Object in front within follow range, adjust motors to maintain distance
    motorFrontLeft.setSpeed(SPEED_NORMAL);
    motorFrontRight.setSpeed(SPEED_NORMAL);
    motorBackLeft.setSpeed(SPEED_NORMAL);
    motorBackRight.setSpeed(SPEED_NORMAL);
    motorFrontLeft.run(FORWARD);
    motorFrontRight.run(FORWARD);
    motorBackLeft.run(FORWARD);
    motorBackRight.run(FORWARD);
  } else if (distanceBack > 0 && distanceBack <= CAUTION_DISTANCE) {
    // Object behind within caution range, slow down
    motorFrontLeft.setSpeed(SPEED_SLOW);
    motorFrontRight.setSpeed(SPEED_SLOW);
    motorBackLeft.setSpeed(SPEED_SLOW);
    motorBackRight.setSpeed(SPEED_SLOW);
    motorFrontLeft.run(FORWARD);
    motorFrontRight.run(FORWARD);
    motorBackLeft.run(FORWARD);
    motorBackRight.run(FORWARD);
  } else if (irLeft == LOW || irRight == LOW) {
    // IR sensors detect an object on either side, stop
    motorFrontLeft.setSpeed(0);
    motorFrontRight.setSpeed(0);
    motorBackLeft.setSpeed(0);
    motorBackRight.setSpeed(0);
    motorFrontLeft.run(RELEASE);
    motorFrontRight.run(RELEASE);
    motorBackLeft.run(RELEASE);
    motorBackRight.run(RELEASE);
  } else {
    // Move forward at normal speed
    motorFrontLeft.setSpeed(SPEED_NORMAL);
    motorFrontRight.setSpeed(SPEED_NORMAL);
    motorBackLeft.setSpeed(SPEED_NORMAL);
    motorBackRight.setSpeed(SPEED_NORMAL);
    motorFrontLeft.run(FORWARD);
    motorFrontRight.run(FORWARD);
    motorBackLeft.run(FORWARD);
    motorBackRight.run(FORWARD);
  }

  delay(50); // Delay for stability and responsiveness
}
