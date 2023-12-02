const int buzz_pin = 3;

void setup() {
  // put your setup code here, to run once:
   pinMode(buzz_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(buzz_pin, 127);
  delay(500);
  analogWrite(buzz_pin, 0);
  delay(500);
}
