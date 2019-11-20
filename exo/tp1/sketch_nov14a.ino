const int R = 11;
const int G = 10;
const int B = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(R,HIGH);
  delay(3000);
  digitalWrite(R,LOW);
  digitalWrite(G,HIGH);
  delay(3000);
  digitalWrite(G,LOW);
  digitalWrite(B,HIGH);
  delay(3000);
  digitalWrite(B,LOW);
}
