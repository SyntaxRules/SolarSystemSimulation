#include "Asteroid.h"
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef PI
#define PI 3.1415926535897932384626433832795028841971693993751058209
#endif

Asteroid::Asteroid(double x, double y, double z) {
	xPos = x;
	yPos = y;
	zPos = z;
	radius = .000005;
	sizeScaleFactor = 1001;
}

void Asteroid::draw() {
	glTranslatef(xPos, yPos, zPos);

	double r = radius * sizeScaleFactor;
	double deltaY = .15;
	double theta = 0.0;
	//double textureX = 1.0;
	//double textureY = 1.0;
	double bottomToTopStrips = 4.0;
	double circChunks = 4.0;

	glPushMatrix();

	glBegin(GL_QUAD_STRIP);
	glColor3ub(122.0, 106.0, 56.0);
	for (double thetaY = 0.0; thetaY < PI; thetaY += PI / bottomToTopStrips) {
		//textureX = 1.0;
		for (theta = -PI; theta < PI; theta += PI / (circChunks / 2.0)) {
			//glTexCoord2d(textureX, textureY);
			glNormal3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
			glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY));

			//glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips));
			glNormal3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
			glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
			//textureX -= 1.0 / circChunks;
		}
		//glTexCoord2d(textureX, textureY);
		glNormal3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
		glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left

		//glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips));
		glNormal3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
		glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left

		//textureY -= 1.0 / bottomToTopStrips;
	}
	glEnd();

	glPopMatrix();

	glTranslatef(-xPos, -yPos, -zPos);
}