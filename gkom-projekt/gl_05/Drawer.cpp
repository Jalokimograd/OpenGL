#include "Drawer.h"

glm::mat4 Drawer::_trans;

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
	if (VAO[0] != 0)
		glDeleteVertexArrays(1, VAO);
	if (VBO[0] != 0)
		glDeleteBuffers(1, VBO);
	if (EBO[0] != 0)
		glDeleteBuffers(1, EBO);
}

void Drawer::transform(GLuint transformLoc, glm::mat4 & trans, int j, glm::mat4 rotationsCube[])
{
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans * rotationsCube[j]));
}

void Drawer::allocate(DrawInfo & info)
{
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);			//przechowuje atrybuty wierzcho³ków
	glBufferData(GL_ARRAY_BUFFER, info.verticesSize, info.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);	//przechowuje indeksy do wierzcho³ków
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.cubeIndicesSize, info.cubeIndices, GL_STATIC_DRAW);


	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
}

void Drawer::render(ShaderProgram &sh, DrawInfo &info)
{
	glBindVertexArray(VAO[0]);
	for (unsigned int j = 0; j < info.cubePositionsSize / sizeof(info.cubePositions[0]); ++j) {
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 trans = _trans;

		trans = glm::translate(trans, info.cubePositions[j]);

		GLuint transformLoc = glGetUniformLocation(sh.get_programID(), "transform");
		transform(transformLoc, trans, j, info.rotationsCube);

		glDrawElements(GL_TRIANGLES, info.cubeIndicesSize, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}
