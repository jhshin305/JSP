# GPIO 라이브러리 불러오기
import RPi.GPIO as GPIO
import time

# PIN 설정
ButtonPin = 17  # 사용할 버튼 핀 번호

# GPIO 설정
GPIO.setmode(GPIO.BCM)  # 브로드컴 핀 넘버링으로 설정
GPIO.setup(ButtonPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # 버튼 핀을 입력, 풀업 설정

buttonPressed = 0

try:
    while True:
        buttonInput = GPIO.input(ButtonPin)  # 버튼 입력 읽기
        if buttonInput == GPIO.LOW:
            buttonPressed = 1
        if buttonPressed and buttonInput == GPIO.HIGH:
            print("Button Pressed!")
            buttonPressed = 0
        time.sleep(0.01)  # 10ms 지연

except KeyboardInterrupt:
    # 종료 시 GPIO 핀 초기화
    GPIO.cleanup()
