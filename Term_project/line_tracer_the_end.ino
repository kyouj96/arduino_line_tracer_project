/*  최종 */
#include<Servo.h>
#include "pitches.h"
#define B 7
#define D 8
#define trigPin 3 //초음파
#define echoPin 2 //초음파

char Sensor[] = {A0, A1, A2}; //핀의 배열
int Sensor_val[3];
int SPEAKER = 7;
Servo servo1, servo2;


float cm0, cm1, cm2;
long duration, cm;

int Led1 = 11;
int Led2 = 6;

///////////////////// Flag /////////////////////////
int enterCross = 0;//십자길을 마주하였다.

int turnFlag = 0 ; // 0: 돌지 않는 상태 1:좌회전 2:우회전

int wclock = 0;  //시계 방향 반시계 방향 //0:시계방향 1:반시계 방향

int gorge = 1; //차고지에 있다/없다

////////////////// 배 열 //////////////////////////

int j = 0, p = 0;        // j는 우리가 가야하는 정류장 순서의 index

int count = 0;      // 몇 칸을 이동해야 하는 지
int nowCount = 0;     // 현재 이동한 칸 수

int l = 0; // 버스의 현재 위치(Location)를 나타내기 위한 변수 -> StaionNumber 의 index로 사용됨
// 처음에는 차고지(l = 0) 이다.

int ClockwiseSum = 0, CounterSum = 0, Sum = 0;
// ClockwiseSum은 시계방향으로 더한 것, CounterSum 은 반시계방향으로 더한 것
// Sum은 정류장 간 총 거리

int StationNumber[8] = {0,3,1,4,7,5,6,2}; // 정류장 번호 ( 시계 방향 기준 )
int OrderToGo[8] = {5,7,2,3,4,5,1,0}; // 가야 하는 정류장 순서
int Length[8] = {34,2,25,55,48,23,4,80}; // 정류장 간 거리 ( 시계 방향 기준 )

//////////////////////// setup  /////////////////////////
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);//초음파
  pinMode(echoPin, INPUT);//초음파
  pinMode(Sensor, INPUT);
  servo1.attach(13);  //왼쪽
  servo2.attach(12);  //오른쪽
  pinMode(Led1, OUTPUT); //led 왼쪽
  pinMode(Led2, OUTPUT); //led 오른쪽
  pinMode(SPEAKER, OUTPUT); // 스피커


  for (int k = 0; k < 8; k++)
    Sum += Length[k];         // 정류장 간 총 거리를 구한다.

}

void Music ()
{
  int notes[] = {
    NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_E5, 0,
    NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_FS5, 0,
    NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_CS5, NOTE_B5, NOTE_B5, NOTE_A5, NOTE_A5,
    NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_E5, 0,
    NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_E5, 0,
    NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_FS5, 0,
    NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_CS6, NOTE_B5, NOTE_B5, NOTE_A5, NOTE_A5,
    NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_A5, 0
  };

  int times[] = {
    250, 250, 250, 500, 500, 250,
    250, 250, 250, 500, 500, 250,
    250, 250, 250, 250, 250, 250, 250, 250,
    250, 250, 250, 500, 750,
    250, 250, 250, 500, 500, 250,
    250, 250, 250, 500, 500, 250,
    250, 250, 250, 250, 250, 250, 250, 250,
    250, 250, 250, 500, 750
  };
  for (int i = 0; i < 50; i++)
  {
    tone(SPEAKER, notes[i], times[i]);
    delay(times[i]);
  }
}

void BBangBBang () {

  int notes[] = {
    NOTE_G6, NOTE_G6, 0, NOTE_G6, NOTE_G6
  };

  int times[] = {
    200, 200, 200, 200, 200
  };

  for (int i = 0; i < 5; i++)
  {
    tone(SPEAKER, notes[i], times[i]);
    delay(times[i]);
  }
}

void ReadIR() //적외선 읽기
{
  Sensor_val[0] = map(analogRead(Sensor[0]), 0, 1023, 0, 5000); //전압값으로 변환
  Sensor_val[1] = map(analogRead(Sensor[1]), 0, 1023, 0, 5000);
  Sensor_val[2] = map(analogRead(Sensor[2]), 0, 1023, 0, 5000);

  cm0 = (24.61 / (Sensor_val[0] - 0.1696)) * 1000; //cm값으로 변환
  cm1 = (24.61 / (Sensor_val[1] - 0.1696)) * 1000;
  cm2 = (24.61 / (Sensor_val[2] - 0.1696)) * 1000;
}


void ReadM() { //초음파를 읽는 함수
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //초음파 발생
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //시간 측정
  // convert the time into a distance
  cm = duration / 29 / 2;
}



void letsgo() { //일반적인 주행
  if (cm0 > B && cm2 > B) { //0x0
    servo1.writeMicroseconds(1540);
    servo2.writeMicroseconds(1460); //전진
  }
  else if (cm0 < B && cm2 > B) { //1x0
    servo1.writeMicroseconds(1500); //500
    servo2.writeMicroseconds(1460); //좌회전
  }
  else if (cm0 > B && cm2 < B) { //0X1
    servo1.writeMicroseconds(1540);
    servo2.writeMicroseconds(1500); //우회전 //500
  }

}

void backward() { //뒤로가는 길을 읽는 함수
  if (cm0 > B && cm2 > B) { //0x0
    servo1.writeMicroseconds(1460);
    servo2.writeMicroseconds(1540); //후진
  }
  else if (cm0 < B && cm2 > B) { //1x0
    servo1.writeMicroseconds(1500); //500
    servo2.writeMicroseconds(1540); //좌회전
  }
  else if (cm0 > B && cm2 < B) { //0X1
    servo1.writeMicroseconds(1460);
    servo2.writeMicroseconds(1500); //우회전 //500
  }
}





void turn(int turnFlag) { //turnFlag 를 인자로 받음
  if (turnFlag == 1) ////십자길을 만났을 때 (좌회전 할때)
  {
    servo1.writeMicroseconds(1500);
    servo2.writeMicroseconds(1400); //제자리 좌회전
    delay(1150);

    while (!(cm0 > B && cm1 < B && cm2 < B) ) { //좌회전
      ReadIR();
      servo1.writeMicroseconds(1500);
      servo2.writeMicroseconds(1445); //제자리 좌회전
    }
    turnFlag = 0; //돌지 않는 상태
  }
  else if (turnFlag == 2) //우회전 할때
  {
    servo1.writeMicroseconds(1600);
    servo2.writeMicroseconds(1500); //제자리 우회전
    delay(1150);

    while (!(cm0 < B && cm1 < B && cm2 > B)) { //우회전
      ReadIR();
      servo1.writeMicroseconds(1555);
      servo2.writeMicroseconds(1500); //제자리 우회전
    }
    turnFlag = 0; //돌지 않음
  }
}

void backTurn() { //뒤로갈때 길을 읽는 함수
  //십자가 길을 들어왔고, 장애물 거리가 5이하이면 1초간 정지후 후진
  while (1) {
    ReadIR();
    letsgo();
    ReadM(); //초음파를 읽는다
    if (cm == 5) {
      servo1.writeMicroseconds(1500);
      servo2.writeMicroseconds(1500);
      delay(365);//정지
      BBangBBang();
      delay(1000); //1초간 정지

      while ( !(cm0 > B && cm1 > B && cm2 > B) ) {
        ReadIR(); //적외선 센서를 읽는다
        servo1.writeMicroseconds(1460);
        servo2.writeMicroseconds(1540); //후진
      }

      while ( !(cm0 < B && cm2 < B) ) { //후진해서 길을 나가면 다시 길을 찾음
        ReadIR();
        letsgo();
      }

      break;
    }

  }
}




void start(int turnFlag) {
  while ( !(cm0 < B && cm1 < B && cm2 < B ) ) { //검은색을 만날 때 까지
    ReadIR();//적외선 센서 인식 함수
    servo1.writeMicroseconds(1540);
    servo2.writeMicroseconds(1460); //전진
  }
  gorge = 0;
  //turnFlag = turn; //좌회전 : 1 , 우회전 : 2
  //turnFlag 값 정해주기

  turn(turnFlag); //차고지에서 나와서 회전하는

}

////////////////////////   loop   /////////////////////////////////////////////////////////////////////
void loop()
{


  Serial.println(Sum);
  ReadIR();//적외선 센서 인식 함수

  // 가야하는 정류장이 시계방향 기준으로 몇 번째 있는지 확인

  for (p = 0; OrderToGo[j] != StationNumber[p]; p++);
  // StationNumber[p] 는 우리가 가야하는 정류장이 시계방향으로 몇 번째 있는지


  if (l < p)   // 현재 있는 위치가 가야할 위치보다 작은 index에 있을 때 (시계방향 기준)
  {
    for (int k = l; k < p; k++)
      ClockwiseSum += Length[k];      // 시계 방향으로 갔을 때의 거리

    CounterSum = Sum - ClockwiseSum;   // 반시계 방향으로 갔을 때의 거리
  }
  else      // 현재 있는 위치가 가야할 위치보다 큰 index에 있을 때
  {
    for (int k = l; k < 8; k++)
      ClockwiseSum += Length[k];   // 끝 까지 더하고
    for (int k = 0; k < p; k++)
      ClockwiseSum += Length[k];   // 또 더한다


    CounterSum = Sum - ClockwiseSum;   // 반시계 방향으로 갔을 때의 거리

  }


  // 몇 칸 이동하는지를 정하는 부분

  if (l < p)   // 현재 있는 위치가 가야할 위치보다 작은 index에 있을 때 (시계방향 기준)
  {
    if (ClockwiseSum <= CounterSum)
      count = p - l;
    else
      count = 8 - (p - l);

  }
  else
  {
    if (ClockwiseSum >= CounterSum)
      count = l - p;
    else
      count = 8 - (l - p);
  }



  if (ClockwiseSum > CounterSum)      // 반시계방향 거리가 반시계방향 거리보다 짧을 경우
  {

    digitalWrite(Led1, HIGH);
    digitalWrite(Led2, LOW);

    // 반시계방향으로 간다.
    // count 칸 이동

    if (gorge)
      start(2);   // 반시계방향 -> 시작할 때 우회전
    else
      turn(1);     // 반시계방향 -> 시작할 때 좌회전



    if (j == 7)
      digitalWrite(Led2, HIGH);


    while (1)
    {
      ReadIR();
      letsgo();



      if (cm0 < B && cm2 < B) { // 1X1, 십자길을 만남
        servo1.writeMicroseconds(1500);
        servo2.writeMicroseconds(1500); // 잠깐 정지
        delay(100);
        nowCount++;

        Serial.println(nowCount);


        if (count == nowCount) {
          turn(2);
          // 들어가기 -> 우회전

          if (j == 7)
          {
            // 차고지!
            servo1.writeMicroseconds(1540);
            servo2.writeMicroseconds(1460); //전진
            delay(365);
            servo1.writeMicroseconds(1500);
            servo2.writeMicroseconds(1500);
            delay(365);
            Music(); Music();
            delay(1000);
            break;
          }

          backTurn();
          // 초음파 후 후진


          break;  // while(1) 탈출

        }
        else {
          while ((cm0 < B && cm2 < B) ) {
            ReadIR();
            servo1.writeMicroseconds(1540);
            servo2.writeMicroseconds(1460); //전진
            //                // 조금 직진 한뒤 letsgo
          }
          servo1.writeMicroseconds(1540);
          servo2.writeMicroseconds(1460); //전진
          delay(365);

        }
      }


    }
  }
  else                        // 시계방향 거리가 반시계방향 거리보다 짧거나 같을 경우
  {

    digitalWrite(Led2, HIGH);
    digitalWrite(Led1, LOW);

    // 시계방향으로 간다.
    // count 칸 이동

    if (gorge)
      start(1);   // 시계방향 -> 시작할 때 좌회전
    else
      turn(2);     // 시계방향 -> 시작할 때 우회전




    if (j == 7)
      digitalWrite(Led1, HIGH);

    while (1)
    {
      ReadIR();
      letsgo();


      if (cm0 < B && cm2 < B) { // 1X1, 십자길을 만남
        servo1.writeMicroseconds(1500);
        servo2.writeMicroseconds(1500); // 잠깐 정지
        delay(100);
        nowCount++;

        Serial.println(nowCount);

        if (count == nowCount) {
          turn(1);
          // 들어가기 -> 우회전

          if (j == 7)
          {
            // 차고지!
            servo1.writeMicroseconds(1540);
            servo2.writeMicroseconds(1460); //전진
            delay(365);
            servo1.writeMicroseconds(1500);
            servo2.writeMicroseconds(1500);
            delay(365);
            Music(); Music();
            delay(1000);
            break;
          }

          backTurn();
          // 초음파 후 후진


          break;  // while(1) 탈출

        }
        else {

          while ((cm0 < B && cm2 < B) ) {
            ReadIR();
            servo1.writeMicroseconds(1540);
            servo2.writeMicroseconds(1460); //전진
            //                // 조금 직진 한뒤 letsgo
          }

          servo1.writeMicroseconds(1540);
          servo2.writeMicroseconds(1460); //전진
          delay(365);

        }
      }



    }
  }


  // 목적지 정류장에  도착 한 후
  ClockwiseSum = 0, CounterSum = 0, nowCount = 0;
  l = p;   // 현재 정류장 위치를 재설정 하는 거임
  j++;   // OrderToGo의 index를 1 증가시킨다 ( 다음으로 가야하는 정류장 위치를 확인하기 위함)

}