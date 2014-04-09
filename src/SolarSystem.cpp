/***************************************************************************
* Source code By SyntaxRules ( syntaxrulesdevelopment@gmail.com )
****************************************************************************/
#include "SolarSystem.h"
#include "Planet.h"
#include "Star.h"
#include <list>
#include <fstream>
#include <string>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define KM_TO_AU .00000000668458712
#define DEG_TO_RAD 3.14159265358979/180.0
#define NUM_PLANETS 10

#ifndef PI
#define PI 3.1415926535897932384626433832795028841971693993751058209
#endif

using namespace std;

SolarSystem::SolarSystem() {
	planetSelected = 0;
	starBackgroundTexture = 0;
	//The death star obj was downloaded from http://www.blendswap.com/blends/view/73041
	// It is marked as "Fan art". It uses and condition can be found here:
	// http://www.blendswap.com/page/fan-art
	deathStar = new ImportedOBJ("obj/death_star2.obj", "img/deathstarTexture1024X1024.bmp");
}

void SolarSystem::init() {
	//SUN
	Star sun;
	sun.setName("Sun");
	sun.setDistanceFromSun(0);
	sun.setRadius(696342.0 / 25.0 * KM_TO_AU); // the sun is huge! so it needs an extra scale factor
	sun.setOrbitalPeriod(1);
	//rotspeed 7.189
	sun.setRotationPeriod(0.0);
	sun.setEccentricity(0.0);
	sun.setInclination(0.0 * DEG_TO_RAD);
	//sun.setAxialTilt(7.25); In this case, the sun shouldnt have any tilt
	sun.setColor(1.0f, 1.0f, 0.0f);
	sun.setOrbitalGuidelines(false);
	sun.setxyzGuidelines(false);
	//retrieved from http://planetpixelemporium.com/
	sun.setPlanetTexture("img/sunMap1000X500.bmp");

	planets.push_back(sun);

	//Mercury
	Planet mercury;
	mercury.setName("Mercury");
	mercury.setDistanceFromSun(0.39);
	mercury.setRadius(2439 * KM_TO_AU);
	mercury.setOrbitalPeriod(87.97);
	//rotspeed10.892
	mercury.setRotationPeriod(58.8);
	mercury.setEccentricity(0.2056);
	mercury.setInclination(3.38  * DEG_TO_RAD);
	mercury.setLonOfAcsendingNode(48.331 * DEG_TO_RAD);
	mercury.setAxialTilt(0.0);
	//retrieved from http://planetpixelemporium.com/
	mercury.setPlanetTexture("img/mercuryMap1000X500.bmp");

	planets.push_back(mercury);

	//Venus
	Planet venus;
	venus.setName("Venus");
	venus.setDistanceFromSun(0.73);
	venus.setRadius(6051.80 * KM_TO_AU);
	venus.setOrbitalPeriod(224.70);
	//rotspeed 6.42
	venus.setRotationPeriod(-244.0);
	venus.setEccentricity(0.0068);
	venus.setInclination(3.86  * DEG_TO_RAD);
	venus.setLonOfAcsendingNode(76.687 * DEG_TO_RAD);
	venus.setAxialTilt(177.26);
	//retrieved from http://planetpixelemporium.com/
	venus.setPlanetTexture("img/venusMap1000X500.bmp");

	planets.push_back(venus);

	//Earth
	Planet earth;
	earth.setName("Earth");
	earth.setDistanceFromSun(1);
	earth.setRadius(6378.10 * KM_TO_AU);
	earth.setOrbitalPeriod(365.26);
	//rotspeed 1674.4
	earth.setRotationPeriod(1.0);
	earth.setEccentricity(.0167);
	earth.setInclination(7.155 * DEG_TO_RAD);
	earth.setLonOfAcsendingNode(348.73936 * DEG_TO_RAD);
	earth.setAxialTilt(23.4);
	//retrieved from http://planetpixelemporium.com/
	earth.setPlanetTexture("img/earthMap1000X500.bmp");

	//Earths Moon
	std::list<Planet> earthMoons;
	Planet eMoon;
	eMoon.setName("Moon");
	eMoon.setDistanceFromSun(384000 * KM_TO_AU);
	eMoon.setRadius(1738.14 * KM_TO_AU);
	eMoon.setOrbitalPeriod(27.32);
	//rotspeed
	eMoon.setRotationPeriod(1.03);
	eMoon.setEccentricity(0.0549);
	eMoon.setInclination((7.155 + 25.00) * DEG_TO_RAD); //earths inclination + moons inclination (in ref to equator);
	eMoon.setIsMoon(true);
	//planet texture retrieved from http://planetpixelemporium.com/
	eMoon.setPlanetTexture("img/earthMoon1000X500.bmp");
	eMoon.recalculateDerivedValues();

	earthMoons.push_front(eMoon);
	earth.setMoons(earthMoons);

	planets.push_back(earth);

	//Mars
	Planet mars;
	mars.setName("Mars");
	mars.setDistanceFromSun(1.524);
	mars.setRadius(3396 * KM_TO_AU);
	mars.setOrbitalPeriod(686.97);
	//rotspeed 868.22
	mars.setRotationPeriod(1.03);
	mars.setEccentricity(.0934);
	mars.setInclination(5.65 * DEG_TO_RAD);
	mars.setLonOfAcsendingNode(49.562 * DEG_TO_RAD);
	mars.setAxialTilt(25.19);
	//planet texture retrieved from http://planetpixelemporium.com/
	mars.setPlanetTexture("img/marsMap1000X500.bmp");

	planets.push_back(mars);

	//Jupiter
	Planet jupiter;
	jupiter.setName("Jupiter");
	jupiter.setDistanceFromSun(5.203);
	jupiter.setRadius(71492 * KM_TO_AU);
	jupiter.setOrbitalPeriod(4332.59);
	//rotspeed 45300
	jupiter.setRotationPeriod(0.415);
	jupiter.setEccentricity(.0484);
	jupiter.setInclination(6.09 * DEG_TO_RAD);
	jupiter.setLonOfAcsendingNode(100.492 * DEG_TO_RAD);
	jupiter.setAxialTilt(3.13);
	//jupiter texture retrieved from http://planetpixelemporium.com/
	jupiter.setPlanetTexture("img/jupiterMap1000X500.bmp");

	//Jupiters moons
	std::list<Planet> jupiterMoons;
	//Io
	Planet io;
	io.setName("Io");
	io.setDistanceFromSun(421800.0 * KM_TO_AU);
	io.setRadius(1821.60 * KM_TO_AU);
	io.setOrbitalPeriod(1.769);
	//rotspeed
	io.setRotationPeriod(1.769);
	io.setEccentricity(.0041);
	io.setInclination((6.09 + 0.05) * DEG_TO_RAD);
	io.setIsMoon(true);

	io.setPlanetTexture("img/JupiterIOMoon1000X500.bmp");
	//inclination
	io.recalculateDerivedValues();

	jupiterMoons.push_front(io);
	//Europa
	Planet europa;
	europa.setName("Europa");
	europa.setDistanceFromSun(671100.0 * KM_TO_AU);
	europa.setRadius(1560.0 * KM_TO_AU);
	europa.setOrbitalPeriod(3.551);
	europa.setRotationPeriod(3.551);
	europa.setEccentricity(.0094);
	europa.setInclination((6.09 + 0.470) * DEG_TO_RAD);
	europa.setIsMoon(true);

	europa.setPlanetTexture("img/JupiterEuropa1000X500.bmp");
	europa.recalculateDerivedValues();

	jupiterMoons.push_front(europa);

	//Ganymede
	Planet ganymede;
	ganymede.setName("Ganymede");
	ganymede.setDistanceFromSun(1070400.0 * KM_TO_AU);
	ganymede.setRadius(2631.2 * KM_TO_AU);
	ganymede.setOrbitalPeriod(7.155);
	ganymede.setRotationPeriod(7.155);
	ganymede.setEccentricity(.204);
	ganymede.setInclination((6.09 + 0.02) * DEG_TO_RAD);
	ganymede.setIsMoon(true);

	ganymede.setPlanetTexture("img/JupiterGanymede1000X500.bmp");
	ganymede.recalculateDerivedValues();

	jupiterMoons.push_front(ganymede);

	//Callisto
	Planet callisto;
	callisto.setName("Callisto");
	callisto.setDistanceFromSun(1882700 * KM_TO_AU);
	callisto.setRadius(2410.30 * KM_TO_AU);
	callisto.setOrbitalPeriod(16.69);
	callisto.setRotationPeriod(16.689);
	callisto.setEccentricity(0.205);
	callisto.setInclination((6.09 + 0.192) * DEG_TO_RAD);
	callisto.setIsMoon(true);

	callisto.setPlanetTexture("img/JupiterCastillo1000X500.bmp");
	callisto.recalculateDerivedValues();

	jupiterMoons.push_front(callisto);
	jupiter.setMoons(jupiterMoons);

	planets.push_back(jupiter);

	//Saturn
	Planet saturn;
	saturn.setName("Saturn");
	saturn.setDistanceFromSun(9.539);
	saturn.setRadius(60268 * KM_TO_AU);
	saturn.setOrbitalPeriod(10759.22);
	saturn.setRotationPeriod(0.445);
	saturn.setEccentricity(0.0542);
	saturn.setInclination(5.51 * DEG_TO_RAD);
	saturn.setLonOfAcsendingNode(113.642811 * DEG_TO_RAD);
	saturn.setAxialTilt(26.73);
	//planet texture retrieved from http://planetpixelemporium.com/
	saturn.setPlanetTexture("img/saturnMap1000X500.bmp");

	saturn.setRing(422732.0*KM_TO_AU, 60268.0 * KM_TO_AU);
	//ring texture retrieved from http://planetpixelemporium.com/
	saturn.setRingTexture("img/saturnRing1024X72.bmp");

	//Saturn moons
	std::list<Planet> saturnMoons;
	Planet titan;
	titan.setName("Titan");
	titan.setDistanceFromSun(1221870 * KM_TO_AU);
	titan.setRadius(2576 * KM_TO_AU);
	titan.setOrbitalPeriod(15.95);
	//rotspeed
	titan.setRotationPeriod(15.95);
	titan.setEccentricity(.0288);
	titan.setInclination((5.51 + 0.34854) * DEG_TO_RAD);
	titan.setIsMoon(true);
	titan.recalculateDerivedValues();

	saturnMoons.push_front(titan);
	saturn.setMoons(saturnMoons);

	planets.push_back(saturn);

	//Uranus
	Planet uranus;
	uranus.setName("Uranus");
	uranus.setDistanceFromSun(19.18);
	uranus.setRadius(25559 * KM_TO_AU);
	uranus.setOrbitalPeriod(30799.1);
	uranus.setRotationPeriod(-0.72);
	uranus.setEccentricity(0.0472);
	uranus.setInclination(6.48 * DEG_TO_RAD);
	uranus.setLonOfAcsendingNode(73.989821 * DEG_TO_RAD);
	uranus.setAxialTilt(97.77);
	//uranus texture retrieved from http://planetpixelemporium.com/
	uranus.setPlanetTexture("img/uranusMap1000X500.bmp");

	uranus.setRing(71000.0*KM_TO_AU, 32000.0 * KM_TO_AU);
	//ring texture retrieved from http://planetpixelemporium.com/
	uranus.setRingTexture("img/uranusRing1024X72.bmp");

	planets.push_back(uranus);

	//Neptune
	Planet neptune;
	neptune.setName("Neptune");
	neptune.setDistanceFromSun(30.06);
	neptune.setRadius(24764 * KM_TO_AU);
	neptune.setOrbitalPeriod(60190.03);
	//rotspeed 9660
	neptune.setRotationPeriod(0.673);
	neptune.setEccentricity(.0086);
	neptune.setInclination(6.43 * DEG_TO_RAD);
	neptune.setLonOfAcsendingNode(131.79431 * DEG_TO_RAD);
	neptune.setAxialTilt(28.32);
	//planet texture retrieved from http://planetpixelemporium.com/
	neptune.setPlanetTexture("img/neptuneMap1000X500.bmp");

	//Neptune moons
	std::list<Planet> neptuneMoons;
	//Triton
	Planet triton;
	triton.setName("Triton");
	triton.setDistanceFromSun(354759 * KM_TO_AU);
	triton.setRadius(1353.4 * KM_TO_AU);
	triton.setOrbitalPeriod(-5.876854);
	//rotspeed
	triton.setRotationPeriod(-5.876854);
	triton.setEccentricity(.000016);
	triton.setInclination((6.43 + 156.885) * DEG_TO_RAD);
	triton.setIsMoon(true);
	triton.recalculateDerivedValues();

	neptuneMoons.push_front(triton);
	neptune.setMoons(neptuneMoons);

	planets.push_back(neptune);

	//Pluto
	Planet pluto;
	pluto.setName("Pluto");
	pluto.setDistanceFromSun(38.53);
	pluto.setRadius(1153 * KM_TO_AU);
	pluto.setOrbitalPeriod(90465);
	pluto.setRotationPeriod(6.41);
	pluto.setEccentricity(0.2488);
	pluto.setInclination(11.88 * DEG_TO_RAD);
	pluto.setLonOfAcsendingNode(110.28683 * DEG_TO_RAD);
	pluto.setAxialTilt(122.53);
	//planet texture retrieved from http://planetpixelemporium.com/
	pluto.setPlanetTexture("img/plutoMap1000X500.bmp");

	planets.push_back(pluto);

	for (int i = 0; i < NUM_PLANETS; i++)
	{
		planets[i].recalculateDerivedValues();
	}

	for (int i = 0; i < 2000; i++) {
		asteroidBelt.addAsteroid();
	}

	/* //This version of opengl isn't quite fast enough to handle this amount of aseroits... to bad eh?
	ifstream file("asteroids.csv");
	string value;
	while (file.good())
	{
		//full_name,a,e,i,om,per_y,diameter,rot_per
		Planet tempAster;
		getline(file, value, ','); //full name
		tempAster.setName((char *)value.c_str());
		getline(file, value, ','); //a semi major axis
		tempAster.setDistanceFromSun(atof(value.c_str()));
		getline(file, value, ','); //e ecentriccity
		tempAster.setEccentricity(atof(value.c_str()));
		getline(file, value, ','); //i inclination
		tempAster.setInclination(atof(value.c_str()) * DEG_TO_RAD);
		getline(file, value, ','); // om log of acending node
		tempAster.setLonOfAcsendingNode(atof(value.c_str()) * DEG_TO_RAD);
		getline(file, value, ','); //orbital period (years)
		tempAster.setOrbitalPeriod(atof(value.c_str()) * 365.25);
		getline(file, value, ','); //planet diameter (km)
		tempAster.setRadius(atof(value.c_str()) / 2.0 * KM_TO_AU * 100);
		getline(file, value, ','); // rot peeriod
		tempAster.setRotationPeriod(atof(value.c_str()));

		tempAster.recalculateDerivedValues();

		asteroids.push_back(tempAster);
	}*/
}

void SolarSystem::loadStarBackgroundTexture()
{
	int width, height;

	unsigned char * data;

	FILE * file;

	fopen_s(&file, "img/outterspace2.bmp", "rb");

	if (file == NULL) return;
	width = 500;
	height = 300;
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

	glGenTextures(1, &starBackgroundTexture);
	glBindTexture(GL_TEXTURE_2D, starBackgroundTexture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
}

void SolarSystem::draw() {
	//check if the background texture is initialized, if not, try init again.
	if (starBackgroundTexture == 0) {
		loadStarBackgroundTexture();
		init();
	}
	//add ambient light
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//add a positioned light
	GLfloat lightcolor0[] = { 5.5f, 5.5f, 5.5f, 1.0f };
	GLfloat lightPos0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	for (int i = 0; i < NUM_PLANETS; i++) {
		if (i == 0) glDisable(GL_LIGHTING); //The light source is in the sun, so the sun needs to shine on its own!
		planets[i].draw();
		if (i == 0) glEnable(GL_LIGHTING);
		planets[i].advance();
	}

	/*for (int i = 0; i < asteroids.size(); i++) {
		//asteroids[i].draw();
	}*/

	asteroidBelt.draw();

	//draw Starry background ( a cube around the*/
	glDisable(GL_LIGHTING);
	double r = 200.0;
	double deltaY = .15;
	double theta = 0.0;
	double textureX = 1.0;
	double bottomToTopStrips = 3.0*10.0;
	double circChunks = 5.0*10.0;

	glBindTexture(GL_TEXTURE_2D, starBackgroundTexture);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	for (double thetaY = 0.0; thetaY < PI; thetaY += PI / bottomToTopStrips) {
		textureX = 1.0;
		for (theta = -PI; theta < PI; theta += PI / (circChunks / 2.0)) {
			glTexCoord2d(textureX, 0.0);
			glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY));

			glTexCoord2d(textureX, 1.0);
			glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left

			if (textureX == 1.0)
				textureX = 0.0;
			else
				textureX = 1.0;
		}
		glTexCoord2d(textureX, 1.0);
		glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left

		glTexCoord2d(textureX, 0.0);
		glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left

	}
	glEnd();
	glEnable(GL_LIGHTING);

	deathStar->draw();
}

void SolarSystem::incSizeScaleFactor() {
	planets[0].setSizeScaleFactor(planets[0].getSizeScaleFactor() + 10.0);
	for (int i = 0; i < NUM_PLANETS; i++) {
		planets[i].setSizeScaleFactor(planets[0].getSizeScaleFactor());
	}
	asteroidBelt.setSizeScaleFactor(planets[0].getSizeScaleFactor());
}

void SolarSystem::decSizeScaleFactor() {
	planets[0].setSizeScaleFactor(planets[0].getSizeScaleFactor() - 10.0);
	for (int i = 0; i < NUM_PLANETS; i++) {
		planets[i].setSizeScaleFactor(planets[0].getSizeScaleFactor());
	}
	asteroidBelt.setSizeScaleFactor(planets[0].getSizeScaleFactor());
}

void SolarSystem::incSimSpeed() {
	planets[0].setSpeed(planets[0].getSpeed() + .01);
	for (int i = 0; i < NUM_PLANETS; i++) {
		planets[i].setSpeed(planets[0].getSpeed());
	}
}

void SolarSystem::decSimSpeed() {
	planets[0].setSpeed(planets[0].getSpeed() - .01);
	for (int i = 0; i < NUM_PLANETS; i++) {
		planets[i].setSpeed(planets[0].getSpeed());
	}
}

void SolarSystem::blowUpPlanet(int planetNum) {
	if (planetNum > NUM_PLANETS || planetNum < 0) {
		return; //no going out of bounds...
	}
	planets[planetNum].blowUpPlanet();
}

void SolarSystem::regeneratePlanets() {
	for (int i = 0; i < NUM_PLANETS; i++) {
		planets[i].regeneratePlanet();
	}
}

void SolarSystem::toggleOrbitalGuidelines() {
	bool on = !planets[1].orbitalGuidelinesOn();
	for (int i = 1; i < NUM_PLANETS; i++) {
		planets[i].setOrbitalGuidelines(on);
	}
}