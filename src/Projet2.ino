template <byte Position, bool Sortie>
struct digital
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
	
};

template <byte Position, bool Sortie>
struct analogique : public digital <Position, Sortie>
{
	byte lire() const noexcept
	{
		return analogRead(Position);
	}
	
	void ecrire(byte Valeur) noexcept
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

template <byte Envoi, byte Reception, unsigned int Duree>
struct capteur : public analogique <Envoi, OUTPUT>, public analogique <Reception, INPUT>
{
	static_assert(Duree != 0);
	
	void connecter() const noexcept
	{
		analogique <Envoi, OUTPUT>::connecter();
		analogique <Envoi, OUTPUT>::ecrire(LOW);
		analogique <Reception, INPUT>::connecter();
	}
	
	unsigned long mesurer() noexcept
	{
		analogique <Envoi, OUTPUT>::ecrire(HIGH);
		delayMicroseconds(Duree);
		analogique <Envoi, OUTPUT>::ecrire(LOW);
		
		return (analogique <Reception, INPUT>::impulser(HIGH) * 340) / (2000 * Duree);
	}
};

template <byte ActiverGauche, byte ActiverDroite, byte AvancerGauche, byte AvancerDroite, byte ReculerGauche, byte ReculerDroite>
struct moteurs : public digital <ActiverGauche, OUTPUT>, public digital <ActiverDroite, OUTPUT>, public digital <AvancerGauche, OUTPUT>, public digital <AvancerDroite, OUTPUT>, public digital <ReculerGauche, OUTPUT>, public digital <ReculerDroite, OUTPUT>
{
  void connecter() noexcept
  {
    digital <ActiverGauche, OUTPUT>::connecter();
    digital <ActiverDroite, OUTPUT>::connecter();

    digital <ActiverGauche, OUTPUT>::ecrire(HIGH);
    digital <ActiverDroite, OUTPUT>::ecrire(HIGH);
    
    digital <AvancerGauche, OUTPUT>::connecter();
    digital <AvancerDroite, OUTPUT>::connecter();
    digital <ReculerGauche, OUTPUT>::connecter();
    digital <ReculerDroite, OUTPUT>::connecter();
  }
  
  void avancer() noexcept
  {
    digital <AvancerGauche, OUTPUT>::ecrire(HIGH);
    digital <AvancerDroite, OUTPUT>::ecrire(HIGH);
    digital <ReculerGauche, OUTPUT>::ecrire(LOW);
    digital <ReculerDroite, OUTPUT>::ecrire(LOW);
  }

  void reculer() noexcept
  {
    digital <AvancerGauche, OUTPUT>::ecrire(LOW);
    digital <AvancerDroite, OUTPUT>::ecrire(LOW);
    digital <ReculerGauche, OUTPUT>::ecrire(HIGH);
    digital <ReculerDroite, OUTPUT>::ecrire(HIGH);
  }

  void tourner_gauche() noexcept
  {
    digital <AvancerGauche, OUTPUT>::ecrire(LOW);
    digital <AvancerDroite, OUTPUT>::ecrire(HIGH);
    digital <ReculerGauche, OUTPUT>::ecrire(LOW);
    digital <ReculerDroite, OUTPUT>::ecrire(LOW);
  }

  void tourner_droite() noexcept
  {
    digital <AvancerGauche, OUTPUT>::ecrire(HIGH);
    digital <AvancerDroite, OUTPUT>::ecrire(LOW);
    digital <ReculerGauche, OUTPUT>::ecrire(LOW);
    digital <ReculerDroite, OUTPUT>::ecrire(LOW);
  }

  void arreter() noexcept
  {
    digital <AvancerGauche, OUTPUT>::ecrire(LOW);
    digital <AvancerDroite, OUTPUT>::ecrire(LOW);
    digital <ReculerGauche, OUTPUT>::ecrire(LOW);
    digital <ReculerDroite, OUTPUT>::ecrire(LOW);
  }
};

template <byte Activer, byte Avancer, byte Reculer>
struct moteur : public digital <Activer, OUTPUT>, public digital <Avancer, OUTPUT>, public digital <Reculer, OUTPUT>
{
  void connecter() noexcept
  {
    digital <Activer, OUTPUT>::connecter();

    digital <Activer, OUTPUT>::ecrire(HIGH);

    digital <Avancer, OUTPUT>::connecter();
    digital <Reculer, OUTPUT>::connecter();
  }
  
  void arreter() noexcept
  {
    digital <Avancer, OUTPUT>::ecrire(LOW);
    digital <Reculer, OUTPUT>::ecrire(LOW);
  }
  
  void avancer() noexcept
  {
    digital <Avancer, OUTPUT>::ecrire(HIGH);
    digital <Reculer, OUTPUT>::ecrire(LOW);
  }
  
  void reculer() noexcept
  {
    digital <Avancer, OUTPUT>::ecrire(LOW);
    digital <Reculer, OUTPUT>::ecrire(HIGH);
  }
};

moteurs <6, 11, 4, 8, 3, 9> Moteurs;

void setup()
{
  Moteurs.connecter();
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
}

bool Marche = false;

void loop()
{
  if (!digitalRead(2))
  {
    Marche = !Marche;
  }

  if (Marche)
  {
    if (analogRead(A0) < 256)
    {
      Moteurs.reculer();
    }
    else
    {
      if (analogRead(A0) > 768)
      {
        Moteurs.avancer();
      }
      else
      {
        if (analogRead(A1) > 768)
        {
          Moteurs.tourner_droite();
        }
        
        if (analogRead(A1) < 256)
        {
          Moteurs.tourner_gauche();
        }
      }
    }
  }
  else
  {
    Moteurs.arreter();
  }
}
