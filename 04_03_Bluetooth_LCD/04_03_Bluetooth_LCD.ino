#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BT_RXD 10
#define BT_TXD 11
liquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

void setup() {
	Serial.begin(9600);
	bluetooth.begin(9600);
	lcd.init();
	lcd.backlight();
}

void loop() {
	if(bluetooth.available()) {
		lcd.init();
		String str = "";
		while(bluetooth.available()) {
			char tmp = bluetooth.read();
			if(tmp == '\n') {
				break;
			}
			str += tmp;
			delay(3);
		}
		lcd.setCursor(0, 0);
		lcd.print(str);
	}
}