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

class WaterDrawer : public Drawer
{
public:
	WaterDrawer();
	virtual void draw(ShaderProgram &sh);

private:
	float waterStep = 1.0;

	GLfloat vertices[8*6] = {
		// coordinates			// color			// texture
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

	};

	GLuint cubeIndices[2 * 3] = {
			0, 1, 2,
			0, 2, 3,
	};

	glm::vec3 cubePositions[1] = {
		glm::vec3(10.0f,  10.0f,  10.0f),

	};


	DrawInfo objectDefinition = {
		vertices, sizeof(vertices),
		cubeIndices, sizeof(cubeIndices),
		cubePositions, sizeof(cubePositions)
	};

	void render(ShaderProgram &sh, DrawInfo &info);
};

