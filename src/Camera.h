#include "Planet.h"

class Camera {
private:
	float camAngle;
	float camHeightAngle;
	float camRadius;
	float camX;
	float camY;
	float camZ;

	float centerX;
	float centerY;
	float centerZ;

	float incAmount;
public:
	Camera();
	void getCamera();
	void display() { getCamera(); };

	void setIncrementAmount(float param) { incAmount = param; };
	void setCameraCenter(Planet * planet);
	void setCameraCenter(float x, float y, float z);

	void zoomIn();
	void zoomOut();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();

	//getters
	float getCamX() { return camX; };
	float getCamY() { return camY; };
	float getCamZ() { return camZ; };
	float getRadius() { return camRadius; };
};