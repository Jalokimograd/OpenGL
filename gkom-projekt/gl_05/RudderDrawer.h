#pragma once
#include "Drawer.h"
class RudderDrawer : public Drawer
{
public:
	RudderDrawer();
	void draw(ShaderProgram &sh);

private:
	GLfloat vertices[8 * 8] = {
		-0.25f, 0.25f, 0.25f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,
		-0.25f, -0.5f, 0.25f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,
		0.25f, -0.5f, 0.25f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		0.25f, 0.0f, 0.25f,		1.0f, 0.0f, 1.0f,	1.0f,  1.0f,

		-0.25f, 0.25f, -0.25f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,
		-0.25f, -0.5f, -0.25f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,
		0.25f, -0.5f, -0.25f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
		0.25f, 0.0f, -0.25f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,
	};

	GLuint cubeIndices[12 * 3] = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		2, 6, 3,
		6, 3, 7,
		1, 2, 5,
		2, 5, 6,
		0, 1, 5,
		0, 5, 4,
		0, 3, 7,
		0, 7, 4,
	};

	glm::vec3 cubePositions[1] = {
		glm::vec3(0 * step, -1 * step, 7 * step),
	};

	glm::mat4 rotationsCube[1] = {
		rotate(_trans, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
	};

	DrawInfo objectDefinition = {
		vertices, sizeof(vertices),
		cubeIndices, sizeof(cubeIndices),
		cubePositions, sizeof(cubePositions),
		rotationsCube, sizeof(rotationsCube)
	};
};

