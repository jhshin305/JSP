#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Scanning for I2C devices...");
}

void loop() {
  // put your main code here, to run repeatedly:
  byte error, address;
  int nDevices = 0;

  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if(error == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
  }

  if(nDevices == 0) {
    Serial.println("No I2C devices found.");
  }
  else {
    Serial.println("Scan complete");
  }
  delay(5000);
}
