#include <Servo.h>

Servo myServo;
Servo servoLeft;
Servo servoRight;

int pingPin = 3;

float duration;
float left;
float right;
float front;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(11);
  servoLeft.attach(10);
  servoRight.attach(12);

  digitalWrite(2, HIGH);

  Serial.begin(9600);
}

void loop() {
  myServo.write(90);
  pulse();
  //Serial.println(duration);
  servoRight.writeMicroseconds(1000);
  servoLeft.writeMicroseconds(1600);

  if(duration <1000){
    halt();
    scan();
    if(left < right){
      Serial.println("Go right");
      turnRight(500);
      }
      else{
      Serial.println("Go left");
      turnLeft(500);  
      }
    }
  delay(750);
  
}

void pulse(){
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  }

void scan(){
  myServo.write(0);
  //Serial.println("Position 0");
  delay(1000);
  pulse();
  right = duration;
  //Serial.print("right is ");
  //Serial.println(right);
  delay(1000);
  
  myServo.write(90);
  //Serial.println("Position 90");
  delay(1000);
  pulse();
  front = duration;
  //Serial.print("front is ");
  //Serial.println(front);
  delay(1000);
  
  myServo.write(180);
  //Serial.println("Position 180");
  delay(1000);
  pulse();
  left = duration;
  //Serial.print("left is ");
  //Serial.println(left);
  delay(1000);
  myServo.write(90);
  }

/*void forward(){
  servoRight.writeMicroseconds(1000);
  servoLeft.writeMicroseconds(2000);
  Serial.println("going forward");  
  }
*/
void backward(){
  servoRight.writeMicroseconds(2000);
  servoLeft.writeMicroseconds(1000);  
  }

void halt(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  }

void turnLeft(int ms){
  servoRight.writeMicroseconds(1000);
  servoLeft.writeMicroseconds(1500);
  delay(ms);
  }

void turnRight(int ms){
  servoRight.writeMicroseconds(1500);
  servoLeft.writeMicroseconds(2000);
  delay(ms);
  }


