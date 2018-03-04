#pragma once
#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Shot.h"
#include "Player.h"
using namespace std;

class Rocket : public Shot, public sf::Drawable 
{
private:
	sf::Texture mTexture;
	sf::Sprite mSpriteSheet;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Rocket();
	bool Update(float dt, int way = 1);
	void Center(sf::Vector2f direction);
	sf::FloatRect getGlobalBounds();


};
#pragma once
#pragma once
