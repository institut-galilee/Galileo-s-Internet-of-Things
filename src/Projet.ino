template <byte Position, bool Sortie>
class digital
{
	void connecter() const noexcept
	{
		pinMode(Position, Sortie);
	}
	
	bool lire() const noexcept
	{
		return digitalRead(Position);
	}
	
	void ecrire(bool Valeur) noexcept
	{
		digitalWrite(Position, Valeur);
	}
	
	unsigned long impulser(bool Valeur) noexcept
	{
		return pulseIn(Position, Valeur);
	}
	
}

template <byte Position, bool Sortie>
class analogique : public digital <Position, Sortie>
{
	byte lire() const noexcept
	{
		return analogicRead(Position);
	}
	
	void ecrire(byte Valeur) noexcept
	{
		analogicWrite(Position, Valeur);
	}
}

template <byte Position>
class led : public digital <Position, OUTPUT>
{
	void allumer() noexcept
	{
		ecrire(HIGH);
	}
	
	void eteindre() noexcept
	{
		ecrire(LOW);
	}
	
	bool est_allume() const noexcept
	{
		return lire();
	}
}

template <byte Position>
class moteur : public analogic <Position, OUTPUT>
{
	void stop() noexcept
	{
		ecrire(LOW);
	}
}

template <byte Envoi, byte Reception, unsigned int Duree>
class capteur : public analogique <Envoi, OUTPUT>, public analogique <Reception, INPUT>
{
	static_assert(Duree != 0);
	
	void connecter() const noexcept
	{
		analogique <Envoi, OUTPUT>::connecter();
		ecrire(LOW);
		analogique <Reception, INPUT>::connecter();
	}
	
	unsigned long mesurer() noexcept
	{
		analogique <Envoi, OUTPUT>::ecrire(HIGH);
		delayMicroseconds(Duree);
		analogique <Envoi, OUTPUT>::ecrire(LOW);
		
		return (analogique <Reception, INPUT>::impulser(HIGH) * 340) / (2000 * Duree);
	}
}

