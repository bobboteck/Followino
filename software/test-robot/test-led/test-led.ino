
// D4: led status 1
// D9: led status 2

int ledPin = 4;
int ledPin_red = 9;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin_red, OUTPUT);
}

void loop() {
  digitalWrite(ledPin_red, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin_red, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);       
}
