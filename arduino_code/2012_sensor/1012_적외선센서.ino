/* 적외선 센서를 사용하여, 검은색 라인에 센서가 닿으면(가까워지면) led가 점등 되도록 구현
    센서가 흰색 바닥에 닿으면(가까워지면) led가 소등된다. */

char Sensor[] = {A2,A3,A4}; //핀의 배열
int Sensor_val[3];
int led[] = {7,8,9};


float cm1, cm2, cm3;
void setup()
{
  Serial.begin(9600);
  pinMode(led[0],OUTPUT);
  pinMode(led[1],OUTPUT);
  pinMode(led[2],OUTPUT);
  //pinMode(Sensor,INPUT);
}

void loop()
{
  Sensor_val[0] = map(analogRead(Sensor[0]), 0, 1023, 0, 5000); //전압값으로 변환
  Sensor_val[1] = map(analogRead(Sensor[1]), 0, 1023, 0, 5000);
  Sensor_val[2] = map(analogRead(Sensor[2]), 0, 1023, 0, 5000);
  
  cm1 = (24.61/(Sensor_val[0]-0.1696))*1000; //cm값으로 변환
  cm2 = (24.61/(Sensor_val[1]-0.1696))*1000;
  cm3 = (24.61/(Sensor_val[2]-0.1696))*1000;
  
  if(cm1 < 7){ //측정값이 가까우면 led 점등
    digitalWrite(led[0],HIGH);
  }
  else
     digitalWrite(led[0],LOW);
     
   if(cm2 < 7){
    digitalWrite(led[1],HIGH);
  }
  else
     digitalWrite(led[1],LOW);
     
   if(cm3 < 7){
    digitalWrite(led[2],HIGH);
  }
  else
     digitalWrite(led[2],LOW);
  
  Serial.println(cm1);
  Serial.println(cm2);
  Serial.println(cm3);
  Serial.println("-----");
  delay(300);
}