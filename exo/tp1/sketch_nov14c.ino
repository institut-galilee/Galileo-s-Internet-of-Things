const int button = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(button));
}
