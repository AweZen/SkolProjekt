#pragma once
#include <string>
#include <iostream>
#include "Enemie.h"
#include "bullet.h"
#include "Rocket.h"

using namespace std;

class Ship : public Enemie
{
private:
	sf::Texture mTexture;
	sf::Sprite mSpriteSheet;
	int health = 10;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool outOfSpace;
	Bullet shots;
	bool IsShootingBullet;
public:
	Ship(int xPos);
	virtual~Ship();
	int getHealth()const;
	void setHealth(int health);
	bool Update(float dt);
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getGlobalBoundsBullet();
	bool IsShooting();
};
#pragma once
#pragma once
#pragma once
