# GPIO 라이브러리 불러오기
import RPi.GPIO as GPIO
import time

# PIN 설정
led1 = 18  # P1 pin 12
led2 = 23  # P1 pin 16
btn  = 17  # P1 pin 11

# GPIO 설정
GPIO.setmode(GPIO.BCM)  # 브로드컴 핀 넘버링으로 설정
GPIO.setup(led1, GPIO.OUT)  # LED1에 사용할 18번 핀 OUTPUT으로 설정
GPIO.setup(led2, GPIO.OUT)  # LED2에 사용할 23번 핀 OUTPUT으로 설정
GPIO.setup(btn, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # 버튼에 사용할 17번 핀 입력, 풀업 설정

# GPIO 제어 시작
print("Press CTRL+C to exit")

try:
    while 1:
        if GPIO.input(btn):  # 버튼을 누르지 않았을 때
            GPIO.output(led1, GPIO.HIGH)  # LED1 켜기
            GPIO.output(led2, GPIO.LOW)   # LED2 끄기
        else:  # 버튼을 눌렀을 때
            GPIO.output(led1, GPIO.LOW)  # LED1 끄기
            GPIO.output(led2, GPIO.HIGH) # LED2 켜기
            time.sleep(0.1)
            GPIO.output(led2, GPIO.LOW)  # LED2 끄기
        time.sleep(0.1)

except KeyboardInterrupt:  # Ctrl+C 를 눌러서 종료 할 경우
    GPIO.cleanup()  # GPIO 초기화
