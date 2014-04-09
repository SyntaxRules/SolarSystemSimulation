#include "AsteroidBelt.h"
#include "Asteroid.h"
#include <list>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

AsteroidBelt::AsteroidBelt() {
	this->distanceFromSunToInside = 2.06;
	this->distanceFromSunToOutside = 3.27;
	this->eccentricity = 0.33; //about
	this->inclination = 0.34906585; // about
}

void AsteroidBelt::addAsteroid() {
	//establish a new random position within the bound set.
	double distanceFromSun = ((rand() % 10000) * .000112) + distanceFromSunToInside; //between 2.06 and 3.27 (1.12)
	double randAngle = ((rand() % 10000) * .000628318530718); //0 - 2*PI
	double modInclination = inclination + (rand() % 10000 * .00001);
	double longOfAsendingNode = ((rand() % 10000) * .000028318530718);
	double x = cos(randAngle) * distanceFromSun;
	double y = cos(randAngle + longOfAsendingNode) * sin(modInclination) * distanceFromSun;
	double z = sin(randAngle) * (distanceFromSun * sqrt(1.0 - pow(eccentricity, 1)));
	Asteroid a(x,y,z);
	asteroids.push_front(a);
}

void AsteroidBelt::draw() {
	glDisable(GL_TEXTURE_2D); //It is better to do this once :)
	for (std::list<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
	{
		it->draw();
	}
	glEnable(GL_TEXTURE_2D);
}

void AsteroidBelt::setSizeScaleFactor(double param) {
	for (std::list<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
	{
		it->setSizeScaleFactor(param);
	}
}
