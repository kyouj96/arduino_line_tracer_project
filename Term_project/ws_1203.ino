/*  십자길을 인식해서 90도 회전 후, 직진함*/
#include<Servo.h>
#define B 7
#define D 8

char Sensor[] = {A0,A1,A2}; //핀의 배열
int Sensor_val[3];
Servo servo1, servo2;

float cm0, cm1, cm2;

///////////////////// Flag /////////////////////////

int enterCross = 0;//십자길을 마주하였다.
int turnLeft = 0; //왼쪽 회전 플래그 //시계방향일때
int turnRight = 0; //오른쪽 회전 플래그 //반시계방향일때
int wclock = 0;  //시계 방향 반시계 방향 //0:시계방향 1:반시계 방향
int i=0;

//////////////////////// setup  /////////////////////////
void setup()
{
  Serial.begin(9600);

  pinMode(Sensor,INPUT);
  servo1.attach(13);  //왼쪽
  servo2.attach(12);  //오른쪽
}

////////////////////////   loop   /////////////////////////////
void loop()
{
  Sensor_val[0] = map(analogRead(Sensor[0]), 0, 1023, 0, 5000); //전압값으로 변환
  Sensor_val[1] = map(analogRead(Sensor[1]), 0, 1023, 0, 5000);
  Sensor_val[2] = map(analogRead(Sensor[2]), 0, 1023, 0, 5000);
  
  cm0 = (24.61/(Sensor_val[0]-0.1696))*1000; //cm값으로 변환
  cm1 = (24.61/(Sensor_val[1]-0.1696))*1000;
  cm2 = (24.61/(Sensor_val[2]-0.1696))*1000;

      /////////////////////////회전 코드///////////////////////////////
  
  if(enterCross == 1 && turnLeft == 1){ //십자길을 만났을 때 (좌회전 할때) (시계방향)
    while(i<135) {  //좌회전: 135 90도 회전
      if(i<20){
        servo1.writeMicroseconds(1540);
        servo2.writeMicroseconds(1460); //전진
        i++;
        Serial.println("i'm in the cross!!!");
      }
      servo1.writeMicroseconds(1460);
      servo2.writeMicroseconds(1460); //제자리 좌회전
      i++;
      Serial.println("trun!!!");
    }
    turnLeft = 0;
    i = 0;
  }
  else if(enterCross == 1 && turnRight == 1){ //십자길을 만났을 때 (우회전 할때) (반시계방향)
    while(i<135) {  //우회전: 135 90도 회전
      if(i<20){
        servo1.writeMicroseconds(1540);
        servo2.writeMicroseconds(1460); //전진
        i++;
        Serial.println("i'm in the cross!!!");
      }
      servo1.writeMicroseconds(1540);
      servo2.writeMicroseconds(1540); //제자리 우회전
      i++;
      Serial.println("trun!!!");
    }
    turnRight = 0;
    i = 0;
  }

/////////////////////길을 읽는다 //////////////////////////
  if(cm0 > B && cm1 < B && cm2 > B){ //010
    servo1.writeMicroseconds(1540);
    servo2.writeMicroseconds(1460); //전진
  }
  else if(cm0 < B && cm1 < B && cm2 > B){ //110
      servo1.writeMicroseconds(1500); //500
      servo2.writeMicroseconds(1460); //좌회전
  } 
  else if(cm0 < B && cm1 > B && cm2 > B){ //100
      servo1.writeMicroseconds(1500); //500
      servo2.writeMicroseconds(1460); //좌회전  
  }
  else if(cm0 > B && cm1 < B && cm2 < B){ //011
      servo1.writeMicroseconds(1540);
      servo2.writeMicroseconds(1500); //우회전 //500
  }
  else if(cm0 > B && cm1 > B && cm2 < B){ //001
      servo1.writeMicroseconds(1540);
      servo2.writeMicroseconds(1500); //우회전 //500
  }
  else if(cm0 < B && cm1 < B && cm2 < B ){ //111, 십자길 처음만남
    if(enterCross == 0){
        servo1.writeMicroseconds(1500);
        servo2.writeMicroseconds(1500); //정지
        delay(1000);

        enterCross = 1;
        turnRight = 1;
        
    //    if(wclock == 0 ){  //시계방향인지 반시계방향인지 판단 
    //깜박이 방향에 따라 다르게 넣기
    //      turnLeft = 1; //좌회전
    //    }
    //    else{
    //      turnRight = 1;//우회전
    //    }
    
    }
    else if(enterCross == 1)
    {
      servo1.writeMicroseconds(1540);
      servo2.writeMicroseconds(1460); //전진
    }
  }
//101인 경우, 000인 경우는 정의하지 않음


  
  //Serial.println(cm0);
  //Serial.println(cm1);
  Serial.println(cm2);
  Serial.println("-----");
  
}
