#include <Servo.h>

Servo servo;
int servo_pin = 2;
int motor_degree = 0;

int VRx = A0;
int x_pos;
int x = 0;

void setup() {
	Serial.begin(9600);

	servo.attach(servo_pin);
	pinMode(VRx, INPUT);
}

void loop() {
	x_pos = analogRead(VRx);
	x = map(x_pos, 0, 1023, -512, 512);
	
	if(x == 512) motor_degree++;
	else if(x == -512) motor_degree--;

	if(motor_degree < 0) motor_degree = 0;
	if(motor_degree > 180) motor_degree = 180;
  
	servo.write(motor_degree);
}