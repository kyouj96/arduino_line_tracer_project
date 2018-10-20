/* 초음파 센서를 이용하여 센서가 장애물과 10cm를 유지하도록 만들기 */

#include <Servo.h>
#define trigPin 7
#define echoPin 8 

Servo servo1,servo2;

void setup()
{
  Serial.begin (9600);  
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);
  servo1.attach(13);
  servo2.attach(12);
}
long microsecondsToCentimeters(long microseconds)
{
  
return microseconds / 29 / 2;
}

void loop()
{
  long duration, cm;  
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //초음파 발생 
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //초음파 시간 측정
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  //float distance = duration / 29 / 2;
  
  Serial.print(cm);
  Serial.println(" cm");
  
  if (cm < 10) {
    servo1.writeMicroseconds(1300);
    servo2.writeMicroseconds(1700); //10cm 보다 가가우면 후진
    delay(200);
  }
  else if (cm == 10) {
    servo1.writeMicroseconds(1500);
    servo2.writeMicroseconds(1500); //같으면 정지
    delay(200);
  }
  else {
    servo1.writeMicroseconds(1700);
    servo2.writeMicroseconds(1300); //멀면 전진
   delay(200);
  }
    
  delay(100);
}

