#include <AFMotor.h>
#include <NewPing.h>

// Pin Definitions
#define TRIGGER_PIN A0
#define ECHO_PIN A1
#define IR_LEFT A4
#define IR_RIGHT A5
#define MAX_DISTANCE 20

// Motor setup on the Motor Shield
AF_DCMotor FrmotorLeft(1);
AF_DCMotor FrmotorRight(2);
AF_DCMotor BmotorLeft(3);
AF_DCMotor BmotorRight(4);

// Ultrasonic sensor setup
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
}

void loop() {
  delay(50); // Slight delay for stability
  unsigned int distance = sonar.ping_cm();
  int irLeft = digitalRead(IR_LEFT);
  int irRight = digitalRead(IR_RIGHT);
  String mode;
  // Check distance and adjust speed accordingly
  if (distance > 0 && distance < 5) {
    // Object detected within 5 cm, adjust speed to maintain following distance
    int speed = map(distance, 1, 5, 0, 100); // Map distance to speed
    FrmotorLeft.setSpeed(speed);
    FrmotorRight.setSpeed(speed);
    BmotorLeft.setSpeed(speed);
    BmotorRight.setSpeed(speed);
    FrmotorLeft.run(FORWARD);
    FrmotorRight.run(FORWARD);
    BmotorLeft.run(FORWARD);
    BmotorRight.run(FORWARD);
    mode = "Following";
   
  } else if (irLeft == LOW || irRight == LOW) {
    // Obstacle detected on the side, initiate backup procedure
    FrmotorLeft.setSpeed(150);
    FrmotorRight.setSpeed(150);
    BmotorLeft.setSpeed(150);
    BmotorRight.setSpeed(150);
    FrmotorLeft.run(BACKWARD);
    FrmotorRight.run(BACKWARD);
    BmotorLeft.run(BACKWARD);
    BmotorRight.run(BACKWARD);
    delay(1000); // Back up for 1 second
    mode = "Backing Up";
  } else {
    // No object detected, move at normal speed
    FrmotorLeft.setSpeed(200);
    FrmotorRight.setSpeed(200);
    BmotorLeft.setSpeed(200);
    BmotorRight.setSpeed(200);
    FrmotorLeft.run(FORWARD);
    FrmotorRight.run(FORWARD);
    BmotorLeft.run(FORWARD);
    BmotorRight.run(FORWARD);
    mode = "Cruising";
  }
  // Send data in CSV format
  Serial.print(millis());
  Serial.print(",");
  Serial.print(distance);
  Serial.print(",");
  Serial.print(irLeft);
  Serial.print(",");
  Serial.print(irRight);
  Serial.print(",");
  Serial.println(mode);
  // Simulate sending data to "cloud" and receiving instructions
}
