// 라이브러리 불러오기
#include <stdio.h>    // printf 출력목적
#include <wiringPi.h>

// PIN 설정
#define led1 1  // P1 pin 12 (wiringPi에서 18번 핀은 1로 매핑)
#define led2 4  // P1 pin 16 (wiringPi에서 23번 핀은 4로 매핑)
#define btn  0  // P1 pin 11 (wiringPi에서 17번 핀은 0으로 매핑)

int main(void) {
    // wiringPi 설정
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed !\n");
        return -1;
    }

    pinMode(led1, OUTPUT);  // LED1 출력 설정
    pinMode(led2, OUTPUT);  // LED2 출력 설정
    pinMode(btn, INPUT);    // 버튼 입력 설정
    pullUpDnControl(btn, PUD_UP);  // 풀업 저항 설정

    // GPIO 제어 시작
    printf("Press CTRL+C to exit\n");

    while (1) {
        if (digitalRead(btn) == HIGH) {  // 버튼을 누르지 않았을 때
            digitalWrite(led1, HIGH);  // LED1 켜기
            digitalWrite(led2, LOW);   // LED2 끄기
        } else {  // 버튼을 눌렀을 때
            digitalWrite(led1, LOW);   // LED1 끄기
            digitalWrite(led2, HIGH);  // LED2 켜기
            delay(100);                // 0.1초 대기
            digitalWrite(led2, LOW);   // LED2 끄기
        }
        delay(100);  // 0.1초 대기
    }

    return 0;
}

