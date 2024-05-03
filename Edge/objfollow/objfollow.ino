#include <AFMotor.h>
#include <NewPing.h>

#define TRIGGER_PIN_FRONT A0
#define ECHO_PIN_FRONT A1
#define TRIGGER_PIN_BACK A2
#define ECHO_PIN_BACK A3
#define IR_PIN_LEFT A4
#define IR_PIN_RIGHT A5
#define MAX_DISTANCE 100

NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE);
NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK, MAX_DISTANCE);
AF_DCMotor motorFrontLeft(1);  // Front left motor on M1 port
AF_DCMotor motorFrontRight(2); // Front right motor on M2 port
AF_DCMotor motorBackLeft(3);   // Back left motor on M3 port
AF_DCMotor motorBackRight(4);  // Back right motor on M4 port

int followDistance = 1142; // Desired distance from the object
int speed = 100; // Initial speed of the motors

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN_LEFT, INPUT);
  pinMode(IR_PIN_RIGHT, INPUT);
}
void loop() {
  delay(50);

  unsigned int distanceFront = sonarFront.ping_cm();
  unsigned int distanceBack = sonarBack.ping_cm();
  if(distanceFront != 0){
  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  }
  if(distanceBack !=0){
  Serial.print(" cm \n Back Distance: ");
  Serial.print(distanceBack);
  Serial.println(" cm\n");
  }
  Serial.println(speed);

  // Handle front sensor for following behavior
  if (distanceFront > 0 && distanceFront >= followDistance) {
    // Calculate speed proportional to the distance
    int speedAdjustment = (distanceFront - followDistance) * 5; // Adjust multiplier to tune responsiveness
    int adjustedSpeed = constrain(speed + speedAdjustment, 0, 255); // Ensure speed stays within motor limits
    setMotorSpeed(40);
    moveForward();
  } else if (distanceBack > 0 && distanceBack <= followDistance) {
    // If object detected at the back, reverse
    setMotorSpeed(100); // Set a reasonable speed for reversing
    moveBackward();
  } else {
    // Otherwise, move forward at normal speed
    setMotorSpeed(100);
    moveForward();
  }
}
void stoper(){
   motorFrontLeft.setSpeed(RELEASE);
  motorFrontRight.setSpeed(RELEASE);
  motorBackLeft.setSpeed(RELEASE);
  motorBackRight.setSpeed(RELEASE);
}
void setMotorSpeed(int motorSpeed) {
  motorFrontLeft.setSpeed(motorSpeed);
  motorFrontRight.setSpeed(motorSpeed);
  motorBackLeft.setSpeed(motorSpeed);
  motorBackRight.setSpeed(motorSpeed);
}

void moveForward() {
  motorFrontLeft.run(FORWARD);
  motorFrontRight.run(FORWARD);
  motorBackLeft.run(FORWARD);
  motorBackRight.run(FORWARD);
}

void moveBackward() {
  motorFrontLeft.run(BACKWARD);
  motorFrontRight.run(BACKWARD);
  motorBackLeft.run(BACKWARD);
  motorBackRight.run(BACKWARD);
}
