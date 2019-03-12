#pragma once

#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct DrawInfo {
	GLfloat *vertices;
	unsigned int verticesSize;
	GLuint *cubeIndices = nullptr;
	unsigned int cubeIndicesSize = 0;
	glm::vec3 *cubePositions = nullptr;
	unsigned int cubePositionsSize = 0;
	glm::mat4 *rotationsCube = nullptr;
	unsigned int rotationsCubeSize = 0;
};

class Drawer
{
public:
	typedef void(Drawer::*transform_callback)(GLuint, glm::mat4&, glm::mat4&, int, glm::mat4*);
	Drawer();
	~Drawer();

	virtual void draw(ShaderProgram &sh) = 0;

protected:
	GLuint VBO[1]{ 0 }, EBO[1]{ 0 }, VAO[1]{ 0 };

	static glm::mat4 _trans;
	float step = 1.0;
	virtual void transform(GLuint transformLoc, glm::mat4 &trans, int j, glm::mat4 rotationsCube[]);
	void allocate(DrawInfo &info);
	void render(ShaderProgram &sh, DrawInfo &info);

};



