#include "Player.h"
#include "Rocket.h"
#include "Bullet.h"

Player::Player()
{
	// Just this line is needed if you remove int playerNumber from the argument list
	sf::String fileName = "spaceship.png";



	// Load texture, set it to the sprite and set what part of the sprite sheet to draw.
	if (mTexture.loadFromFile(fileName))
	{
		// Handle error
	}
	mSpriteSheet.setTexture(mTexture);
	mSpriteSheet.scale(0.2,0.2);
	mSpriteSheet.setPosition(300,535);
	
	// Initialise animation variables.
	this->shots = new Shot*[2];
	this->shots[0] = new Rocket();
	this->shots[1] = new Bullet();
	this->outOfMap.x = -100;
	this->outOfMap.y = -100;


}
Player::~Player()
{
	delete shots[0];
	delete shots[1];
	delete[] shots;
}

sf::FloatRect Player::getGlobalBoundsBullet()
{
	Bullet* tempBullet = dynamic_cast<Bullet*>(shots[1]);
	return tempBullet->getGlobalBounds();
}

sf::FloatRect Player::getGlobalBoundsRocket()
{

	Rocket* tempRocket = dynamic_cast<Rocket*>(shots[0]);
	return tempRocket->getGlobalBounds();
}

sf::FloatRect Player::getGlobalBounds()
{
	return mSpriteSheet.getGlobalBounds();
}

void Player::removeBullet()
{
	this->mIsShootingBullet = false;
	shots[1]->Center(outOfMap);
}

void Player::removeRocket()
{
	this-> mIsShootingRocket = false;
	shots[0]->Center(outOfMap);
}

void Player::Update(float dt)
{
	sf::Vector2f direction(0.0f, 0.0f);

	// Handle input from arrow keys and update direction and animation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if ( mSpriteSheet.getPosition().x > 0) {
			direction.x = -1.0f;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if ( mSpriteSheet.getPosition().x < 540) {
			direction.x = 1.0f;

		}

	}

	bool isArrowUpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	if (isArrowUpPressed && !mIsShootingBullet)
	{
		mIsShootingBullet = true;
		shots[1]->Center(mSpriteSheet.getPosition());
	}
	// Check to start jumping
	bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	if (isSpacePressed && !mIsShootingRocket)
	{
		mIsShootingRocket = true;
		shots[0]->Center(mSpriteSheet.getPosition());
	}

	// Update jump
	if (mIsShootingRocket)
	{
		if(shots[0]->Update(dt))
		{
			mIsShootingRocket = false;
		}
	}
	if (mIsShootingBullet)
	{
		if (shots[1]->Update(dt))
		{
			mIsShootingBullet = false;
		}
	}
	mSpriteSheet.move(direction * mSpeed * dt);
	// Update animation
}

bool Player::getShootingRocket() const
{
	return mIsShootingRocket;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(mSpriteSheet, states);
	if (mIsShootingRocket) {
		target.draw(*shots[0], states);
	}
	if (mIsShootingBullet) {
		target.draw(*shots[1], states);
	}
}