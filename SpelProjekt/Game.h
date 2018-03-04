#pragma once
#include <string>
#include <iostream>
#include "EnemieHandler.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



using namespace std;

class Game : public sf::Drawable
{
public:
	Game();
	void Update(float dt);
	bool GetPause();
	void Pause();
	void Resume();
private:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	sf::Music music;
	sf::Font font;
	sf::Text pauseText;
	bool pause;
	int score;
	Player user;
	sf::Event event;
	EnemieHandler enemieHandler;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool gamePause;


};
#pragma once
#pragma once
#pragma once
