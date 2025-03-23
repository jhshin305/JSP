#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper stepper(stepsPerRevolution, 11, 9, 10, 8);

int VRx = A0;
int x_pos;
int x = 0;

void setup() {
	Serial.begin(9600);

	stepper.setSpeed(5);
	pinMode(VRx, INPUT);
}

void loop() {
	x_pos = analogRead(VRx);
	x = map(x_pos, 0, 1023, -512, 512);

	if(x > 300) stepper.step(10);
	if(x < -300) stepper.step(-10);
}