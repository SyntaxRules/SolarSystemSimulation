/***************************************************************************
* Source code By SyntaxRules ( syntaxrulesdevelopment@gmail.com )
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "Planet.h"
#include "Camera.h"
#include "TextDisplay.h"
#include "AsteroidBelt.h"
#include "SolarSystem.h"

#include <glm/glm.hpp>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define KM_TO_AU .00000000668458712
#define DEG_TO_RAD 3.14159265358979/180.0
#define NUM_PLANETS 10

/*TODOS
Add textures to moons
Make Moon class (to separate from normal planets)
Port to opengl 3.3
	Implement shaders
	Implement point lights for background stars
	Implement sun rays
*/

SolarSystem solarSystem;
Camera *camera;
TextDisplay textDisplay;
double width, height;
bool viewDeathStar = false;

/* Program initialization NOT OpenGL/GLUT dependent,
as we haven't created a GLUT window yet */
void init()
{
	camera = new Camera();
	width = 900;
	height = 900;
}

/* Callback functions for GLUT */

/*It turns out you need this reshape function for changing the window size 
AND what is viewable in the window (the viewport)*/
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 400.0f); //last param sets the far clip!

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

/* Draw the window - this is where all the GL actions are */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera->getCamera();

	glDrawBuffer(GL_BACK_RIGHT);
	solarSystem.draw();
	if (!viewDeathStar)
		camera->setCameraCenter(solarSystem.getSelectedPlanet());

	glDrawBuffer(GL_BACK_LEFT);
	glDisable(GL_TEXTURE_2D);
	if (viewDeathStar) 
	{
		char * displayText = new char[512];
		sprintf_s(displayText, 512, "The Death Star~ Enough said...~");
		textDisplay.setPlanetDisplayInfo(displayText);
	}
	else
	{
		textDisplay.setPlanetDisplayInfo(solarSystem.getSelectedPlanet()->getDisplayText());
	}
	textDisplay.setCameraPos(camera->getCamX(), camera->getCamY(), camera->getCamZ());
	textDisplay.display(height, width);
	glEnable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {
	switch (key) {
	case 27:
		exit(0); //TOOD: write cleanup function
		break;
	case '!':
		solarSystem.blowUpPlanet(1);
		break;
	case '@':
		solarSystem.blowUpPlanet(2);
		break;
	case'#':
		solarSystem.blowUpPlanet(3);
		break;
	case'$':
		solarSystem.blowUpPlanet(4);
		break;
	case'%':
		solarSystem.blowUpPlanet(5);
		break;
	case'^':
		solarSystem.blowUpPlanet(6);
		break;
	case'&':
		solarSystem.blowUpPlanet(7);
		break;
	case'*':
		solarSystem.blowUpPlanet(8);
		break;
	case'(':
		solarSystem.blowUpPlanet(9);
		break;
	case 43: //+
		camera->zoomIn();
		break;
	case 45: //-
		camera->zoomOut();
		break;
	case 48: //0
	case 49: //1
	case 50: //2
	case 51: //3
	case 52: //4
	case 53: //5
	case 54: //6
	case 55: //7
	case 56: //8
	case 57: //9
		viewDeathStar = false;
		solarSystem.setPlanetSelected(key - 48);
		camera->setCameraCenter(solarSystem.getSelectedPlanet());
		textDisplay.setPlanetDisplayInfo(solarSystem.getSelectedPlanet()->getDisplayText());
		break;
	case 58: //:
		solarSystem.incSizeScaleFactor();
		textDisplay.setPlanetSizeScaleFactor(solarSystem.getSizeScaleFactor());
		break;
	case 59: //;
		solarSystem.decSizeScaleFactor();
		textDisplay.setPlanetSizeScaleFactor(solarSystem.getSizeScaleFactor());
		break;
	case 60: // <
		solarSystem.decSimSpeed();
		textDisplay.setSimSpeed(40.0 * solarSystem.getSimSpeed());
		break;
	case 62: // >
		solarSystem.incSimSpeed();
		textDisplay.setSimSpeed(40.0 * solarSystem.getSimSpeed());
		break;
	case 'd':
		viewDeathStar = true;
		camera->setCameraCenter(-1.75, .7, -1.75);
		break;
	case 'i': //i for info
		textDisplay.showPlanetInfo = !textDisplay.showPlanetInfo;
		break;
	case 'o':
		solarSystem.toggleOrbitalGuidelines();
		break;
	case 'r':
		solarSystem.regeneratePlanets();
		break;
	}
}

void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		camera->goLeft();
		break;
	case GLUT_KEY_RIGHT:
		camera->goRight();
		break;
	case GLUT_KEY_UP:
		camera->goUp();
		break;
	case GLUT_KEY_DOWN:
		camera->goDown();
		break;
	}
}


void processMouseClick(int button, int state, int x, int y) {
	if (state == GLUT_UP) {
		printf("Mouse clicked at %d, %d\n", x, y);
	}
	else {
		printf("Mouse clicked at %d, %d\n", x, y);
	}
}

void processMouseMovement(int x, int y){
	printf("Mouse movement at %d, %d\n", x, y);
}

//Called every 25 milliseconds
//40 FPS = 25ms
void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[])
{
	width = 900;
	height = 900;
	/// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("The Solar System");

	//* register function to handle window resizes
	//It turns out you need this reshape function for changing the window size 
	//AND what is viewable in the window (the viewport)
	glutReshapeFunc(changeSize);

	//* register function that draws in the window
	glutDisplayFunc(display);
	//glutIdleFunc(display);
	glutTimerFunc(25, update, 0);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseClick);
	glutMotionFunc(processMouseMovement);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_NORMALIZE); //normalizes all vectors to one.
	glShadeModel(GL_SMOOTH); //uses the normal vectors to determine shading!

	init();
	//textDisplay.setFramesPerSecond(40.0f);
	textDisplay.setSimSpeed(40.0*0.31);

	//* start the GLUT main loop 
	glutMainLoop();

	return 1;
}