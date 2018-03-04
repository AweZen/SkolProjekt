#include "Game.h"
#include "Enemie.h"
#include "shot.h"
#include "Alien.h"
#include "Ship.h"


Game::Game() :user()
{
	int CAP = 3;
	backgroundTexture.loadFromFile("space.png");
	backgroundSprite.setTexture(backgroundTexture);
	if (!music.openFromFile("music.ogg")) {

	}
	music.play();
	this->pause = false;
	int highScore = enemieHandler.getHighscore();
	if (!font.loadFromFile("font.ttf")) {
		cout << "errorororororor" << endl;
	}
	this->pauseText.setFont(font);
	this->pauseText.setFillColor(sf::Color::Yellow);
	this->pauseText.setPosition(150, 300);
	this->pauseText.setCharacterSize(50);
	this->pauseText.setString("Highscore: " + to_string(enemieHandler.getHighscore())+ "\nPress ESC to resume.");
}
void Game::Update(float dt)
{
	this->pauseText.setString("Highscore: " + to_string(enemieHandler.getHighscore()) + "\nPress ESC to resume.\nPress F1 to exit.");

	if (!this->pause) {
		user.Update(dt);
		enemieHandler.Collision(user);
		enemieHandler.Update(dt);
	}
}

bool Game::GetPause()
{
	return this->pause;
}

void Game::Pause()
{
	this->pause = true;
}

void Game::Resume()
{
	this->pause = false;
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	target.draw(backgroundSprite, states);
	target.draw(user, states);
	enemieHandler.draw(enemieHandler, target, states);
	if (this->pause) {
		target.draw(pauseText, states);
	}
}