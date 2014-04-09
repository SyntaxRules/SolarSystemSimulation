#ifndef PLANET_H
#define PLANET_H

#include <cmath>
#include <list>

class Planet {
protected:
	char * name;

	double distanceFromSun; //from planets center to sun center (semimajor axis)
	double semiMinorAxis;
	double radius; //radius of planet
	double orbitalPeriod; //in earth days
	double rotationPeriod; //days
	double eccentricity;
	double inclination; // in RAD, inclination to the suns equator
	double lonOfAscendingNode; //in rad, the location where the orbit  crosess the x-z plane
	double axialTilt; //In degrees, also called Obliquity

	bool hasRing;
	double ringWidth; //The measure (in AU) from the outside edge of the ring to the inside edge
	double ringInnerEdge; //The measure (in AU) from the center of the planet to the inner ring edge

	double rotationAngle; //in Degrees!
	double rotationAngleIncrement; //in Degrees
	double posAngle; //The angle the planet resides on
	double posAngleInc; // The amount the angle increments every adance() call;

	std::list<Planet> moons; //array of moons...

	bool isMoon;

	double sizeScaleFactor;
	double orbitScaleFactor;
	double speed;

	float * color;
	unsigned int planetTexture;
	unsigned int ringTexture;

	bool xyzGuidelines; //display a line going thourgh the plannet in the x, y and z directions
	float guildlinesLength;
	bool orbitalGuidelines; //display the path the planet will take.

	bool blowingUp;
	int framesSinceBlowUp;
	float blowUpPos[3];
	bool destroyed;
	
	void drawOrbitalGuidelines();
	void drawxyzGuidelines();
	void loadPlanetTexture(const char * filename);
	void loadRingTexture(const char * filename);
	void drawsphere();
	void drawRing();

	void drawCube(double r = .5);
	void drawExplodingCube();
public:
	Planet();
	void recalculateDerivedValues();
	void advance();
	void draw();

	//Setters
	void setPlanetTexture(const char * filename) { loadPlanetTexture(filename); };
	void setxyzGuidelines(bool param) { xyzGuidelines = param; };
	void setGuildlinesLength(float param) { guildlinesLength = param; };
	void setOrbitalGuidelines(bool param);
	void setColor(float red, float green, float blue);

	void setName(char * param) { this->name = param; };
	void setDistanceFromSun(double param) { this->distanceFromSun = param; };
	void setRadius(double param) { this->radius = param; };
	void setOrbitalPeriod(double param) { this->orbitalPeriod = param; };
	//rotSpeed
	void setRotationPeriod(double param) { this->rotationPeriod = param; };
	void setEccentricity(double param) { this->eccentricity = param; };
	void setInclination(double param) { this->inclination = param; };
	void setLonOfAcsendingNode(double param) { this->lonOfAscendingNode = param; };
	void setAxialTilt(double param) { this->axialTilt = param; };

	void setRing(double ringWidth, double ringInnerEdge);
	void setRingTexture(const char * filename) { loadRingTexture(filename); };

	void setMoons(std::list<Planet> pMoons) { moons = pMoons; };
	void setIsMoon(bool param) { isMoon = param; };

	char * getDisplayText();

	double getSizeScaleFactor() { return this->sizeScaleFactor; };
	void setSizeScaleFactor(double param);
	double getOrbitScaleFactor() { return this->orbitScaleFactor; };
	void setOrbitScaleFactor(double param) { this->orbitScaleFactor = param; };
	double getSpeed() { return this->speed; };
	void setSpeed(double param);
	
	//wouldn't it be awesome to have these abilities in real life?
	void blowUpPlanet();
	void regeneratePlanet() { blowingUp = false; destroyed = false; framesSinceBlowUp = 0; };

	//Getters
	double getX();
	double getY();
	double getZ();

	double getRadius() { return radius; };
	bool orbitalGuidelinesOn() { return orbitalGuidelines; };
};

#endif //PLANET_H