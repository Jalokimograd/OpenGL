#pragma once
#include "Drawer.h"

#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class HullDrawer : public Drawer
{
public:
	HullDrawer();
	void draw(ShaderProgram &sh);

private:
	GLfloat vertices[8*6] = {
		// coordinates				// normal				// texture
		0.5f,  0.5f,  0.5f,			0.0f, 0.0f, 1.0f,		1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,		-1.0f, -1.0f, 0.0f,		1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,			-1.0f, -1.0f, 0.0f,		1.0f,  0.0f,

		0.5f,  0.5f,  -0.5f,		0.0f, 0.0f, -1.0f,		0.0f,  1.0f,
		-0.5f,  0.5f,  -0.5f,		-1.0f, -1.0f, 0.0f,		0.0f,  1.0f,
		0.5f, -0.5f,  -0.5f,		-1.0f, -1.0f, 0.0f,		0.0f,  0.0f,
	};

	GLuint cubeIndices[3*8] {
		0, 1, 2,
		3, 4, 5,
		1, 2, 5,
		1, 5, 4,
		0, 2, 5,
		0, 5, 3,
		0, 1, 3,
		1, 3, 4,
	};

	glm::vec3 cubePositions[12] = {
		glm::vec3(-1 * step, -1 * step, 1 * step),
		glm::vec3(-1 * step, -1 * step, 2 * step),
		glm::vec3(-1 * step, -1 * step, 3 * step),
		glm::vec3(-1 * step, -1 * step, 4 * step),
		glm::vec3(-1 * step, -1 * step, 5 * step),
		glm::vec3(-1 * step, -1 * step, 6 * step),
		glm::vec3(1 * step, -1 * step, 1 * step),
		glm::vec3(1 * step, -1 * step, 2 * step),
		glm::vec3(1 * step, -1 * step, 3 * step),
		glm::vec3(1 * step, -1 * step, 4 * step),
		glm::vec3(1 * step, -1 * step, 5 * step),
		glm::vec3(1 * step, -1 * step, 6 * step),
	};

	glm::mat4 rotationsCube[12] = {
		rotate(_trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		rotate(_trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		rotate(_trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		rotate(_trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		rotate(_trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		rotate(_trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),

		rotate(_trans, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		rotate(_trans, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		rotate(_trans, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		rotate(_trans, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		rotate(_trans, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		rotate(_trans, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
	};

	DrawInfo objectDefinition = {
		vertices, sizeof(vertices),
		cubeIndices, sizeof(cubeIndices),
		cubePositions, sizeof(cubePositions),
		rotationsCube, sizeof(rotationsCube)
	};
};

