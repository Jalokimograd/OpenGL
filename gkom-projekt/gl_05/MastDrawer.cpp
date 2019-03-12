#include "MastDrawer.h"

MastDrawer::MastDrawer()
{
	allocate(objectDefinition);
}

void MastDrawer::draw(ShaderProgram &sh)
{
	render(sh, objectDefinition);
}

void MastDrawer::render(ShaderProgram &sh, DrawInfo &info)
{
	glBindVertexArray(VAO[0]);
	for (unsigned int j = 0; j < info.cubePositionsSize / sizeof(info.cubePositions[0]); ++j) {
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 trans = _trans;

		trans = glm::translate(trans, info.cubePositions[j]);

		GLuint transformLoc = glGetUniformLocation(sh.get_programID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glDrawElements(GL_TRIANGLES, info.cubeIndicesSize, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}