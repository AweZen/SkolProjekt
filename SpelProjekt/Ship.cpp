#include "Ship.h"
#include <SFML/Graphics.hpp>

void Ship::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSpriteSheet, states);
	if (this->IsShootingBullet) {
		target.draw(shots,states);
	}

}

Ship::Ship(int xPos)
{
	sf::String fileName = "alienshiptex.png";


	if (mTexture.loadFromFile(fileName))
	{
	}
	mSpriteSheet.setTexture(mTexture);
	mSpriteSheet.scale(0.1, 0.1);
	mSpriteSheet.setRotation(-90);
	mSpriteSheet.setPosition(xPos, 0);
	this->outOfSpace = false;
	this->IsShootingBullet = false;
}

int Ship::getHealth()const
{
	return this->health;
}

void Ship::setHealth(int health) 
{
	this->health = health;
}

Ship::~Ship()
{
}

bool Ship::Update(float dt)
{
	int random  = rand() % 400+ mSpriteSheet.getPosition().y;
	bool outOfSpace = false;
	mSpriteSheet.move(0, getSpeed()*dt * 1);
	if (mSpriteSheet.getPosition().y >= 600) {
		outOfSpace = true;
	}
	if (mSpriteSheet.getPosition().y >= random && !this->IsShootingBullet) {
		this->IsShootingBullet = true;
		shots.Center(mSpriteSheet.getPosition());
	}
	if (this->IsShootingBullet) {
		shots.Update(dt, -1);
	}
	if (shots.getPosition().y >= 700){
		this->IsShootingBullet = false;
	}
	return outOfSpace;
}
sf::FloatRect Ship::getGlobalBounds()
{
	return this->mSpriteSheet.getGlobalBounds();
}

sf::FloatRect Ship::getGlobalBoundsBullet()
{
	return shots.getGlobalBounds();
}

bool Ship::IsShooting()
{
	return this->IsShootingBullet;
}

