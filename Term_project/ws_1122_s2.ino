/* 선을 따라 갈 수 있다.
    흰색에서는 멈춘다.
    십자모양길을 만나면 멈춘다.
     90도 좌회전 한다.
*/
#include <Servo.h>

char Sensor[] = {A0, A1, A2};  // 로봇에서 1 2 3 순서
int Sensor_val[3];
Servo servo1, servo2;

float cm0, cm1, cm2;

int i = 0; //90도 도는지 확인 할 변수

int turnFlag = 0; //돌기위해 나머지 if를 멈추기위한 flag
int enterCross = 0; //십자길을 마주했을 때 flag

void setup()
{
  Serial.begin(9600); //시리얼

  servo1.attach(13);  //오른쪽
  servo2.attach(12);  //왼쪽
  //pinMode(Sensor,INPUT);
}

void loop()
{
  Sensor_val[0] = map(analogRead(Sensor[0]), 0, 1023, 0, 5000); //전압값으로 변환
  Sensor_val[1] = map(analogRead(Sensor[1]), 0, 1023, 0, 5000);
  Sensor_val[2] = map(analogRead(Sensor[2]), 0, 1023, 0, 5000);

  cm0 = (24.61 / (Sensor_val[0] - 0.1696)) * 1000; //cm값으로 변환
  cm1 = (24.61 / (Sensor_val[1] - 0.1696)) * 1000;
  cm2 = (24.61 / (Sensor_val[2] - 0.1696)) * 1000;

  if (turnFlag == 1 && enterCross == 1) {  //십자 길을 만났을 때
    if ( i < 20) {  //조금 전진
      servo1.writeMicroseconds(1540);
      servo2.writeMicroseconds(1460); //전진
      i++;
      Serial.println("i'am in the cross!!!");
      //delay(1000);
    }
   
    servo1.writeMicroseconds(1460);
    servo2.writeMicroseconds(1460); //제자리 좌회전
    i++;
    Serial.println("trun!!!");
    
    if (i > 135) { //90도 돌고나면 flag를 0으로
      enterCross = 0;
      turnFlag = 0;
      i=0;
      servo1.writeMicroseconds(1500);
      servo2.writeMicroseconds(1500);//정지
      delay(1000);
    }
  }

  if ( cm1 < 7 && cm2 < 7 && enterCross == 0) { // X11
    if (cm0 < 7) { //111 (십자길처음 만남)
      
      servo1.writeMicroseconds(1500);
      servo2.writeMicroseconds(1500);//정지
      delay(1000);
      
      enterCross = 1;
      turnFlag = 1;
      Serial.println("meet cross!!!");
    }
    else if (cm0 > 7  ) { //110 (일자길) 전진
      servo1.writeMicroseconds(1540);
      servo2.writeMicroseconds(1460);//전진
      
    }
  }
  else if (cm1 < 7 && cm2 > 7 ) { // X10   //우회전
    servo1.writeMicroseconds(1500);
    servo2.writeMicroseconds(1460);// 제자리 우회전
  }
  else if (cm1 > 7 && cm2 < 7 ) { // X01  //좌회전
    servo1.writeMicroseconds(1540);
    servo2.writeMicroseconds(1500);// 제자리 좌회전
  }

  else if (cm1 > 7 && cm2 > 7 ) { //X00  //정지
    servo1.writeMicroseconds(1500);
    servo2.writeMicroseconds(1500);// 정지
  }
}