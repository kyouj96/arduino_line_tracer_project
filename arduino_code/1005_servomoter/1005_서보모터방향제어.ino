#include <Servo.h> 

void setup()
{
servo1.attach(13);  //왼쪽
servo2.attach(12);  //오른쪽

}
void loop()
{
servo1.writeMicroseconds(1700);
servo2.writeMicroseconds(1300);
delay(2000);                  //최고 속도로 전진

servo1.writeMicroseconds(1300);
servo2.writeMicroseconds(1700);
delay(2000);                 // 후진

servo1.writeMicroseconds(1550);
servo2.writeMicroseconds(1300); //좌회전
delay(2000);                   

servo1.writeMicroseconds(1700);
servo2.writeMicroseconds(1450); //우회전
delay(2000);

servo1.writeMicroseconds(1450);
servo2.writeMicroseconds(1700); //뒤로 좌회전
delay(2000);

servo1.writeMicroseconds(1300);
servo2.writeMicroseconds(1550); //뒤로 우회전
delay(2000);

servo1.writeMicroseconds(1700);
servo2.writeMicroseconds(1700); //제자리에서 반시계로 돌기
delay(2000);

servo1.writeMicroseconds(1300);
servo2.writeMicroseconds(1300); //제자리에서 시계로 돌기
delay(2000);
}
