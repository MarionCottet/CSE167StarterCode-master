#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

using namespace std;

class OBJObject
{
private:
	std::vector<unsigned int> indices;

public:
	OBJObject(const char* filepath);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;
	float angle;
	float pointSize;

	void parse(const char* filepath);
	void draw();
	void update();
	void spin(float);
	void changePointSize(float size);
	void translate(float x, float y, float z);
	void scale(float size);
	void orbit(float deg, float direction);
	void resetPosition();
	void resetOrientationScale();
};

#endif