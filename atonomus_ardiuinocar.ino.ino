
/*  Obstacle Avoidance + Line Following Robot
  2-Channel IR Sensor | HC-SR04 Ultrasonic | L298N Driver
*/

// Pins 
#define IR_LEFT     2
#define IR_RIGHT    3

#define TRIG_PIN    9
#define ECHO_PIN    10

#define IN1         4
#define IN2         5
#define IN3         6
#define IN4         7
#define ENA         11
#define ENB         12

// Tuning Parameters 
#define OBSTACLE_DIST     20    
#define MOTOR_SPEED       160   
#define TURN_SPEED        130   
#define AVOID_TURN_TIME   400    

// IR sensor logic: LOW = detects line (dark surface), HIGH = no line (light surface)

#define LINE_DETECTED     HIGH
void setup() {
  pinMode(IR_LEFT,  INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  stopMotors();
  delay(1000);
}

void loop() {
  long dist = getDistance();
  Serial.print("Dist: "); Serial.print(dist);

  if (dist > 0 && dist < OBSTACLE_DIST) {
    //  OBSTACLE AVOIDANCE MODE
    Serial.println(" | OBSTACLE");
    avoidObstacle();
  } else {
    //  LINE FOLLOWING MODE 
    bool leftIR  = (digitalRead(IR_LEFT)  == LINE_DETECTED);
    bool rightIR = (digitalRead(IR_RIGHT) == LINE_DETECTED);

    Serial.print(" | L:"); Serial.print(leftIR);
    Serial.print(" R:"); Serial.println(rightIR);

    if (leftIR && rightIR) {
      moveForward();          
    } else if (leftIR && !rightIR) {
      turnLeft();             
    } else if (!leftIR && rightIR) {
      turnRight();            
    } else {
      stopMotors();           
    }
  }
}


//  OBSTACLE AVOIDANCE

void avoidObstacle() {
  stopMotors();
  delay(200);
  moveBackward();
  delay(300);
  turnRight();
  delay(AVOID_TURN_TIME);
  stopMotors();
  delay(100);
}

//  ULTRASONIC DISTANCE

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000); // 25ms timeout
  if (duration == 0) return 999; // no echo = clear path
  return duration * 0.034 / 2;
}

//  MOTOR CONTROL

void moveForward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); // Left motor back
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Right motor fwd
}

void turnRight() {
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Left motor fwd
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); // Right motor back
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}