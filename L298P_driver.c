// Shield terminal variables
byte pwmA = 10;
byte pwmB = 11;
byte enA = 12;
byte enB = 13;
byte buz = 4;

// 
void setup() {
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(buz, OUTPUT);
}

void loop() {
  for (int x = 50; x < 200; x++) {
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    analogWrite(pwmA, x);
    analogWrite(pwmB, x);
    delay(10);
  }
  for (int y = 200; y > 50; y--) {
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    digitalWrite(buz, HIGH);
    analogWrite(pwmA, y);
    analogWrite(pwmB, y);
    delay(1);
  }
  digitalWrite(buz, LOW);
  delay(1000);
}
