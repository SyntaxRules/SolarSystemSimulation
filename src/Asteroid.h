#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid
{
private:
	double xPos;
	double yPos;
	double zPos;
	double radius;
	double sizeScaleFactor;
public:
	Asteroid(double x, double y, double z);
	void draw();
	void setSizeScaleFactor(double param) { sizeScaleFactor = param; };
};

#endif