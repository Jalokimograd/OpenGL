#include "WaterDrawer.h"

WaterDrawer::WaterDrawer()
{
	allocate(objectDefinition);
}

void WaterDrawer::draw(ShaderProgram &sh)
{
	render(sh, objectDefinition);
}

void WaterDrawer::render(ShaderProgram &sh, DrawInfo &info)
{
	glBindVertexArray(VAO[0]);
	int size = 100;
	int middle = size / 2;

	vertices[0] += 1;
	vertices[1] += 1;
	vertices[2] += 1;

	for (int j = 0; j<size; ++j) {
		for (int i = 0; i<size; ++i) {

			glm::mat4 trans = _trans;
			trans = glm::translate(trans, glm::vec3(waterStep * (i - middle), -2, waterStep * (j - middle)));

			GLuint transformLoc = glGetUniformLocation(sh.get_programID(), "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

			glDrawElements(GL_TRIANGLES, info.cubeIndicesSize, GL_UNSIGNED_INT, 0);
		}
	}
	glBindVertexArray(0);
}