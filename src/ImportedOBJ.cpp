#include "ImportedOBJ.h"

#include <vector>
#include <glm/glm.hpp>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

ImportedOBJ::ImportedOBJ(char * objPath)
: objTexture(0), scaleFactor(.5), hasTexture(false), texWidth(1024),
texHeight(1024), x(1.75), y(.7), z(1.75), initialized(false)
{ 
	pathToObj = objPath;
}

ImportedOBJ::ImportedOBJ(char * objPath, char * texPath)
: objTexture(0), scaleFactor(.5), hasTexture(true), texWidth(1024),
texHeight(1024), x(-1.75), y(.7), z(-1.75), initialized(false)
{
	pathToObj = objPath; 
	pathToTexture = texPath;
}

void ImportedOBJ::draw() {
	if (!initialized) {
		init();
		initialized = true;
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glTranslatef(x, y, z);
	glRotatef(40, 0, 1, 0);

	if (hasTexture)	
		glBindTexture(GL_TEXTURE_2D, objTexture);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i++) {
		if (hasTexture)
			glTexCoord2f(uvs[i].x, uvs[i].y);
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(scaleFactor * vertices[i].x, scaleFactor * vertices[i].y, scaleFactor * vertices[i].z);
	}
	glEnd();

	glTranslatef(-x, -y, -z);

	//glPolygonMode(GL_FRONT_AND_BACK, GLU_FILL);
}

bool ImportedOBJ::loadOBJ()
{
	printf("Loading OBJ file %s...\n", pathToObj);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file;
	fopen_s(&file, pathToObj, "rb");
	if (file == NULL){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			//uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			uvIndex[0] = 0;
			uvIndex[1] = 0;
			uvIndex[2] = 0;
			if (hasTexture) {
				int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9){
					printf("File can't be read by our simple parser :-( Try exporting with other options (9)\n");
					return false;
				}
			}
			else {
				int matches = fscanf_s(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
				if (matches != 6){
					printf("File can't be read by our simple parser :-( Try exporting with other options (6)\n");
					return false;
				}
			}
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++){

		if (!hasTexture) {
			unsigned int vertexIndex = vertexIndices[i];
		}
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		this->vertices.push_back(vertex);
		this->normals.push_back(normal);

		if (hasTexture) {
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			this->uvs.push_back(uv);
		}

	}

	return true;
}

void ImportedOBJ::loadDeathStarTexture()
{
	unsigned char * data;
	FILE * file;
	fopen_s(&file, pathToTexture, "rb");

	if (file == NULL) return;
	data = (unsigned char *)malloc(texWidth * texHeight * 3);
	fread(data, texWidth * texHeight * 3, 1, file);
	fclose(file);

	for (int i = 0; i < texWidth * texHeight; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}
	glGenTextures(1, &objTexture);
	glBindTexture(GL_TEXTURE_2D, objTexture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texWidth, texHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
}

void ImportedOBJ::init() {
	loadOBJ();
	if (hasTexture)	
		loadDeathStarTexture();
}