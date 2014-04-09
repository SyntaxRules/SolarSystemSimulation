#include "Star.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void Star::draw()
{
	glDisable(GL_LIGHTING); //The light source is in the sun, so the sun needs to shine on its own!
	Planet::draw();
	glEnable(GL_LIGHTING);
}

char * Star::getDisplayText() {
	char * displayText = new char[512];
	sprintf_s(displayText, 512, "%s~ Distance from Sun: %f AU~ Radius: %f AU~ Orbital Period: %f days~ Rotation Period: %f days~ Eccentricity: %f rad~ Inclination: %f rad~ Long. of ascending node: %f rad~ Axial Tilt: %f degrees~",
		name,
		distanceFromSun,
		radius,
		orbitalPeriod,
		rotationPeriod,
		eccentricity,
		inclination,
		lonOfAscendingNode,
		axialTilt);
	return displayText;
}