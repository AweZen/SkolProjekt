#include "Shot.h"

Shot::Shot()
{
	mSpeed = -400.0f;

}

Shot::~Shot()
{
}

float Shot::getSpeed()
{
	return mSpeed;
}
