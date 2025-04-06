# GPIO 라이브러리 불러오기
import RPi.GPIO as GPIO
import time

# PIN 설정
LedPin = 18  # 사용할 LED 핀 번호

# GPIO 설정
GPIO.setmode(GPIO.BCM)  # 브로드컴 핀 넘버링으로 설정
GPIO.setup(LedPin, GPIO.OUT)  # LED 핀을 출력으로 설정

try:
    while True:
        GPIO.output(LedPin, GPIO.HIGH)  # LED 켜기
        print("LED on")
        time.sleep(1)  # 1초 대기

        GPIO.output(LedPin, GPIO.LOW)  # LED 끄기
        print("LED off")
        time.sleep(1)  # 1초 대기

except KeyboardInterrupt:
    # 종료 시 GPIO 핀 초기화
    GPIO.cleanup()
