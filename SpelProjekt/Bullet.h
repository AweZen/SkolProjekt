#pragma once
#include <string>
#include <iostream>
#include "Shot.h"
#include <SFML\Graphics.hpp>

using namespace std;

class Bullet : public Shot
{
private:
	sf::Texture mTexture;
	sf::Sprite mSpriteSheet;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Bullet();
	virtual~Bullet();
	bool Update(float dt, int bullet = 1);
	void Center(sf::Vector2f direction);
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();

};
#pragma once
#pragma once
