#pragma once
#include <string>
#include <iostream>
#include "Enemie.h"
#include "Player.h"
using namespace std;

class EnemieHandler
{

private:
	static const int spawns[];
	static const int AmountOfSpawns;
	sf::Font font;
	sf::Text text;
	int score;
	Enemie * *enemies;
	int nrOfEnemies;
	void initiate(int from = 0);
	int nrOfDead;
	int level;
	bool gameOver;
	int highScore;
public:
	EnemieHandler();
	virtual~EnemieHandler();
	void draw(const EnemieHandler & origObj, sf::RenderTarget & target, sf::RenderStates states)const;
	Enemie* getEnemies(int enemieNumber);
	void setDead(int enemieNumber);
	int getNrOfEnemies()const;
	void Update(float dt);
	void setHealth(int enemieNumber, int health);
	void addAlien(int xValue);
	void addShip(int xValue);
	void spawn();
	void reset();
	void Collision(Player& user);
	int getHighscore();
	bool setHighscore(int score);
};
