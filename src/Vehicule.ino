#include <Projet.h>

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1);

led <13> Led;

moteur <3, 5> Gauche;
moteur <9, 10> Droite;
capteur <12, 11, 10> CapteurGauche;
capteur <7, 6, 10> CapteurDroite;

photoresistance <A2> PhotoGauche;
photoresistance <A3> PhotoDroite;

int VitesseGauche = 0, VitesseDroite = 0;
int IntensiteMinimale = 300, IntensiteMaximale = 800;
int EcartIntensite = IntensiteMaximale - IntensiteMinimale;

void setup()
{
  Led.connecter();
  
  PhotoGauche.connecter();
  PhotoDroite.connecter();
  
  Gauche.connecter();
  Droite.connecter();
  
  CapteurGauche.connecter();
  CapteurDroite.connecter();
  
  Serial.begin(9600);
  BTSerial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
}

//int LuminositePrecedante = 0;

int pred = 0;

void loop()
{
  if (BTSerial.available())
  {
    char Caractere = BTSerial.read();
    byte Vitesse;
    Serial.println(Caractere);
    switch (Caractere)
    {
      case 'A' :
        Led.allumer();
        break;
      case 'a' :
        Gauche.arreter();
        Droite.arreter();
        break;
      case 'E' :
        Led.eteindre();
        break;
      case 'g' :
        while (!BTSerial.available());
        Vitesse = BTSerial.read();
        Gauche.reculer(Vitesse);
        break;
      case 'G' :
      while (!BTSerial.available());
        Vitesse = BTSerial.read();
        Gauche.avancer(Vitesse);
        break;
     case 'd' :
     while (!BTSerial.available());
        Vitesse = BTSerial.read();
        Droite.reculer(Vitesse);
        break;
     case 'D' :
     while (!BTSerial.available());
        Vitesse = BTSerial.read();
        Droite.avancer(Vitesse);
        break;
    }
  }

  
//  int Luminosite = PhotoGauche.luminosite();
//  
//  if (Luminosite < IntensiteMinimale)
//  {
//    Marche = false;
//  }
//  else
//  {
//    if (Luminosite < IntensiteMaximale)
//    {
//      int Reduction = Luminosite / EcartIntensite;////
//    }
//  }
  
//  auto a = PhotoGauche.luminosite();
//  auto b = PhotoDroite.luminosite();
//  
//  Serial.print("G = ");
//  Serial.println(pred - a);
  //Serial.print(" D = ");
  //Serial.println(b);

//  pred = a;
//  delay(500);
}
