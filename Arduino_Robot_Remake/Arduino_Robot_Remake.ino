const int IN1 = 7;  // Motor A input pin 1
const int IN2 = 6; // Motor A input pin 2
const int ENA = 5; // Enable pin for Motor A (PWM for speed control)

const int IN3 = 8;  // Motor B input pin 1
const int IN4 = 9;  // Motor B input pin 2
const int ENB = 10;  // Enable pin for Motor B (PWM for speed control)

const int delayTime = 5000; // Delay time in milliseconds (5 seconds)

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set initial motor speeds (0 to 255)
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void loop() {
  // Rotate both motors in one direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(delayTime);

  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(1000); // Optional delay for motors to stop completely

  // Rotate both motors in the opposite direction
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(delayTime);

  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(1000); // Optional delay for motors to stop completely
}
