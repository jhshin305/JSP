#include <SoftwareSerial.h>

#define BT_RXD 10
#define BT_TXD 11
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

char c;
int ledpin = 13;

void setup() {
	Serial.begin(9600);
	bluetooth.begin(9600);
	pinMode(ledpin, OUTPUT);
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