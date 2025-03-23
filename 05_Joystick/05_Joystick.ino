int VRx = A0;
int VRy = A1;
int SW = 2;

int x_position = 0;
int y_position = 0;
int button = 0;
int x = 0;
int y = 0;

void setup() {
	Serial.begin(9600);
	pinMode(VRx, INPUT);
	pinMode(VRy, INPUT);
	pinMode(SW, INPUT_PULLUP);
}

void loop() {
	x_position = analogRead(VRx);
	y_position = analogRead(VRy);
	button = digitalRead(SW);

	x = map(x_position, 0, 1023, -512, 512);
	y = map(y_position, 0, 1023, -512, 512);
	Serial.print("\nX: ");
	Serial.print(x);
	Serial.print(" | Y: ");
	Serial.print(y);
	if(!button) {
		Serial.print("\n버튼이 눌렸습니다!");
	}
	delay(100);
}