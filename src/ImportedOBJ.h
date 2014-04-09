#ifndef IMPORTEDOBJ_H
#define IMPORTEDOBJ_H

#include <vector>
#include <glm/glm.hpp>

class ImportedOBJ
{
public:
	//constructer constructs stuff before GL initilization
	ImportedOBJ(char * objPath);
	ImportedOBJ(char * objPath, char * texPath);

	void draw();

	float getScaleFactor() { return scaleFactor; };
	glm::vec3 getPos() { return glm::vec3(x, y, z); };

	void setScaleFactor(float param) { scaleFactor = param; };
	void setPos(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };
	void setPos(glm::vec3 param) { x = param.x; y = param.y; z = param.z; };
private:
	bool loadOBJ();
	void loadDeathStarTexture();

	//for stuff after GL intitilization
	void init();
	bool initialized;

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;

	char * pathToObj;
	char * pathToTexture;
	
	bool hasTexture;
	int texWidth;
	int texHeight;

	unsigned int objTexture;

	float scaleFactor;
	float x;
	float y;
	float z;
};

#endif