#pragma once
#include <string>
#include <iostream>

using namespace std;

class ShotHandler
{
private:
	ShotHandler * *Shots;
public:
	ShotHandler();
	virtual~ShotHandler();
	void Update(float dt);
	void addShot();
	void addRocket();

};
#pragma once
