#include <SoftwareSerial.h>

// Define motor pins
const int IN1 = 7;  // Motor A input pin 1
const int IN2 = 6;  // Motor A input pin 2
const int ENA = 5;  // Enable pin for Motor A (PWM for speed control)
const int IN3 = 8;  // Motor B input pin 1
const int IN4 = 9;  // Motor B input pin 2
const int ENB = 10;  // Enable pin for Motor B (PWM for speed control)

// Define Bluetooth pins
const int BT_RX = 3;
const int BT_TX = 4;

// Define IR sensor pins
const int LEFT_IR = A0;
const int RIGHT_IR = A1;

// Define control pin for switching between modes
const int MODE_PIN = 2;

// Define speed values
const int BT_SPEED = 250;
const int LINE_SPEED = 150;

// Create software serial object for Bluetooth
SoftwareSerial BTSerial(BT_RX, BT_TX);

void setup() {
  // Initialize Bluetooth serial communication
  BTSerial.begin(9600);

  // Initialize motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize IR sensor pins
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  // Initialize mode pin
  pinMode(MODE_PIN, INPUT_PULLUP);

  // Set initial motor speeds (0 to 255)
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void loop() {
  if (digitalRead(MODE_PIN) == LOW) {
    // Line following mode
    followLine();
  } else {
    // Bluetooth control mode
    if (BTSerial.available() > 0) {
      char command = BTSerial.read(); // Read the incoming data

      switch (command) {
        case 'F': // Move forward
          moveForward(BT_SPEED);
          break;
        case 'B': // Move backward
          moveBackward(BT_SPEED);
          break;
        case 'L': // Turn left
          turnLeft(BT_SPEED);
          break;
        case 'R': // Turn right
          turnRight(BT_SPEED);
          break;
        case 'S': // Stop
          stopMotors();
          break;
        default:
          stopMotors();
          break;
      }
    }
  }
}

void followLine() {
  bool leftState = digitalRead(LEFT_IR);
  bool rightState = digitalRead(RIGHT_IR);

  if (!leftState && !rightState) { // Both sensors on line
    moveForward(LINE_SPEED);
  } else if (!leftState && rightState) { // Left sensor on line, right sensor off line
    turnLeft(LINE_SPEED);
  } else if (leftState && !rightState) { // Right sensor on line, left sensor off line
    turnRight(LINE_SPEED);
  } else { // Both sensors off line
    stopMotors();
  }
}

void moveForward(int speed) {

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
