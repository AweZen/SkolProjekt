#include "Enemie.h"
Enemie::Enemie()
{
	this->mSpeed = 70.f;
	this->dead = false;
}

Enemie::~Enemie()
{
}

bool Enemie::getDead()const
{
	return this->dead;
}

void Enemie::setDead()
{
	this->dead = true;
}


int Enemie::getSpeed()
{
	return mSpeed;
}
