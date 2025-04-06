#include <SoftwareSerial.h>

#define BT_RXD 3
#define BT_TXD 2
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

char c;
int ledpin = 13;

void setup() {
	Serial.begin(9600);
	bluetooth.begin(9600);
	pinMode(ledpin, OUTPUT);
	delay(1000);
	Serial.println("HC-06 AT 모드 테스트 시작");
}

void loop() {
	if(bluetooth.available()) {
		c = bluetooth.read();
		Serial.println(c);
		switch (c)
		{
		case '0':
			digitalWrite(ledpin, LOW);
			break;
		
		case '1':
			digitalWrite(ledpin, HIGH);
			break;
		}
	}
}