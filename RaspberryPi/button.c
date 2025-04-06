#include <wiringPi.h>
#include <stdio.h>

#define ButtonPin 7

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("Setup wiringPi failed.\n");
        return -1;
    }
    
    pinMode(ButtonPin, INPUT);
    int buttonPressed = 0;
    
    while(1) {
        int buttonInput = digitalRead(ButtonPin);
        if (buttonInput == LOW) {
            buttonPressed = 1;
        }
        if (buttonPressed && buttonInput == HIGH) {
            printf("Button Pressed!\n");
            buttonPressed = 0;
        }
        delay(10);
    }
    
    return 0;
}
