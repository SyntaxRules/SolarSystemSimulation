#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

#include <list>
#include "Asteroid.h"

class AsteroidBelt
{
private:
	double distanceFromSunToInside;
	double distanceFromSunToOutside;
	double eccentricity;
	double inclination;
	std::list<Asteroid> asteroids;
public:
	AsteroidBelt();
	void addAsteroid();
	void draw();
	void setSizeScaleFactor(double param);
};

#endif