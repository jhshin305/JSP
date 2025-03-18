String s;
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    char c;
    c = Serial.read();
    if(c == '\n') {
      if( s=="on") {
        digitalWrite(ledPin, HIGH);
        Serial.print("led = on\n");
        s="";
      }
      else if(s == "off") {
        digitalWrite(ledPin, LOW);
        Serial.print("led = off\n");
        s="";
      }
    }
    else s+=c;
  }
}
