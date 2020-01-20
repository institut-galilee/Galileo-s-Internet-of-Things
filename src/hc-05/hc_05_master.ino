#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX  = > BT-TX=10 BT-RX=11

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter a command:");
  BTSerial.begin(9600);  // HC-05 9600 baud 
}

void loop()
{
    String message;
    while (Serial.available())
    {
      message = Serial.readString();
      BTSerial.println(message);
    }
}
