const int buzzer = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(buzzer,1000);
  delay(300);
}
