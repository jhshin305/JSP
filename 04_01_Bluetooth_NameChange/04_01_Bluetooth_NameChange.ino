#include <SoftwareSerial.h>

#define BT_RXD 3
#define BT_TXD 2
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

delay(1000);
Serial.print("HC-06 AT 모드 테스트 시작"); 
}

void loop() {
  if(bluetooth.available()) {
	char c = bluetooth.read();
	Serial.print(c);
  }
  if(Serial.available()) {
	char c = Serial.read();
	bluetooth.print(c);
  }
}