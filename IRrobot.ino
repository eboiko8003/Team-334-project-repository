#include <IRLibAll.h>
#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo clawServo;

const long FORWARD = 1112;
const long FORWARD1 = 66648;
const long BACKWARD = 1113;
const long BACKWARD1 = 66649;
const long TURNLEFT = 1114;
const long TURNLEFT1 = 66650;
const long TURNRIGHT = 1115;
const long TURNRIGHT1 = 66651;
const long STOP = 1116;
const long STOP1 = 66652;
const long OPEN = 1026;
const long OPEN1 = 66562;
const long CLOSE = 1027;
const long CLOSE1 = 66563;


IRrecvPCI myReciver(2);
IRdecode myDecoder;

uint32_t previous;//handles repeat codes

int duration;

bool isAutoMode = 0;

void setup() {
  // put your setup code here, to run once:

  servoLeft.attach(12);
  servoRight.attach(13);
  clawServo.attach(11);
  

  Serial.begin(9600);
  myReciver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myReciver.getResults()){
    myDecoder.decode();

    if(myDecoder.value == 1025 || myDecoder.value == 66561){
      isAutoMode = 1;
    }
    else
      isAutoMode = 0;
    
    Serial.print("Recived Value: "); Serial.println(myDecoder.value);
    if( !isAutoMode){
    
      switch(myDecoder.value){
          case FORWARD: Serial.println("Forward pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10);
          servoLeft.writeMicroseconds(1625);
        servoRight.writeMicroseconds(1300);
          break;
  
          
          case FORWARD1: Serial.println("Forward pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10);
          servoLeft.writeMicroseconds(1625);
        servoRight.writeMicroseconds(1300);
          break;
  
          
          case BACKWARD: Serial.println("Backward pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10); 
          servoLeft.writeMicroseconds(1300);
          servoRight.writeMicroseconds(1700);
          break;
  
          
          case BACKWARD1: Serial.println("Backward pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10); 
          servoLeft.writeMicroseconds(1300);
          servoRight.writeMicroseconds(1700);
          break;
  
          
          case TURNLEFT: Serial.println("Left pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10); 
          servoLeft.writeMicroseconds(1300);
          servoRight.writeMicroseconds(1300);
          break;
  
          
          case TURNLEFT1: Serial.println("Left pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10); 
          servoLeft.writeMicroseconds(1300);
          servoRight.writeMicroseconds(1300);
          break;
  
          
          case TURNRIGHT: Serial.println("Right pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10); 
          servoLeft.writeMicroseconds(1625);
          servoRight.writeMicroseconds(1700);
          break;
  
          
          case TURNRIGHT1: Serial.println("Right pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          delay(10); 
          servoLeft.writeMicroseconds(1625);
        servoRight.writeMicroseconds(1700);
          break;
  
          
          case STOP: Serial.println("Stop pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          break;
  
          
          case STOP1: Serial.println("Stop pressed");
          servoLeft.writeMicroseconds(1500);
          servoRight.writeMicroseconds(1500);
          break;

          case OPEN: Serial.println("opening");
          clawServo.write(30);
          //(myDecoder.value)=FORWARD;
          break;

          case OPEN1: Serial.println("opening");
          clawServo.write(30);
         //(myDecoder.value)=FORWARD;
          break;

          case CLOSE: Serial.println("closing");
         // clawServo.attach(11);
          //Serial.println("attached");
          clawServo.write(110);
         //(myDecoder.value)=FORWARD;
         //clawServo.detach();
          break;

          case CLOSE1: Serial.println("closing");
          //clawServo.attach(11);
          //Serial.println("attached");
          clawServo.write(110);
          //(myDecoder.value)=FORWARD;
          //clawServo.detach();
          break;
    }
    
     myReciver.enableIRIn();
   }
    //Serial.println(F("Value type: "), myDecoder.protocolNum);
//    Serial.print("Value type: "); Serial.println(myDecoder.protocolNum);
    //Serial.print("Value: "); Serial.println(myDecoder.value);
//    myReciver.enableIRIn();
 }
  else {
    if(isAutoMode){   
          
        servoLeft.writeMicroseconds(1625);
        servoRight.writeMicroseconds(1300);
        
        pinMode(7, OUTPUT);
        digitalWrite(7, LOW);
        delayMicroseconds(2);
        digitalWrite(7, HIGH);
        delayMicroseconds(5);
        digitalWrite(7, LOW);
        pinMode(7, INPUT);
        duration = pulseIn(7, HIGH);
        //Serial.println(duration);
        delay(5);
        if(duration < 1000){
           servoLeft.writeMicroseconds(1625);
           servoRight.writeMicroseconds(1700);
           delay(500);   
        }
        
      }
      myReciver.enableIRIn();
    }
}
