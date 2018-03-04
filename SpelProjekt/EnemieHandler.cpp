#include "EnemieHandler.h"
#include "Alien.h"
#include "Ship.h"
#include <time.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>

int const EnemieHandler::spawns[6] = { 50,150,225,325,425,500 };
int const EnemieHandler::AmountOfSpawns = 6;


void EnemieHandler::initiate(int from)
{
	for (int i = from; i<AmountOfSpawns; i++)
	{
		this->enemies[i] = nullptr;
	}
}

int EnemieHandler::getHighscore()
{
	return this->highScore;
}

bool EnemieHandler::setHighscore(int score)
{
	bool newHighscore = false;
	if (score > this->highScore) {
		ofstream highScoreFile("highscore.txt");

		if (highScoreFile.is_open())
		{
			highScoreFile << score;
			this->highScore = score;
			newHighscore = true;
		}
		else cout << "Unable to open file";
		
	}
	return newHighscore;
}


EnemieHandler::EnemieHandler()
{
	ifstream highScoreFile("highscore.txt");
	if (highScoreFile.is_open())
	{
		highScoreFile >> this->highScore;
		cout << this->highScore;
		highScoreFile.close();
	}
	else cout << "Unable to open file";

	this->level = 2;
	this->nrOfEnemies = 0;
	this->nrOfDead = 0;
	this->enemies = new Enemie*[this->AmountOfSpawns];
	initiate();
	spawn();
	this->score = 0;
	this->gameOver = false;
	if (!font.loadFromFile("font.ttf")) {
		cout << "errorororororor" << endl;
	}
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::Yellow);
	this->text.setPosition(100, 100);
	this->text.setCharacterSize(50);
	this->text.setString("Score: " + to_string(score));

}

void EnemieHandler::draw(const EnemieHandler & origObj, sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text, states);
	for (int i = 0; i < nrOfEnemies; i++) {
		if (!enemies[i]->getDead())
		target.draw(*enemies[i], states);

	}

}

Enemie* EnemieHandler::getEnemies(int enemieNumber)
{
	return enemies[enemieNumber];
}

void EnemieHandler::setDead(int enemieNumber)
{
	this->enemies[enemieNumber]->setDead();
	this->nrOfDead++;
	if (this->nrOfDead == this->nrOfEnemies) {

		this->nrOfEnemies = 0;
		this->nrOfDead = 0;
		this->level++;
		if (this->level == this->AmountOfSpawns) {
			this ->level = 0;
		}
		spawn();
	}
}

int EnemieHandler::getNrOfEnemies() const
{
	return this->nrOfEnemies;
}

EnemieHandler::~EnemieHandler()
{
	for (int i = 0; i < nrOfEnemies; i++) {
		delete enemies[i];
	}
	delete[] enemies;
}

void EnemieHandler::Update(float dt)
{
	if (this->gameOver) {
		reset();
	}
	this->text.setString("Score: " + to_string(score));
	for (int i = 0; i < this->nrOfEnemies; i++) {
		if (!enemies[i]->getDead())
			if (enemies[i]->Update(dt)) {
				this->gameOver = true;
			}
			
	}
}

void EnemieHandler::setHealth(int enemieNumber, int health)
{
	Ship* shipPtr;
	shipPtr = dynamic_cast<Ship*>(enemies[enemieNumber]);
	shipPtr->setHealth(health);
	if (shipPtr->getHealth() == 0) {
		setDead(enemieNumber);
	}
	cout << shipPtr->getHealth() << endl;
	enemies[enemieNumber] = shipPtr;
}

void EnemieHandler::addAlien(int xValue)
{

	this->enemies[this->nrOfEnemies] = new Alien(xValue);

	this->nrOfEnemies++;
}

void EnemieHandler::addShip(int xValue)
{
	 
	this->enemies[this->nrOfEnemies] = new Ship(xValue); 

	this->nrOfEnemies++;

}

void EnemieHandler::spawn()
{
	for (int i = 0; i < this->AmountOfSpawns; i++) {
		delete enemies[i];
	}
	delete[] enemies;
	initiate();

	this->enemies = new Enemie*[this->AmountOfSpawns];

	int i;
	for (i = 0; i < this->level; i++) {
		addShip(spawns[i]);
	}
	for (i; i < this->AmountOfSpawns; i++) {
		addAlien(spawns[i]);
	}
}

void EnemieHandler::reset()
{
	setHighscore(score);
	this->level = 0;
	this->nrOfEnemies = 0;
	this->nrOfDead = 0;
	this->score = 0;
	this->gameOver = false;
	spawn();
}

void EnemieHandler::Collision(Player& user)
{
	int health;
	Ship* shipPtr;
	Alien* alienPtr;
	for (int i = 0; i < this->nrOfEnemies; i++) 
	{
		alienPtr = dynamic_cast<Alien*>(getEnemies(i));
		if (alienPtr != nullptr) 
		{
			Alien tempAlien(*alienPtr);
			if (!tempAlien.getDead()) {
				if (tempAlien.getGlobalBounds().intersects(user.getGlobalBounds())) {
					this->gameOver = true;
				}
				if (tempAlien.getGlobalBounds().intersects(user.getGlobalBoundsBullet())) {
					setDead(i);
					user.removeBullet();
					score += 10;
				}
				if (tempAlien.getGlobalBounds().intersects(user.getGlobalBoundsRocket())) {
					setDead(i);
					user.removeRocket();
					score += 10;
				}
			}
		}
		else 
		{
			shipPtr = dynamic_cast<Ship*>(getEnemies(i));
			if (shipPtr != nullptr) 
			{
				Ship tempShip(*shipPtr);
				if (!tempShip.getDead()) 
				{
					health = tempShip.getHealth();
					if (health == 1)
					{
						if (tempShip.getGlobalBounds().intersects(user.getGlobalBounds())) {
							this->gameOver = true;
						}
						if (tempShip.getGlobalBounds().intersects(user.getGlobalBoundsBullet()))
						{
							setDead(i);
							user.removeBullet();
							score += 100;
						}
						if (tempShip.getGlobalBounds().intersects(user.getGlobalBoundsRocket()))
						{
							setDead(i);
							user.removeRocket();
							score += 100;
						}
					}
					else
					{
						if (tempShip.getGlobalBounds().intersects(user.getGlobalBounds())) {
							this->gameOver = true;
						}
						if (tempShip.getGlobalBounds().intersects(user.getGlobalBoundsBullet()))
						{
							setHealth(i, health - 1);
							user.removeBullet();
						}
						if (tempShip.getGlobalBounds().intersects(user.getGlobalBoundsRocket()))
						{
							setDead(i);
							user.removeRocket();
							score += 100;
						}
					}
				}
				if (tempShip.IsShooting()) {
					if (tempShip.getGlobalBoundsBullet().intersects(user.getGlobalBounds())) {
						this->gameOver = true;
				}
				}

			}
		}
	}
}