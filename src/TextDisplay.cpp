/***************************************************************************
* Source code By SyntaxRules ( syntaxrulesdevelopment@gmail.com )
****************************************************************************/
#include "TextDisplay.h"
#include <fstream>
#include <string>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

TextDisplay::TextDisplay() {
	font = GLUT_BITMAP_8_BY_13;
	framesPerSecond = new char[256];
	framesPerSecond[0] = '\0';
	cameraPos = new char[256];
	cameraPos[0] = '\0';
	simulationSpeed = new char[256];
	simulationSpeed[0] = '\0';
	planetSizeScaleFactor = new char[256];
	planetSizeScaleFactor[0] = '\0';
	planetDisplayInfo = new char[512];
	planetDisplayInfo[0] = '\0';
	showPlanetInfo = false;
}

void TextDisplay::setOrthographicProjection(float height, float width) {
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, height, width, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void TextDisplay::restorePerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void TextDisplay::renderBitmapString(float x, float y, float z, const char *string) {
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void TextDisplay::display(float height, float width) {
	setOrthographicProjection(height, width);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_LIGHTING);

	int lineNum = 1;


	if (cameraPos[0] != '\0') {
		renderBitmapString(10, lineNum++ * 15, 0, cameraPos);
	}
	if (framesPerSecond[0] != '\0') {
		renderBitmapString(10, lineNum++ * 15, 0, framesPerSecond);
	}
	if (simulationSpeed[0] != '\0') {
		renderBitmapString(10, lineNum++ * 15, 0, simulationSpeed);
	}
	if (planetSizeScaleFactor[0] != '\0') {
		renderBitmapString(10, lineNum++ * 15, 0, planetSizeScaleFactor);
	}
	lineNum = 1;
	renderBitmapString(width - 175, lineNum++ * 15, 0, (char *)"< or > - Change speed");
	renderBitmapString(width - 175, lineNum++ * 15, 0, (char *)": or ; - Change planet size");
	renderBitmapString(width - 175, lineNum++ * 15, 0, (char *)"1-9 - Planet selectors");
	renderBitmapString(width - 175, lineNum++ * 15, 0, (char *)"o - Toggle orbital guidelines");
	renderBitmapString(width - 175, lineNum++ * 15, 0, (char *)"i - Toggle info overlay");
	renderBitmapString(width - 175, lineNum++ * 15, 0, (char *)"Esc - Quit");

	float r = 20.0;

	if (showPlanetInfo && planetDisplayInfo[0] != '\0') {
		glBegin(GL_LINES);
		//Draw center target
		glVertex2f(width / 2.0, height / 2.0 + r);
		glVertex2f(width / 2.0 - r, height / 2.0);

		glVertex2f(width / 2.0 - r, height / 2.0);
		glVertex2f(width / 2.0, height / 2.0 - r);

		glVertex2f(width / 2.0, height / 2.0 - r);
		glVertex2f(width / 2.0 + r, height / 2.0);
	
		glVertex2f(width / 2.0 + r, height / 2.0);
		glVertex2f(width / 2.0, height / 2.0 + r);
		//End Draw Box

		glVertex2f(width / 2.0, height / 2.0 - r);
		glVertex2f(width / 2.0 + 2 * r, height / 2.0 - 2.0*r);

		glVertex2f(width / 2.0 + 2 * r, height / 2.0 - 2.0*r);
		glVertex2f(width / 2.0 + 2 * r, height / 2.0 + 2.0*r);

		glEnd();

		//draw info
		std::string pdis(planetDisplayInfo);
		int beginPos = 0;
		lineNum = 1;
		for (int i = 0; i < pdis.length(); i++) {
			if (pdis[i] == '~') {
				renderBitmapString(width / 2.0 + 2 * r + 5.0, height / 2.0 - (2.0*r + lineNum++ * -15), 0, pdis.substr(beginPos, i - beginPos).c_str());
				beginPos = i + 1;
			}
		}
	}

	glEnable(GL_LIGHTING);
	restorePerspectiveProjection();
}

void TextDisplay::setFramesPerSecond(float fps) {
	sprintf_s(framesPerSecond, 256, "FPS: %f", fps);
}

void TextDisplay::setCameraPos(float x, float y, float z) {
	sprintf_s(cameraPos, 256, "Camera Position: X: %f, Y: %f, Z: %f", x, y, z);
}

void TextDisplay::setSimSpeed(double speed) {
	sprintf_s(simulationSpeed, 256, "Simulation speed: ~%f days per second", speed);
}

void TextDisplay::setPlanetSizeScaleFactor(double scale) {
	sprintf_s(planetSizeScaleFactor, 256, "Planet Size: %fX the orbit", scale);
}