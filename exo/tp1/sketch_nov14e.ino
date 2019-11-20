const int r = 10;
const int g = 11;
const int b = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(b,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(r,HIGH);
  delay(300);
  digitalWrite(r,LOW);
  digitalWrite(g,HIGH);
  delay(300);
  digitalWrite(g,LOW);
  digitalWrite(b,HIGH);
  delay(300);
  digitalWrite(b,LOW);
}
