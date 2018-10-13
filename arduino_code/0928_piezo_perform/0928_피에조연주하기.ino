/* 0928 스피커로 음악 재생하기 
	피에조를 이용하여 음악 연주하기 */

#include "pitches.h" //계이름이 정의된 헤더 파일 삽입

const int SPEAKER=11; //11번 핀을 사용하는 SPEAKER 상수 정의

//연주할 음이 저장된 배열 notes 선언
int notes[]= {
    NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
    NOTE_E4, NOTE_E3, NOTE_A4, 0
};

//음의 지속 시간이 저장된 배열 times 선언. 단위는 ms
int times[]= {
    250, 250, 250, 250,
    250, 250, 250, 250,
    125, 125, 125, 125, 125, 125, 125, 125,
    250, 250, 250, 250
};
 
void setup()
{
    //계이름, 지속 시간 배열 순서대로 음악 재생
    for(int i=0; i<20; i++)
    {
        tone(SPEAKER, notes[i], times[i]);
        delay(times[i]);
    }
}

void loop()
{
    //음악을 다시 들으려면 리셋 버튼을 누름
}
