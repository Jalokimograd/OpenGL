#include "SailDrawer.h"




SailDrawer::SailDrawer()
{
	allocate(objectDefinition);
}

void SailDrawer::draw(ShaderProgram &sh)
{
	DrawInfo objectDefinition = {
		vertices, sizeof(vertices),
		cubeIndices, sizeof(cubeIndices),
		cubePositions, sizeof(cubePositions),
		rotationsCube, sizeof(rotationsCube)
	};
	render(sh, objectDefinition);
}

void SailDrawer::transform(GLuint transformLoc, glm::mat4 &trans, int j, glm::mat4 *rotationsCube)
{
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), scale);

	if (j == 0)
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans * (rotationsCube[j] + rotate(_trans, glm::radians(sailRotation), glm::vec3(0.0f, 1.0f, 0.0f)))));
	else if (j == 1)
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans * rotationsCube[j] * Model));
	else
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans * rotationsCube[j]));
}