template <byte Position, byte Sortie>
struct digital
{
	void connecter() const noexcept
	{
		pinMode(Position, Sortie);
	}
	
	bool lire() const noexcept
	{
		return static_cast <bool> (digitalRead(Position));
	}
	
	void ecrire(bool Valeur) noexcept
	{
		digitalWrite(Position, static_cast <byte> (Valeur));
	}
	
	unsigned long impulser(byte Valeur) noexcept
	{
		return pulseIn(Position, Valeur);
	}
	
	unsigned long impulser(byte Valeur, unsigned long Duree) noexcept
	{
		return pulseIn(Position, Valeur, Duree);
	}
	
};

template <byte Position, bool Sortie>
struct analogique : public digital <Position, Sortie>
{
	int lire() const noexcept
	{
		return analogRead(Position);
	}
	
	void ecrire(int Valeur) noexcept
	{
		analogWrite(Position, Valeur);
	}
};

template <byte Position>
struct led : public digital <Position, OUTPUT>
{
	void allumer() noexcept
	{
		digital <Position, OUTPUT>::ecrire(HIGH);
	}
	
	void eteindre() noexcept
	{
		digital <Position, OUTPUT>::ecrire(LOW);
	}
};

template <byte X, byte Y, byte Appui>
struct joystick : public analogique <X, INPUT>, public analogique <Y, INPUT>, public digital <Appui, INPUT_PULLUP>
{
	void connecter() const noexcept
	{
		digital <Appui, INPUT_PULLUP>::connecter();
	}
	
	int x() const noexcept
	{
		analogique <X, INPUT>::lire();
	}
	
	int y() const noexcept
	{
		analogique <Y, INPUT>::lire();
	}
	
	bool est_appuye() const noexcept
	{
		return !(static_cast <bool> (digital <Appui, INPUT_PULLUP>::lire()));
	}
};

template <byte Position>
struct photoresistance : public analogique <Position, INPUT>
{
	void connecter() const noexcept
	{
		analogique <Position, INPUT>::connecter();
	}
	
	int luminosite() const noexcept
	{
		return analogique <Position, INPUT>::lire();
	}
};

template <byte Envoi, byte Reception, unsigned int Duree>
struct capteur : public digital <Envoi, OUTPUT>, public analogique <Reception, INPUT>
{
	//static_assert(Duree != 0);
	
	void connecter() const noexcept
	{
		digital <Envoi, OUTPUT>::connecter();
		digital <Envoi, OUTPUT>::ecrire(LOW);
		analogique <Reception, INPUT>::connecter();
	}
	
	unsigned long mesurer() noexcept
	{
		digital <Envoi, OUTPUT>::ecrire(HIGH);
		delayMicroseconds(Duree);
		digital <Envoi, OUTPUT>::ecrire(LOW);
		
		return (analogique <Reception, INPUT>::impulser(HIGH) * 340) / (2000 * Duree);
	}
};

template <byte Avancer, byte Reculer>
struct moteur : public analogique <Avancer, OUTPUT>, public analogique <Reculer, OUTPUT>
{
	void connecter() noexcept
	{
		analogique <Avancer, OUTPUT>::connecter();
		analogique <Reculer, OUTPUT>::connecter();
	}
	
	void arreter() noexcept
	{
		analogique <Avancer, OUTPUT>::ecrire(LOW);
		analogique <Reculer, OUTPUT>::ecrire(LOW);
	}
	
	void avancer(byte Vitesse) noexcept
	{
		if (Vitesse >= 0 && Vitesse < 256)
		{
			analogique <Avancer, OUTPUT>::ecrire(Vitesse);
			analogique <Reculer, OUTPUT>::ecrire(LOW);
		}
		else
		{
			//throw 0;
		}
	}
	
	void reculer(byte Vitesse) noexcept
	{
		if (Vitesse >= 0 && Vitesse < 256)
		{
			analogique <Avancer, OUTPUT>::ecrire(LOW);
			analogique <Reculer, OUTPUT>::ecrire(Vitesse);
		}
		else
		{
			//throw 1;
		}
	}
};
