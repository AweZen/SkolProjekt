#pragma once
#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

class Enemie: public sf::Drawable
{

private:
	float mSpeed;
	bool dead;
public:
	Enemie();
	virtual ~Enemie() = 0;
	bool getDead()const;
	void setDead();
	int getSpeed();
	virtual bool Update(float dt) = 0;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;



};
