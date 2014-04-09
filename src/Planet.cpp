/***************************************************************************
* Source code By SyntaxRules ( syntaxrulesdevelopment@gmail.com )
****************************************************************************/

#include <cmath>
#include <fstream>
#include <list>
#include "Planet.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef PI
#define PI 3.1415926535897932384626433832795028841971693993751058209
#endif

#define DEATH_STAR_LAZER_TIME 100

void Planet::loadPlanetTexture(const char * filename)
{
	int width, height;
	unsigned char * data;
	FILE * file;

	fopen_s(&file, filename, "rb");

	if (file == NULL) return;
	width = 1000;
	height = 500;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}

	glGenTextures(1, &planetTexture);
	glBindTexture(GL_TEXTURE_2D, planetTexture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
}

void Planet::loadRingTexture(const char * filename)
{
	int width, height;
	unsigned char * data;
	FILE * file;

	fopen_s(&file, filename, "rb");

	if (file == NULL) return;
	width = 1024;
	height = 72;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}
	glGenTextures(1, &ringTexture);
	glBindTexture(GL_TEXTURE_2D, ringTexture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
}

void Planet::drawOrbitalGuidelines() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f); //white are the lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //draw a wireframe
	glBegin(GL_POLYGON);
	double x = distanceFromSun * orbitScaleFactor;
	double y = sin(inclination) * distanceFromSun * orbitScaleFactor;
	double z = semiMinorAxis * orbitScaleFactor;
	if (isMoon) {
		x = distanceFromSun * sizeScaleFactor * orbitScaleFactor / 5.0;
		y = sin(inclination) * distanceFromSun * sizeScaleFactor * orbitScaleFactor / 5.0;
		z = semiMinorAxis * sizeScaleFactor * orbitScaleFactor / 5.0;
	}
	for (double i = 0; i < 2.0 * PI; i += PI / 32.0) {
		glVertex3f(cos(i) * x, cos(i + lonOfAscendingNode) * y, sin(i) * z);
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void Planet::drawxyzGuidelines() {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f); //white are the lines
	glBegin(GL_LINES);
	glVertex3d(0.0f, guildlinesLength, 0.0f);
	glVertex3d(0.0f, -1.0* guildlinesLength, 0.0f);
	glVertex3d(guildlinesLength, 0.0f, 0.0f);
	glVertex3d(-1.0* guildlinesLength, 0.0f, 0.0f);
	glVertex3d(0.0f, 0.0f, guildlinesLength);
	glVertex3d(0.0f, 0.0f, -1.0* guildlinesLength);
	glEnd();
	glEnable(GL_LIGHTING);
}

Planet::Planet(){
	this->distanceFromSun = 1;
	this->semiMinorAxis = 0; //derrived value
	this->radius = 1; //radius of planet
	this->orbitalPeriod = 365.26; //in earth days
	this->rotationPeriod = 0.0; //in earth days
	this->eccentricity = 0.0;
	this->inclination = 0.0;
	this->lonOfAscendingNode = 0.0;
	this->axialTilt = 0.0;

	this->hasRing = false;
	this->ringWidth = 0.0; //The measure (in AU) from the outside edge of the ring to the inside edge
	this->ringInnerEdge = 0.0;

	this->rotationAngle = 0; //in degrees
	this->rotationAngleIncrement = 1.5; //in degrees
	this->posAngle = (rand() % 618) / 100.0;
	this->posAngleInc = .1; //derrived value
	
	this->isMoon = false;

	this->sizeScaleFactor = 1001;
	this->orbitScaleFactor = 1;
	this->speed = 0.31;

	color = new float[3];
	//default color to blue
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 1.0f;
	planetTexture = 0;
	ringTexture = 0;

	orbitalGuidelines = true;
	xyzGuidelines = false;
	guildlinesLength = 200.0f;

	blowingUp = false;
	framesSinceBlowUp = 0;
	destroyed = false;
}

void Planet::recalculateDerivedValues() {
	semiMinorAxis = (distanceFromSun * sqrt(1.0 - pow(eccentricity, 1)));
	posAngleInc = (2.0*PI / this->orbitalPeriod) * speed;
	if (rotationPeriod != 0.0) {
		rotationAngleIncrement = (360 / rotationPeriod) * speed; //rotation angle is in degrees
	}
	else {
		rotationAngleIncrement = 0.0;
	}
	for (std::list<Planet>::iterator it = moons.begin(); it != moons.end(); ++it)
	{
		it->recalculateDerivedValues();
	}
}

void Planet::advance() {
	posAngle += posAngleInc;
	rotationAngle += rotationAngleIncrement;

	for (std::list<Planet>::iterator it = moons.begin(); it != moons.end(); ++it)
	{
		it->advance();
	}
}

void Planet::drawsphere() {
	double r = radius * sizeScaleFactor;
	double deltaY = .15;
	double theta = 0.0;
	double textureX = 1.0;
	double textureY = 1.0;
	double bottomToTopStrips = 16.0;
	double circChunks = 32.0;

	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindTexture(GL_TEXTURE_2D, planetTexture);
	glRotatef(axialTilt, 1.0f, 1.0f, 1.0f);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	for (double thetaY = 0.0; thetaY < PI; thetaY += PI / bottomToTopStrips) {
		textureX = 1.0;
		for (theta = -PI; theta < PI; theta += PI / (circChunks / 2.0)) {
			glTexCoord2d(textureX, textureY); 
			glNormal3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
			glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY));
			
			glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips)); 
			glNormal3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
			glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
			textureX -= 1.0 / circChunks;
		}
		glTexCoord2d(textureX, textureY); 
		glNormal3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
		glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left

		glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips)); 
		glNormal3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
		glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left

		textureY -= 1.0 / bottomToTopStrips;
	}
	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();

}

void Planet::drawRing() {
	double theta = 0.0;
	double textureY = 0.0;
	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindTexture(GL_TEXTURE_2D, ringTexture);
	glRotatef(axialTilt, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	//set the ringInnerEdge and RingWidth according to our scale factors.
	double rie = ringInnerEdge * sizeScaleFactor; 
	double rw = ringWidth * sizeScaleFactor;
	for (theta = -PI; theta < PI; theta += PI / 32.0) {
		glTexCoord2d(0.0, textureY);
		glNormal3d(rie * cos(theta), 0, rie * sin(theta));
		glVertex3d(rie * cos(theta), 0, rie * sin(theta));
		glTexCoord2d(1.0, textureY);
		glNormal3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
		glVertex3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
		textureY += 1.0 / 32.0;
	}
	glTexCoord2d(0.0, 1.0);
	glNormal3d(rie * cos(theta), 0, rie * sin(theta));
	glVertex3d(rie * cos(theta), 0, rie * sin(theta));
	glTexCoord2d(0.0, 1.0);
	glNormal3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
	glVertex3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
}

void Planet::draw() {
	if (orbitalGuidelines) {
		drawOrbitalGuidelines();
	}

	float x = getX();
	float z = getZ();
	float y = getY();
	// Draw Body

	if (blowingUp) {
		//oh dear... The death star has shot us....

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		if (framesSinceBlowUp < DEATH_STAR_LAZER_TIME) //Lazer warm up shot....
		{
			glColor3ub(155, 232, 104);
			float modifier = framesSinceBlowUp % 2 == 0 ? .005 : -.005;
			glBegin(GL_QUAD_STRIP);
			glVertex3f(-1.75, .9 + modifier, -1.40);
			glVertex3f(-1.75, 1.15 + modifier, -1.40);

			glVertex3f(x, y - 0.15, z);
			glVertex3f(x, y + 0.15, z);

			glVertex3f(-1.80, 1.0, -1.40);
			glVertex3f(-1.60, 1.0, -1.40);

			glVertex3f(x - 0.15 + modifier, y, z);
			glVertex3f(x + 0.15 + modifier, y, z);
			glEnd();
		}
		else if (framesSinceBlowUp == 100)
		{
			blowUpPos[0] = x;
			blowUpPos[1] = y;
			blowUpPos[2] = z;
		}
		else
		{
			glColor3ub(255.0, 204.0, 102.0);
			destroyed = true;
			glTranslatef(blowUpPos[0], blowUpPos[1], blowUpPos[2]);
			drawExplodingCube();
			if (framesSinceBlowUp > 400) { //we dont want to blow up forever....
				destroyed = true;
				blowingUp = false;
			}
			glTranslatef(-blowUpPos[0], -blowUpPos[1], -blowUpPos[2]);
		}
		framesSinceBlowUp++;
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
	}
	if (!destroyed) {
		glTranslatef(x, y, z);

		glColor4f(color[0], color[1], color[2], 1.0);
		drawsphere();

		if (hasRing) {
			drawRing();
		}
		glTranslatef(-x, -y, -z);
	}

	glTranslatef(x, y, z);
	if (xyzGuidelines) {
		drawxyzGuidelines();
	}
	for (std::list<Planet>::iterator it = moons.begin(); it != moons.end(); ++it)
	{
		it->draw();
	}
	glTranslatef(-x, -y, -z);
}

double Planet::getX() {
	if (isMoon) {
		return cos(posAngle) * distanceFromSun * orbitScaleFactor * sizeScaleFactor / 5.0;
	}
	return cos(posAngle) * distanceFromSun * orbitScaleFactor;
}

double Planet::getY() {
	if (isMoon) {
		return  cos(posAngle + lonOfAscendingNode) * sin(inclination) * distanceFromSun * sizeScaleFactor * orbitScaleFactor / 5.0;
	}
	return cos(posAngle + lonOfAscendingNode) * sin(inclination) * distanceFromSun * orbitScaleFactor;
}

double Planet::getZ() {
	if (isMoon) {
		return sin(posAngle) * semiMinorAxis * orbitScaleFactor * sizeScaleFactor / 5.0;
	}
	return sin(posAngle) * semiMinorAxis * orbitScaleFactor;
}

void Planet::setColor(float red, float green, float blue) {
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}

void Planet::setRing(double ringWidth, double ringInnerEdge) {
	this->hasRing = true;
	this->ringWidth = ringWidth;
	this->ringInnerEdge = ringInnerEdge;
}

void Planet::setSpeed(double param) {
	this->speed = param;
	for (std::list<Planet>::iterator it = moons.begin(); it != moons.end(); ++it)
	{
		it->setSpeed(this->speed);
	}
	recalculateDerivedValues();
}

void Planet::setSizeScaleFactor(double param) {
	if (param == 0.0) param = 1.0;
	this->sizeScaleFactor = param;

	for (std::list<Planet>::iterator it = moons.begin(); it != moons.end(); ++it)
	{
		it->setSizeScaleFactor(this->sizeScaleFactor);
	}
}

char * Planet::getDisplayText() {
	char * displayText = new char[512];
	if (blowingUp) 
	{
		sprintf_s(displayText, 512, "%s (Blowing up)~ Distance from Sun: %f AU~ Radius: %f AU~ Orbital Period: %f days~ Rotation Period: %f days~ Eccentricity: %f rad~ Inclination: %f rad~ Long. of ascending node: %f rad~ Axial Tilt: %f degrees~",
			name,
			distanceFromSun,
			radius,
			orbitalPeriod,
			rotationPeriod,
			eccentricity,
			inclination,
			lonOfAscendingNode,
			axialTilt);
	}
	else if (destroyed) 
	{
		sprintf_s(displayText, 512, "%s (Destroyed)~ Distance from Sun: %f AU~ Radius: %f AU~ Orbital Period: %f days~ Rotation Period: %f days~ Eccentricity: %f rad~ Inclination: %f rad~ Long. of ascending node: %f rad~ Axial Tilt: %f degrees~",
			name,
			distanceFromSun,
			radius,
			orbitalPeriod,
			rotationPeriod,
			eccentricity,
			inclination,
			lonOfAscendingNode,
			axialTilt);
	}
	else 
	{
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
	}
	return displayText;
}

void Planet::drawCube(double r) {
	glBegin(GL_QUADS);
	glTexCoord2d(r, r); glVertex3d(r, -r, r);  //top
	glTexCoord2d(-r, r); glVertex3d(r, -r, -r);
	glTexCoord2d(-r, -r); glVertex3d(-r, -r, -r);
	glTexCoord2d(r, -r); glVertex3d(-r, -r, r);


	glTexCoord2d(r, r); glVertex3d(r, r, r); //bottom
	glTexCoord2d(-r, r); glVertex3d(r, r, -r);
	glTexCoord2d(-r, -r); glVertex3d(-r, r, -r);
	glTexCoord2d(r, -r); glVertex3d(-r, r, r);


	glTexCoord2d(r, r); glVertex3d(r, r, r); //back
	glTexCoord2d(-r, r); glVertex3d(-r, r, r);
	glTexCoord2d(-r, -r); glVertex3d(-r, -r, r);
	glTexCoord2d(r, -r); glVertex3d(r, -r, r);


	glTexCoord2d(r, r); glVertex3d(r, r, -r); //front
	glTexCoord2d(-r, r); glVertex3d(-r, r, -r);
	glTexCoord2d(-r, -r); glVertex3d(-r, -r, -r);
	glTexCoord2d(r, -r); glVertex3d(r, -r, -r);

	glTexCoord2d(r, r); glVertex3d(r, r, r); //left
	glTexCoord2d(-r, r); glVertex3d(r, r, -r);
	glTexCoord2d(-r, -r); glVertex3d(r, -r, -r);
	glTexCoord2d(r, -r); glVertex3d(r, -r, r);


	glTexCoord2d(r, r); glVertex3d(-r, r, r); //right
	glTexCoord2d(-r, r); glVertex3d(-r, r, -r);
	glTexCoord2d(-r, -r); glVertex3d(-r, -r, -r);
	glTexCoord2d(r, -r); glVertex3d(-r, -r, r);

	glEnd();
}

void Planet::drawExplodingCube() {
	double distanceAway = (this->framesSinceBlowUp - DEATH_STAR_LAZER_TIME) * .01;
	double r = (radius * sizeScaleFactor) / 3.0;
	glTranslatef(r + distanceAway, 0, 0);
	drawCube(r);
	glTranslatef(-(r + distanceAway), 0, 0);

	glTranslatef(-(r + distanceAway), 0, 0);
	drawCube(r);
	glTranslatef(r + distanceAway, 0, 0);

	glTranslatef(0, r + distanceAway, 0);
	drawCube(r);
	glTranslatef(0, -(r + distanceAway), 0);

	glTranslatef(0, -(r + distanceAway), 0);
	drawCube(r);
	glTranslatef(0, r + distanceAway, 0);

	glTranslatef(r + distanceAway, r + distanceAway, 0);
	drawCube(r);
	glTranslatef(-(r + distanceAway), -(r + distanceAway), 0);

	glTranslatef(r + distanceAway, -(r + distanceAway), 0);
	drawCube(r);
	glTranslatef(-(r + distanceAway), r + distanceAway, 0);

	glTranslatef(-(r + distanceAway), r + distanceAway, 0);
	drawCube(r);
	glTranslatef(r + distanceAway, -(r + distanceAway), 0);

	glTranslatef(-(r + distanceAway), -(r + distanceAway), 0);
	drawCube(r);
	glTranslatef(r + distanceAway, r + distanceAway, 0);

	//l
	glTranslatef(0, 0, r + distanceAway);
	drawCube(r);
	glTranslatef(0, 0, -(r + distanceAway));

	glTranslatef(r + distanceAway, 0, r + distanceAway);
	drawCube(r);
	glTranslatef(-(r + distanceAway), 0, -(r + distanceAway));

	glTranslatef(-(r + distanceAway), 0, r + distanceAway);
	drawCube(r);
	glTranslatef(r + distanceAway, 0, -(r + distanceAway));

	glTranslatef(0, r + distanceAway, r + distanceAway);
	drawCube(r);
	glTranslatef(0, -(r + distanceAway), -(r + distanceAway));

	glTranslatef(0, -(r + distanceAway), r + distanceAway);
	drawCube(r);
	glTranslatef(0, r + distanceAway, -(r + distanceAway));

	glTranslatef(r + distanceAway, r + distanceAway, r + distanceAway);
	drawCube(r);
	glTranslatef(-(r + distanceAway), -(r + distanceAway), -(r + distanceAway));

	glTranslatef(r + distanceAway, -(r + distanceAway), r + distanceAway);
	drawCube(r);
	glTranslatef(-(r + distanceAway), r + distanceAway, -(r + distanceAway));

	glTranslatef(-(r + distanceAway), r + distanceAway, r + distanceAway);
	drawCube(r);
	glTranslatef(r + distanceAway, -(r + distanceAway), -(r + distanceAway));

	glTranslatef(-(r + distanceAway), -(r + distanceAway), r + distanceAway);
	drawCube(r);
	glTranslatef(r + distanceAway, r + distanceAway, -(r + distanceAway));

	//r
	glTranslatef(0, 0, -(r + distanceAway));
	drawCube(r);
	glTranslatef(0, 0, r + distanceAway);

	glTranslatef(r + distanceAway, 0, -(r + distanceAway));
	drawCube(r);
	glTranslatef(-(r + distanceAway), 0, r + distanceAway);

	glTranslatef(-(r + distanceAway), 0, -(r + distanceAway));
	drawCube(r);
	glTranslatef(r + distanceAway, 0, r + distanceAway);

	glTranslatef(0, r + distanceAway, -(r + distanceAway));
	drawCube(r);
	glTranslatef(0, -(r + distanceAway), r + distanceAway);

	glTranslatef(0, -(r + distanceAway), -(r + distanceAway));
	drawCube(r);
	glTranslatef(0, r + distanceAway, r + distanceAway);

	glTranslatef(r + distanceAway, r + distanceAway, -(r + distanceAway));
	drawCube(r);
	glTranslatef(-(r + distanceAway), -(r + distanceAway), r + distanceAway);

	glTranslatef(r + distanceAway, -(r + distanceAway), -(r + distanceAway));
	drawCube(r);
	glTranslatef(-(r + distanceAway), r + distanceAway, r + distanceAway);

	glTranslatef(-(r + distanceAway), r + distanceAway, -(r + distanceAway));
	drawCube(r);
	glTranslatef(r + distanceAway, -(r + distanceAway), r + distanceAway);

	glTranslatef(-(r + distanceAway), -(r + distanceAway), -(r + distanceAway));
	drawCube(r);
	glTranslatef(r + distanceAway, r + distanceAway, r + distanceAway);

	r = r * sizeScaleFactor * distanceAway;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //draw a wireframe
	glBegin(GL_QUAD_STRIP);
	double y = sin(inclination) * r;
	for (double i = 0; i < 2.0 * PI; i += PI / 32.0) {
		glVertex3f(cos(i) * r, cos(i) * y, sin(i) * r);
		glVertex3f(cos(i) * (r + r * .03), cos(i) * y, sin(i) * (r + r * .03));
	}
	glEnd();
}

void Planet::blowUpPlanet() {
	blowingUp = true;
	for (std::list<Planet>::iterator it = moons.begin(); it != moons.end(); ++it)
	{
		//it->blowUpPlanet();
	}
}

void Planet::setOrbitalGuidelines(bool param) {
	orbitalGuidelines = param;
	for (std::list<Planet>::iterator it = moons.begin(); it != moons.end(); ++it)
	{
		it->setOrbitalGuidelines(param);
	}
}