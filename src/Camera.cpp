#include "Camera.h"
#include <cmath>
#include "Planet.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef PI
#define PI 3.1415926535897932384626433832795028841971693993751058209
#endif

Camera::Camera() {
	camAngle = .5f;
	camHeightAngle = .2f;
	camRadius = 50.0f;
	camX = 0.0f;
	camY = 0.2f;
	camZ = 0.5f;

	centerX = 0.0f;
	centerY = 0.0f;
	centerZ = 0.0f;

	incAmount = .01f;
}

void Camera::getCamera() {
	camX = centerX + camRadius * cos(camAngle) * sin(camHeightAngle);
	camY = centerY + cos(camHeightAngle) * camRadius;
	camZ = centerZ + camRadius * sin(camAngle)* sin(camHeightAngle);
	
	gluLookAt(camX, camY, camZ,
		centerX, centerY, centerZ, //Always focused on the center point (the sun)
		0.0f, 1.0f, 0.0f);
}

void Camera::setCameraCenter(Planet * planet) {
	centerX = planet->getX();
	centerY = planet->getY();
	centerZ = planet->getZ();
}

void Camera::setCameraCenter(float x, float y, float z) {
	centerX = x;
	centerY = y;
	centerZ = z;
}

void Camera::zoomIn() {
	if ((camRadius - 1.0f) > 0)
		camRadius -= 1.0f;
}

void Camera::zoomOut() {
	if (camRadius + 1.0f < 200.0)
		camRadius += 1.0f;
}

void Camera::goLeft() {
	camAngle -= incAmount;
}

void Camera::goRight() {
	camAngle += incAmount;
}

void Camera::goUp() {
	if ((camHeightAngle + incAmount) < PI) {
		camHeightAngle += incAmount;
	}
}

void Camera::goDown() {
	if ((camHeightAngle - incAmount) > 0.0f) {
		camHeightAngle -= incAmount;
	}
}