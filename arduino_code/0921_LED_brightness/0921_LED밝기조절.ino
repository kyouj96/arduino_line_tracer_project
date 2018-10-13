/* 0921 LED밝기조절하기 
	analogWrite를 이용하여 밝기조절 */

int bli[]={0,60,120,180,255};

int led[]={3,5,6,9,10};
int i=0;

//int q=0,w=1,e=2,r=3,t=4;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led[0], OUTPUT);     
  pinMode(led[1], OUTPUT); 
  pinMode(led[2], OUTPUT); 
  pinMode(led[3], OUTPUT); 
  pinMode(led[4], OUTPUT); 
}

void loop()
{
  /*
  for(int i=0;i<=4;i++){
    
    analogWrite(led[0], b[q++]);
    analogWrite(led[1], b[w++]);
    analogWrite(led[2], b[e++]);
    analogWrite(led[3], b[r++]);
    analogWrite(led[4], b[t++]);
    
    delay(500);
    
    if(q==5)
      q=0;
    if(w==5)
      w=0;
    if(e==5)
      e=0;
    if(r==5)
      r=0;
    if(t==5)
      t=0;
  }*/
  

  	i++;
  	if(i>1000001){ i=0;}
    analogWrite(led[0], bli[i%5]);
    analogWrite(led[1], bli[(i+1)%5]);
    analogWrite(led[2], bli[(i+2)%5]);
    analogWrite(led[3], bli[(i+3)%5]);
    analogWrite(led[4], bli[(i+4)%5]);
    delay(100);
  
}