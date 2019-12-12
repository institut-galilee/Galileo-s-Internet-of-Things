#include <SoftwareSerial.h>
#define PIN_LED 13

SoftwareSerial BTSerial(0, 1); // RX | TX  = > BT-TX=10 BT-RX=11

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter a command:");
  BTSerial.begin(9600);  // HC-05 9600 baud 

  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
    String message;
    while (BTSerial.available())
    {
      message = BTSerial.readString();
      Serial.println(message);
    }
    if(message == "on\r\n")
    {
      digitalWrite(PIN_LED,HIGH);
    }
    else if(message == "off\r\n")
    {
      digitalWrite(PIN_LED,LOW);  
    }
}
