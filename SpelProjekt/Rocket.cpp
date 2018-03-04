#include "Rocket.h"

void Rocket::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSpriteSheet, states);
}

Rocket::Rocket()
	:Shot()
{
	if (mTexture.loadFromFile("spr_missile.png"))
	{
		// Handle error
	}
	mSpriteSheet.setTexture(mTexture);
	mSpriteSheet.setPosition(-100, -100);
	mSpriteSheet.rotate(-90);
	mSpriteSheet.scale(0.5, 0.5);
}

bool Rocket::Update(float dt, int way)
{
	bool outOfSpace = false;
	mSpriteSheet.move(0, getSpeed()*dt * way);

	if (mSpriteSheet.getPosition().y <= -70)
	{
		outOfSpace = true;
	}
	return outOfSpace;
}

void Rocket::Center(sf::Vector2f direction)
{
	mSpriteSheet.setPosition(direction);
	mSpriteSheet.move(28, 0);

}

sf::FloatRect Rocket::getGlobalBounds()
{
	return this->mSpriteSheet.getGlobalBounds();
}
