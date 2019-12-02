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
//    digital <AvancerGauche, OUTPUT>::ecrire(HIGH);
//    digital <AvancerDroite, OUTPUT>::ecrire(HIGH);
//    digital <ReculerGauche, OUTPUT>::ecrire(LOW);
//    digital <ReculerDroite, OUTPUT>::ecrire(LOW);


    analogWrite(AvancerGauche, 100);
    analogWrite(AvancerDroite, 100);
    analogWrite(ReculerGauche, 0);
    analogWrite(ReculerDroite, 0);
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
    analogique <Avancer, OUTPUT>::ecrire(Vitesse);
    analogique <Reculer, OUTPUT>::ecrire(LOW);
  }
  
  void reculer(byte Vitesse) noexcept
  {
    analogique <Avancer, OUTPUT>::ecrire(LOW);
    analogique <Reculer, OUTPUT>::ecrire(Vitesse);
  }
};

//moteurs <11, 12, 9, 3, 10, 5> Moteurs;

moteur <3, 5> Gauche;
moteur <9, 10> Droite;

bool Marche;

//bool ActiverGauche;
//bool ActiverDroite;

void setup()
{
  Gauche.connecter();
  Droite.connecter();

  //ActiverGauche = false;
  //ActiverDroite = false;

  
  Marche = false;
//  Moteurs.connecter();
  Serial.begin(9600);

  //pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  
}




void loop()
{
  if (!digitalRead(2))
  {
    Marche = !Marche;
  }

  if (Marche)
  {
    int x = analogRead(A0), y = analogRead(A1);
    byte G, D;

    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);

    
    if (x > 511)
    {
      if (y > 511)
      {
        if (x > y)  // X > Y
        {
          G = (x - 512) * 0.5;
          D = (x - y) * 0.5;

          Droite.avancer(D);
        }
        else
        {
          G = (y - 512  ) * 0.5;
          D = (y - x) * 0.5;

          Droite.reculer(D);
        }
        
        Gauche.avancer(G);
      }
      else
      {
        G = (x + y - 511) * 0.5; ////////////////////////////////////////////////////////////
        
        if (x + y >= 1023) // X > Y
        {
          D = (x - 512) * 0.5;

          Gauche.avancer(G);
        }
        else
        {
          D = (511 - y) * 0.5;

          Gauche.reculer(G);
        }
        
        Droite.avancer(D);
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
          
          Droite.reculer(D);
        }
        else
        {
          G = (y - 512) * 0.5;
          D = (x + y) * 0.5;
          
          Droite.avancer(D);
        }
        
        Gauche.reculer(G);
      }
      else
      {
        if (x > y) // X > Y
        {
          D = (511 - y) * 0.5;
          G = (x - y) * 0.5;
          
          Gauche.avancer(G);
        }
        else
        {
          D = (511 - x) * 0.5;
          G = (y - x) * 0.5;

          Gauche.reculer(G);
        }
        
        Droite.reculer(D);
      }
    }
  }
  else
  {
    Gauche.arreter();
    Droite.arreter();
    delay(500);
  }
  
}
