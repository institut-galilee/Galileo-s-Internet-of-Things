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

int LuminositeGauche, LuminositeDroite;

bool Autonome = false;

void setup()
{
	Led.connecter();

	PhotoGauche.connecter();
	PhotoDroite.connecter();

	Gauche.connecter();
	Droite.connecter();

	CapteurGauche.connecter();
	CapteurDroite.connecter();

	BTSerial.begin(9600);

	LuminositeGauche = PhotoGauche.luminosite();
	LuminositeDroite = PhotoDroite.luminosite();
}

void loop()
{
	if (BTSerial.available())
	{
		switch ((char)BTSerial.read())
		{
		case 'A':
				
			bool Allumer = false;

			if (PhotoGauche.luminosite() < LuminositeGauche)
			{
				Gauche.arreter();
				Allumer = true;
			}
			else
			{
				while (!BTSerial.available());
				Gauche.avancer(BTSerial.read());
			}

			if (PhotoDroite.luminosite() < LuminositeDroite)
			{
				Droite.arreter();
				Allumer = true;
			}
			else
			{
				while (!BTSerial.available());
				Droite.avancer(BTSerial.read());
			}

			if (Allumer)
			{
				Led.allumer();
			}
			else
			{
				Led.eteindre();
			}

			break;

		case 'g':
			while (!BTSerial.available());
			Gauche.reculer((byte)BTSerial.read());
			break;

		case 'G':
			while (!BTSerial.available());
			Gauche.avancer((byte)BTSerial.read());
			break;

		case 'd':
			while (!BTSerial.available());
			Droite.reculer((byte)BTSerial.read());
			break;

		case 'D':
			while (!BTSerial.available());
			Droite.avancer((byte)BTSerial.read());
			break;
		}
	}
}