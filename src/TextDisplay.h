
class TextDisplay {
private:
	void setOrthographicProjection(float height, float width);
	void restorePerspectiveProjection();
	void renderBitmapString(float x, float y, float z, const char *string);
	void *font;

	char * framesPerSecond;
	char * cameraPos;
	char * simulationSpeed;
	char * planetSizeScaleFactor;
	char * planetDisplayInfo;
public:
	TextDisplay();

	bool showPlanetInfo;

	void setFramesPerSecond(float fps);
	void setCameraPos(float x, float y, float z);
	void setSimSpeed(double speed);
	void setPlanetSizeScaleFactor(double scale);
	void setPlanetDisplayInfo(char *param) { planetDisplayInfo = param; };

	void display(float height, float width);
};