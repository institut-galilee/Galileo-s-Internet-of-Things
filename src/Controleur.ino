#include <Projet.h>

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);

joystick <A0, A1, 2> Joystick;

bool Etat = false;

void setup()
{
  BTSerial.begin(9600);

  //Serial.begin(9600);
  Joystick.connecter();
}

void loop()
{
  if (Joystick.est_appuye())
  {
    Etat = !Etat;
    
  }
  
  if (Etat)
  {
    int x = analogRead(A0), y = analogRead(A1);
    byte G, D;
    
    if (x > 511)
    {
      if (y > 511)
      {
        if (x > y)  // X > Y
        {
          G = (x - 512) * 0.5;
          D = (x - y) * 0.5;

          BTSerial.print('D');
          BTSerial.write(D);
          
          //Droite.avancer(D);
        }
        else
        {
          G = (y - 512  ) * 0.5;
          D = (y - x) * 0.5;

          BTSerial.print('d');
          BTSerial.write(D);
          
          //Droite.reculer(D);
        }

        BTSerial.print('G');
        BTSerial.write(G);
        
        //Gauche.avancer(G);
      }
      else
      {
        G = (x + y - 511) * 0.5; ////////////////////////////////////////////////////////////
        
        if (x + y >= 1023) // X > Y
        {
          D = (x - 512) * 0.5;

          BTSerial.print('G');
          BTSerial.write(G);
          
          //Gauche.avancer(G);
        }
        else
        {
          D = (511 - y) * 0.5;

          BTSerial.print('g');
          BTSerial.write(G);
          
          //Gauche.reculer(G);
        }

        BTSerial.print('D');
        BTSerial.write(D);
        
        //Droite.avancer(D);
      }
    }
    else
    {
      if (y > 511)
      {
        if (x + y < 1023) // X > Y   511 - x > y - 512
        {
          G = (511 - x) * 0.5;
          D = (y - x) * 0.5;

          BTSerial.print('d');
          BTSerial.write(D);
          
          //Droite.reculer(D);
        }
        else
        {
          G = (y - 512) * 0.5;
          D = (x + y) * 0.5;
          
          BTSerial.print('D');
          BTSerial.write(D);
          
          //Droite.avancer(D);
        }

        BTSerial.print('g');
        BTSerial.write(G);
        
        //Gauche.reculer(G);
      }
      else
      {
        if (x > y) // X > Y
        {
          D = (511 - y) * 0.5;
          G = (x - y) * 0.5;

          BTSerial.print('G');
          BTSerial.write(G);
          
          //Gauche.avancer(G);
        }
        else
        {
          D = (511 - x) * 0.5;
          G = (y - x) * 0.5;

          BTSerial.print('g');
          BTSerial.write(G);
        
          //Gauche.reculer(G);
        }
        
        BTSerial.print('d');
        BTSerial.write(D);
        
        //Droite.reculer(D);
      }
    }
  }
  else
  {
    BTSerial.write('a');
  }
}
