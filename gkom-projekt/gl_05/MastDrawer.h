#pragma once

#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Drawer.h"

using namespace std;

class MastDrawer : public Drawer
{
public:
	MastDrawer();
	virtual void draw(ShaderProgram &sh);

private:
	GLfloat vertices[8*36] = {
		// coordinates			// color			// texture
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	GLuint cubeIndices[12 * 3] = {
			0, 1, 2,
			3, 4, 5,

			6, 7, 8,
			9, 10, 11,

			12, 13, 14,
			15, 16, 17,

			18, 19, 20,
			21, 22, 23,

			24, 25, 26,
			27, 28, 29,

			30, 31, 32,
			33, 34, 35,
	};

	glm::vec3 cubePositions[36] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(0 * step,  0 * step, 1 * step),
		glm::vec3(0 * step,  0 * step, 2 * step),
		glm::vec3(0 * step,  0 * step, 3 * step),
		glm::vec3(0 * step,  0 * step, 4 * step),
		glm::vec3(0 * step,  0 * step, 5 * step),
		glm::vec3(0 * step,  0 * step, 6 * step),

		glm::vec3(0 * step, -1 * step, 1 * step),
		glm::vec3(0 * step, -1 * step, 2 * step),
		glm::vec3(0 * step, -1 * step, 3 * step),
		glm::vec3(0 * step, -1 * step, 4 * step),
		glm::vec3(0 * step, -1 * step, 5 * step),
		glm::vec3(0 * step, -1 * step, 6 * step),

		glm::vec3(1 * step,  0 * step, 1 * step),
		glm::vec3(1 * step,  0 * step, 2 * step),
		glm::vec3(1 * step,  0 * step, 3 * step),
		glm::vec3(1 * step,  0 * step, 4 * step),
		glm::vec3(1 * step,  0 * step, 5 * step),
		glm::vec3(1 * step,  0 * step, 6 * step),

		glm::vec3(-1 * step,  0 * step, 1 * step),
		glm::vec3(-1 * step,  0 * step, 2 * step),
		glm::vec3(-1 * step,  0 * step, 3 * step),
		glm::vec3(-1 * step,  0 * step, 4 * step),
		glm::vec3(-1 * step,  0 * step, 5 * step),
		glm::vec3(-1 * step,  0 * step, 6 * step),

		glm::vec3(0 * step,  1 * step, 6 * step),
		glm::vec3(1 * step,  1 * step, 6 * step),
		glm::vec3(-1 * step,  1 * step, 6 * step),
		glm::vec3(0 * step,  1 * step, 5 * step),
		glm::vec3(1 * step,  1 * step, 5 * step),
		glm::vec3(-1 * step,  1 * step, 5 * step),


		glm::vec3(0 * step,  1 * step, 3 * step),
		glm::vec3(0 * step,  2 * step, 3 * step),
		glm::vec3(0 * step,  3 * step, 3 * step),
		glm::vec3(0 * step,  4 * step, 3 * step),
		glm::vec3(0 * step,  5 * step, 3 * step),
	};


	DrawInfo objectDefinition = {
		vertices, sizeof(vertices),
		cubeIndices, sizeof(cubeIndices),
		cubePositions, sizeof(cubePositions)
	};

	void render(ShaderProgram &sh, DrawInfo &info);
};

