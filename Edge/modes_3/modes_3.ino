

#include <AFMotor.h>
#include <NewPing.h>

#define TRIGGER_PIN_FRONT A0
#define ECHO_PIN_FRONT A1
#define IR_PIN_LEFT A4
#define IR_PIN_RIGHT A5
#define MAX_DISTANCE 100
#define FOLLOW_DISTANCE 20 // Distance for object following
#define IR_THRESHOLD 500    // Threshold value for IR sensor detection

NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE);
AF_DCMotor motorFrontLeft(1);  // Front left motor on M1 port
AF_DCMotor motorFrontRight(2); // Front right motor on M2 port
AF_DCMotor motorBackLeft(3);   // Back left motor on M3 port
AF_DCMotor motorBackRight(4);  // Back right motor on M4 port

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN_LEFT, INPUT);
  pinMode(IR_PIN_RIGHT, INPUT);
}

void loop() {
  delay(5);

  unsigned int distanceFront = sonarFront.ping_cm();
  int irLeft = analogRead(IR_PIN_LEFT);
  int irRight = analogRead(IR_PIN_RIGHT);
if(distanceFront!=0){
  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm | IR Left: ");
  Serial.print(irLeft);
  Serial.print(" | IR Right: ");
  Serial.println(irRight);
}
int speed=50;
  // Check if object is in front within follow distance or detected by IR sensors
  if ((distanceFront > 0 || distanceFront <= FOLLOW_DISTANCE) || irLeft < IR_THRESHOLD || irRight < IR_THRESHOLD) {
    // Object in front within follow range or detected by IR sensors, adjust motors to follow object
    motorFrontLeft.setSpeed(150); // Adjust speed as needed
    motorFrontRight.setSpeed(150); // Adjust speed as needed
    motorBackLeft.setSpeed(150); // Adjust speed as needed
    motorBackRight.setSpeed(150); // Adjust speed as needed
    motorFrontLeft.run(FORWARD);
    motorFrontRight.run(FORWARD);
    motorBackLeft.run(FORWARD);
    motorBackRight.run(FORWARD);
    speed =150;
  } else {
    // Move forward at initial speed
    motorFrontLeft.setSpeed(100); // Initial speed
    motorFrontRight.setSpeed(100); // Initial speed
    motorBackLeft.setSpeed(100); // Initial speed
    motorBackRight.setSpeed(100); // Initial speed
    motorFrontLeft.run(FORWARD);
    motorFrontRight.run(FORWARD);
    motorBackLeft.run(FORWARD);
    motorBackRight.run(FORWARD);
    speed=100;
  }
  
}
// dunno still undetermined 

//
//
//#include <AFMotor.h>
//
//AF_DCMotor motorFrontLeft(1);  // Front left motor on M1 port
//AF_DCMotor motorFrontRight(2); // Front right motor on M2 port
//AF_DCMotor motorBackLeft(3);   // Back left motor on M3 port
//AF_DCMotor motorBackRight(4);  // Back right motor on M4 port
//int speed;
//int timeInSeconds;
//
//void setup() {
//  Serial.begin(9600);
//  // Get speed and time input from user
//  Serial.println("Enter speed (0-255):");
//  while (!Serial.available()) {}
//  speed = 150;
//
// // Serial.println("Enter time in seconds:");
//  //while (!Serial.available()) {}
//  timeInSeconds = 20;
////delay(10000);
//  Serial.println("Press any key to start...");
//  while (!Serial.available()) {}
//  delay(1000);
//}
//
//void loop() {
//  // Move forward at specified speed for specified time
//   motorFrontLeft.setSpeed(speed); // Adjust speed as needed
//    motorFrontRight.setSpeed(speed);
//  motorBackLeft.setSpeed(speed); // Adjust speed as needed
//    motorBackRight.setSpeed(speed); // Adjust speed as needed
//    motorFrontLeft.run(FORWARD);
//    motorFrontRight.run(FORWARD);
//    motorBackLeft.run(FORWARD);
//    motorBackRight.run(FORWARD);
//
//  delay(timeInSeconds * 1000);  // Convert seconds to milliseconds
//
//  // Stop and reverse at twice the speed
//  motorFrontLeft.setSpeed(speed * 2);
//  motorFrontRight.setSpeed(speed * 2);
//  motorBackLeft.setSpeed(speed * 2);
//  motorBackRight.setSpeed(speed * 2);
//    motorBackLeft.run(BACKWARD);
//    motorBackRight.run(BACKWARD);
//  motorFrontLeft.run(BACKWARD);
//  motorFrontRight.run(BACKWARD);
//  delay(timeInSeconds * 1000);  // Convert seconds to milliseconds
//
//  // Stop and perform wheelies
//  motorFrontLeft.setSpeed(255);
//  motorFrontRight.setSpeed(255);
//  motorFrontLeft.run(FORWARD);
//  motorFrontRight.run(BACKWARD);
//  delay(2000);  // Perform wheelies for 2 seconds
//
//  // Stop motors
//  motorFrontLeft.setSpeed(0);
//  motorFrontRight.setSpeed(0);
//  motorBackRight.setSpeed(0);
//  motorBackLeft.setSpeed(0);
//  motorBackLeft.run(RELEASE);
//  motorBackRight.run(RELEASE);
//  motorFrontLeft.run(RELEASE);
//  motorFrontRight.run(RELEASE);
//  // End program
//  while (true) {}
//}
