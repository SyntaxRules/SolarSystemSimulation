#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <vector>
#include "Planet.h"
#include "AsteroidBelt.h"
#include "ImportedOBJ.h"

#ifndef NUM_PLANETS
#define NUM_PLANETS 10
#endif

class SolarSystem {
private:
	void init();
	void loadStarBackgroundTexture();

	std::vector<Planet> planets;
	//std::vector<Planet> asteroids;

	AsteroidBelt asteroidBelt;
	ImportedOBJ * deathStar;
	ImportedOBJ * vaderTieFighter;

	int planetSelected;
	unsigned int starBackgroundTexture;
public:
	SolarSystem();
	void draw();

	Planet * getSelectedPlanet() { return &planets[planetSelected]; }

	void setPlanetSelected(int param) { this->planetSelected = param; };

	double getSizeScaleFactor() { return planets[0].getSizeScaleFactor(); };
	
	void incSizeScaleFactor();
	void decSizeScaleFactor();

	void incSimSpeed();
	void decSimSpeed();
	double getSimSpeed() { return planets[0].getSpeed(); };
	void blowUpPlanet(int planetNum);
	void regeneratePlanets(); // what?!?! planets can't do this!
	void toggleOrbitalGuidelines();
};

#endif