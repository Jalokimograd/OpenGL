#pragma once
#include "Drawer.h"

class SailDrawer : public Drawer
{
public:
	SailDrawer();
	void setParameters(float rotationSail, glm::vec3 scaleSail) { sailRotation = rotationSail; scale = scaleSail; }
	void draw(ShaderProgram &sh);

private:
	float sailRotation = -90.0f;
	glm::vec3 scale;

	void transform(GLuint trsansformLoc, glm::mat4 &trans, int j, glm::mat4 *rotationsCube) override;

	GLfloat vertices[6 * 8] = {
		// coordinates			// normal			// texture
		0.0f, 0.0f, 0.05f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		-2.0f, 0.0f, 0.05f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		0.0f, 2.0f, 0.05f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,

		0.0f, 0.0f, -0.05f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f,
		-2.0f, 0.0f, -0.05f,	0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
		0.0f, 2.0f, -0.05f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
	};

	GLuint cubeIndices[8 * 3] = {
			0, 1, 2,
			3, 4, 5,
			0, 2, 3,
			2, 3, 5,
			1, 2, 4,
			2, 4, 5,
			0, 1, 3,
			1, 3, 4,
	};

	glm::vec3 cubePositions[2] = {
		glm::vec3(0 * step,  0.7 * step, 1.2f * step),
		glm::vec3(0 * step, 3 * step, 3.5f * step),
	};

	glm::mat4 rotationsCube[2]{
		rotate(_trans, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		rotate(_trans, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
	};

	DrawInfo objectDefinition = {
		vertices, sizeof(vertices),
		cubeIndices, sizeof(cubeIndices),
		cubePositions, sizeof(cubePositions),
		rotationsCube, sizeof(rotationsCube)
	};
};

