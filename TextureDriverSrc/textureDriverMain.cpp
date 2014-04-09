#include <cmath>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


float angle = 0.0f;
float camAngle = .5f;
float camHeightAngle = .5f;
float camRadius = 3.0f;
float camX = 0.0f;
float camY = 0.2f;
float camZ = 0.5f;
float angleY = 1.0f;
int drawNumber = 10;
#define PI 3.1415926535897932384626433832795028841971693993751058209

#define NUM_RANDS 10000
double randAngels[NUM_RANDS][3];

GLuint texture;

void draw1();
void draw2();
void draw3();
void draw4();
void draw5();
void draw6();
void draw7();
void draw8();
void draw9();
void draw10();
void draw11();
void draw12(); //draw square

GLuint LoadTexture(const char * filename)
{

	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

	fopen_s(&file, filename, "rb");

	if (file == NULL) return 0;
	width = 1000;
	height = 500;
	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
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


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

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
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	float tempRadius = camRadius - abs(cos(camHeightAngle) * camRadius);
	gluLookAt(cos(camAngle) * tempRadius, cos(camHeightAngle) * camRadius, sin(camAngle)* tempRadius,
		0.0f, 0.0f, 0.0f,
		0.0f, angleY, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	switch (drawNumber) {
	case 1:
		draw1();
		break;
	case 2:
		draw2();
		break;
	case 3:
		draw3();
		break;
	case 4:
		draw4();
		break;
	case 5:
		draw5();
		break;
	case 6:
		draw6();
		break;
	case 7:
		draw7();
		break;
	case 8:
		draw8();
		break;
	case 9:
		draw9();
		break;
	case 10:
		draw10();
		break;
	case 11:
		draw11();
		break;
	case 12:
		draw12();
		break;
	}

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {
	if (key == 27)
		exit(0);
	float incAmount = .1;
	switch (key) {
	case 43: //+
		camRadius -= incAmount;
		break;
	case 45: //-
		camRadius += incAmount;
		break;
	case 91: //[
		angleY -= incAmount;
		break;
	case 93: //]
		angleY += incAmount;
		break;
	case 113: //q
		drawNumber--;
		break;
	case 119: //w
		drawNumber++;
		break;
	}
}
void processSpecialKeys(int key, int xx, int yy) {
	float incAmount = .01;
	switch (key) {
	case GLUT_KEY_LEFT:
		camAngle -= incAmount;
		break;
	case GLUT_KEY_RIGHT:
		camAngle += incAmount;
		break;
	case GLUT_KEY_UP:
		if ((camHeightAngle + incAmount) < PI) {
			camHeightAngle += incAmount;
		}
		break;
	case GLUT_KEY_DOWN:
		if ((camHeightAngle - incAmount) > 0.0f) {
			camHeightAngle -= incAmount;
		}
		break;
	}
}

//Called every 25 milliseconds
//40 FPS = 25ms
void update(int value) {
	angle += .01f;
	if (angle > 360) {
		angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(900, 900);
	glutCreateWindow("Texture driver main");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	texture = LoadTexture("earthmap1k.bmp");

	//need this to enable textures
	glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutTimerFunc(25, update, 0);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glEnable(GL_DEPTH_TEST);
	randAngels[0][0] = 0.0;
	randAngels[0][1] = 0.0;
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

void draw1() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 4; i++) {
		float yOffset = 0.5f;
		float xOffset = 1.0f;

		switch (i) {
		case 1:
			xOffset = 0.0f;
			yOffset = 0.0f;
			break;
		case 2:
			xOffset = 0.0f;
			yOffset = 0.5f;
			break;
		case 3:
			xOffset = 1.0f;
			yOffset = 0.0f;
			break;
		case 4:
			xOffset = 1.0f;
			yOffset = 0.5f;
			break;

		}

		glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 0.0f, yOffset + 0.0f, 0.0f); //bottom left
		glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 0.0f, yOffset + 0.5f, 0.0f); //top left
		glTexCoord2f(0.5f, 0.5f); glVertex3f(xOffset + 0.5f, yOffset + 0.25f, 0.2f); //center

		glTexCoord2f(0.0f, 1.0f); glVertex3f(xOffset + 0.0f, yOffset + 0.5f, 0.0f); //top left
		glTexCoord2f(0.5f, 0.5f); glVertex3f(xOffset + 0.5f, yOffset + 0.25f, 0.2f); //center
		glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 1.0f, yOffset + 0.5f, 0.0f); // top right

		//glVertex3f(xOffset + 0.0f, yOffset + 0.5f, 0.0f); //top left
		//glVertex3f(xOffset + 0.5f, yOffset + 0.25f, 0.2f); //center
		//glVertex3f(xOffset + 1.0f, yOffset + 0.5f, 0.0f); // top right


		glTexCoord2f(1.0f, 1.0f); glVertex3f(xOffset + 1.0f, yOffset + 0.5f, 0.0f); //top right
		glTexCoord2f(0.5f, 0.5f); glVertex3f(xOffset + 0.5f, yOffset + 0.25f, 0.2f); //center
		glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 1.0f, yOffset + 0.0f, 0.0f); //bottom right

		glTexCoord2f(1.0f, 0.0f); glVertex3f(xOffset + 1.0f, yOffset + 0.0f, 0.0f); //bottom right
		glTexCoord2f(0.5f, 0.5f); glVertex3f(xOffset + 0.5f, yOffset + 0.25f, 0.2f); //center
		glTexCoord2f(0.0f, 0.0f); glVertex3f(xOffset + 0.0f, yOffset + 0.0f, 0.0f); //bottome left
	}
	glEnd();

}
double X = .525731112119133606;
double Z = .850650808352039932;
float vData[12][3] = {
	{ -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
	{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
	{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 }
};
int tindices[20][3] = {
	{ 1, 4, 0 }, { 4, 9, 0 }, { 4, 9, 5 }, { 8, 5, 4 }, { 1, 8, 4 },
	{ 1, 10, 8 }, { 10, 3, 8 }, { 8, 3, 5 }, { 3, 2, 5 }, { 3, 7, 2 },
	{ 3, 10, 7 }, { 10, 6, 7 }, { 6, 11, 7 }, { 6, 0, 11 }, { 6, 1, 0 },
	{ 10, 1, 6 }, { 11, 0, 9 }, { 2, 11, 9 }, { 5, 2, 9 }, { 11, 2, 7 }
};
void draw2() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++) {
		//icoNormVec(i);
		glVertex3fv(&vData[tindices[i][0]][0]);
		glVertex3fv(&vData[tindices[i][1]][0]);
		glVertex3fv(&vData[tindices[i][2]][0]);
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void draw3() {
	glBindTexture(GL_TEXTURE_2D, texture);
	double lats = 20;
	double longs = 20;
	double r = 1.0;
	double i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);
		double lat1 = PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);
			glNormal3f(x * zr0, y * zr0, z0);
			glTexCoord2f(j / longs, i / lats); glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glTexCoord2f((j + 1.0) / longs, (i + 1.0) / lats); glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}
void draw4() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float theta = 0, phi = 0, deltaTheta = PI / 9, deltaPhi = PI / 9;
	float z1, x1, y1, z2, x2, y2, z3, x3, y3, z4, x4, y4;
	float r = 1.0;

	glBegin(GL_QUAD_STRIP);

	for (theta = 0; theta <= 2 * PI; theta += deltaTheta)
	{
		for (phi = 0; phi <= PI; phi += deltaPhi)
		{

			z1 = r * sin(phi + deltaPhi) * cos(theta + deltaTheta);
			x1 = r * sin(phi + deltaPhi) * sin(theta + deltaTheta);
			y1 = r * cos(phi + deltaPhi);

			z2 = r * sin(phi) * cos(theta + deltaTheta);
			x2 = r * sin(phi) * sin(theta + deltaTheta);
			y2 = r * cos(phi);

			z3 = r * sin(phi) * cos(theta);
			x3 = r * sin(phi) * sin(theta);
			y3 = r * cos(phi);

			z4 = r * sin(phi + deltaPhi) * cos(theta);
			x4 = r * sin(phi + deltaPhi) * sin(theta);
			y4 = r * cos(phi + deltaPhi);

			glColor3f(cos(phi), sin(phi), sin(phi));
			glVertex3f(x4, y4, z4);
			glColor3f(cos(phi), sin(phi), cos(phi));
			glVertex3f(x1, y1, z1);
			glColor3f(cos(theta), sin(theta), sin(theta));
			glVertex3f(x2, y2, z2);
			glColor3f(cos(theta), sin(theta), cos(theta));
			glVertex3f(x3, y3, z3);
		}
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void draw5() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(0.0f, 0.0f, 0.0f); //bottom left
	glVertex3f(0.0f, 0.25f, 0.0f); //top left
	glVertex3f(0.5f, 0.0f, 0.0f); //bottom right
	glVertex3f(0.5f, 0.25f, 0.0f); //top right
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void draw6() {
	double r = 1.0;
	double deltaY = .3;
	double theta = 0.0;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	for (theta; theta <= 2.0 * PI; theta += PI / 24.0) {
		glVertex3d(r*cos(theta), deltaY, r*sin(theta)); //bottom left
		glVertex3d(r*cos(theta), -1.0*deltaY, r*sin(theta)); //bottom left
	}
	glVertex3d(r*cos(theta), deltaY, r*sin(theta)); //bottom left
	glVertex3d(r*cos(theta), -1.0*deltaY, r*sin(theta)); //bottom left
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void draw7() {
	double r = 1.0;
	double deltaY = 1.0;
	double theta = 0.0;
	double textureX = 0.0;
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUAD_STRIP);
	for (theta; theta <= 2.0 * PI; theta +=  PI/24.0) {
		glTexCoord2d(textureX, 1.0); glVertex3d(r*cos(theta), deltaY, r*sin(theta)); //bottom left
		glTexCoord2d(textureX, 0.0); glVertex3d(r*cos(theta), -1.0*deltaY, r*sin(theta)); //bottom left
		textureX += 1.0 / 48.0;
	}
	glTexCoord2d(1.0, 1.0); glVertex3d(r*cos(theta), deltaY, r*sin(theta)); //bottom left
	glTexCoord2d(1.0, 0.0); glVertex3d(r*cos(theta), -1.0*deltaY, r*sin(theta)); //bottom left
	glEnd();
}
void draw8() {
	double r = 1.0;
	double deltaY = .15;
	double theta = 0.0;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	for (double thetaY = -PI; thetaY < PI; thetaY += PI / 8.0) {

		for (theta = -PI; theta < PI; theta += PI / 8.0) {
			glVertex3d(r * cos(theta), r * cos(thetaY), r * sin(theta)); //bottom left
			glVertex3d(r * cos(theta), r * cos(thetaY + PI / 8.0), r * sin(theta)); //bottom left
		}
		//connect to the last one
		//glVertex3d(r*cos(theta), thetaY + deltaY, r*sin(theta)); //bottom left
		//glVertex3d(r*cos(theta), thetaY - deltaY, r*sin(theta)); //bottom left
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void draw9() {
	double r = .5;
	double deltaY = .15;
	double theta = 0.0;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glRotatef(23.4, 1.0f, 1.0f, 1.0f); //angle in degrees
	glBegin(GL_QUAD_STRIP);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	//Note We only go up to thetaY < 0 becasue we are drawing the whole ring!
	for (double thetaY = 0.0; thetaY < PI; thetaY += PI / 8.0) {

		for (theta = -PI; theta < PI; theta += PI / 8.0) {
			glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
			glVertex3d(r * cos(theta) * sin(thetaY + PI / 8.0), r * cos(thetaY + PI / 8.0), r * sin(theta) * sin(thetaY + PI / 8.0)); //bottom left
		}
		glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
		glVertex3d(r * cos(theta) * sin(thetaY + PI / 8.0), r * cos(thetaY + PI / 8.0), r * sin(theta) * sin(thetaY + PI / 8.0)); //bottom left
	}
	glEnd();
	
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 0.0f, .2f);
	r = .6;
	if (randAngels[0][0] == 0.0) {
		for (int i = 0; i < NUM_RANDS; i++) {
			double rand1 = ((rand() % 10000) * .000628318530718);
			double rand2 = ((rand() % 10000) * .000628318530718); 
			double randR = .5 + ((rand() % 10000) * .0000112);
			glVertex3d(r * cos(rand1) * sin(rand2), r * cos(rand2), r * sin(rand1) * sin(rand2)); //bottom left
			glVertex3d(r * cos(rand1) * sin(rand2 + PI / 8.0), r * cos(rand2 + PI / 8.0), r * sin(rand1) * sin(rand2 + PI / 8.0));
			randAngels[i][0] = rand1;
			randAngels[i][1] = rand2;
			randAngels[i][2] = randR;
		}
	} else {
		for (int i = 0; i < NUM_RANDS; i++) {
			
			glVertex3d(randAngels[i][2] * cos(randAngels[i][0]) * sin(randAngels[i][1]), randAngels[i][2] * cos(randAngels[i][1]), randAngels[i][2] * sin(randAngels[i][0]) * sin(randAngels[i][1])); //bottom left
			glVertex3d(randAngels[i][2] * cos(randAngels[i][0]) * sin(randAngels[i][1] + PI / 48.0), randAngels[i][2] * cos(randAngels[i][1] + PI / 48.0), randAngels[i][2] * sin(randAngels[i][0]) * sin(randAngels[i][1] + PI / 48.0));
		}

	}
	glEnd();
	
	/*Add Atmosphere!
	r = .8;
	deltaY = .15;
	theta = 0.0;
	//glRotatef(23.4, 1.0f, 1.0f, 1.0f); //angle in degrees
	glBegin(GL_QUAD_STRIP);
	glColor4f(1.0f, 1.0f, 1.0f, .1f);
	//Note We only go up to thetaY < 0 becasue we are drawing the whole ring!
	for (double thetaY = 0.0; thetaY < PI; thetaY += PI / 8.0) {

		for (theta = -PI; theta < PI; theta += PI / 8.0) {
			glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
			glVertex3d(r * cos(theta) * sin(thetaY + PI / 8.0), r * cos(thetaY + PI / 8.0), r * sin(theta) * sin(thetaY + PI / 8.0)); //bottom left
		}
		glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
		glVertex3d(r * cos(theta) * sin(thetaY + PI / 8.0), r * cos(thetaY + PI / 8.0), r * sin(theta) * sin(thetaY + PI / 8.0)); //bottom left
	}
	glEnd();

	/*Add rings!
	double ringWidth = .5;
	r += .2;
	glBegin(GL_QUAD_STRIP);
	for (theta = -PI; theta < PI; theta += PI / 8.0) {
		glVertex3d(r * cos(theta), 0, r * sin(theta));
		glVertex3d((r+ringWidth) * cos(theta), 0, (r+ringWidth) * sin(theta));
	}
	glVertex3d(r * cos(theta), 0, r * sin(theta));
	glVertex3d((r + ringWidth) * cos(theta), 0, (r + ringWidth) * sin(theta));
	glEnd();
	//*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


//The numbers are very picky! if you change any of these numbers you'll need to retest!
void draw10() {
	double r = 1.0;
	double deltaY = .15;
	double theta = 0.0;
	double textureX = 1.0;
	double textureY = 1.0;
	double bottomToTopStrips = 16.0;
	double circChunks = 32.0;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUAD_STRIP);
	for (double thetaY = 0.0; thetaY < PI; thetaY += PI / bottomToTopStrips) {
		textureX = 1.0;
		for (theta = -PI; theta < PI; theta += PI / (circChunks / 2.0)) {
			glTexCoord2d(textureX, textureY); glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
			glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips)); glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
			textureX -= 1.0 / circChunks;
		}
		glTexCoord2d(textureX, textureY); glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
		glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips)); glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left

		textureY -= 1.0 / bottomToTopStrips;
	}
	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

float rotationAngle = 0.0;
void draw11() {
	double r = 1.0;
	double deltaY = .15;
	double theta = 0.0;
	double textureX = 1.0;
	double textureY = 1.0;
	double bottomToTopStrips = 16.0;
	double circChunks = 32.0;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(0.0, 1.0f, 1.0f, 1.0f);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	rotationAngle++;
	glBegin(GL_QUAD_STRIP);
	for (double thetaY = 0.0; thetaY < PI; thetaY += PI / bottomToTopStrips) {
		textureX = 1.0;
		for (theta = -PI; theta < PI; theta += PI / (circChunks / 2.0)) {
			glTexCoord2d(textureX, textureY); glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
			glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips)); glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left
			textureX -= 1.0 / circChunks;
		}
		glTexCoord2d(textureX, textureY); glVertex3d(r * cos(theta) * sin(thetaY), r * cos(thetaY), r * sin(theta) * sin(thetaY)); //bottom left
		glTexCoord2d(textureX, (textureY - 1.0 / bottomToTopStrips)); glVertex3d(r * cos(theta) * sin(thetaY + PI / bottomToTopStrips), r * cos(thetaY + PI / bottomToTopStrips), r * sin(theta) * sin(thetaY + PI / bottomToTopStrips)); //bottom left

		textureY -= 1.0 / bottomToTopStrips;
	}
	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void drawCube(double r = .5) {
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

double distanceAway = 0;

void explodeCube(double r) {
	r = r / 3.0;
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

	r = r * 9 * distanceAway;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //draw a wireframe
	glBegin(GL_QUAD_STRIP);
	double y = sin(.05) * r;
	for (double i = 0; i < 2.0 * PI; i += PI / 32.0) {
		glVertex3f(cos(i) * r, cos(i) * y, sin(i) * r);
		glVertex3f(cos(i) * (r * 1.2), cos(i) * y, sin(i) * r * 1.2);
	}
	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void draw12() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_TEXTURE_2D);

	glColor3f(255.0, 204.0, 102.0);
	explodeCube(1);
	distanceAway += .01;

	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}