#include <Projet.h>

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);
joystick <A0, A1, 2> Joystick;

bool Etat = true;

void setup()
{
	BTSerial.begin(9600);

	Joystick.connecter();
}

byte precision(byte Vitesse)
{
	if (Vitesse < 100)
	{
		return 0;
	}
	else
	{
		return (Vitesse - 99.0) * 255.0 / (255.0 - 99.0);
	}
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
					BTSerial.write(precision(D));
				}
				else
				{
					G = (y - 512) * 0.5;
					D = (y - x) * 0.5;

					BTSerial.print('d');
					BTSerial.write(precision(D));
				}

				BTSerial.print('G');
				BTSerial.write(precision(G));
			}
			else
			{
				G = (x + y - 511) * 0.5; ////////////////////////////////////////////////////////////

				if (x + y >= 1023) // X > Y
				{
					D = (x - 512) * 0.5;

					BTSerial.print('G');
					BTSerial.write(precision(G));
				}
				else
				{
					D = (511 - y) * 0.5;

					BTSerial.print('g');
					BTSerial.write(precision(G));
				}

				BTSerial.print('D');
				BTSerial.write(precision(D));
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
					BTSerial.write(precision(D));
				}
				else
				{
					G = (y - 512) * 0.5;
					D = (x + y) * 0.5;

					BTSerial.print('D');
					BTSerial.write(precision(D));
				}

				BTSerial.print('g');
				BTSerial.write(precision(G));
			}
			else
			{
				if (x > y) // X > Y
				{
					D = (511 - y) * 0.5;
					G = (x - y) * 0.5;

					BTSerial.print('G');
					BTSerial.write(precision(G));
				}
				else
				{
					D = (511 - x) * 0.5;
					G = (y - x) * 0.5;

					BTSerial.print('g');
					BTSerial.write(precision(G));
				}

				BTSerial.print('d');
				BTSerial.write(precision(D));
			}
		}
	}
	else
	{
		int x = analogRead(A0);

		BTSerial.print('A');

		if (x > 511)
		{
			BTSerial.write(precision((x - 512) * 0.5));
		}
		else
		{
			BTSerial.write(precision(0));
		}
	}
}
