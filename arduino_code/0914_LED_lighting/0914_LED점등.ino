/*0914_LED점등
  팀빌딩 : 3조 16김유진 18이명진 18김도욱 18강지완
  led 3개를 사용하여 2진수 0~7 까지 파도타기처럼 이어서 점등하기 */

int led[] ={13,8,2};

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  //001
  digitalWrite(2, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  digitalWrite(2, LOW);
  //delay(500); // Wait for 1000 millisecond(s)
  
  //010
  digitalWrite(8, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  digitalWrite(8, LOW);
  //delay(500); // Wait for 1000 millisecond(s)
  
  //011
  digitalWrite(2, HIGH);
  digitalWrite(8, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  digitalWrite(2, LOW);
  digitalWrite(8, LOW);
  //delay(500); // Wait for 1000 millisecond(s)
  
  //100
  digitalWrite(13, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  //delay(500); // Wait for 1000 millisecond(s)
  
  //101
  digitalWrite(2, HIGH);
  digitalWrite(13, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  digitalWrite(2, LOW);
  digitalWrite(13, LOW);
  //delay(500); // Wait for 1000 millisecond(s)
  
  //110
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
  //delay(500); // Wait for 1000 millisecond(s)
  
  //111
  digitalWrite(2, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  delay(500); // Wait for 1000 millisecond(s)
  
  //000
  digitalWrite(2, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
  delay(500); // Wait for 1000 millisecond(s)
 
  
}