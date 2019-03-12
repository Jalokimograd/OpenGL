#include "WorldDrawer.h"

WorldDrawer::WorldDrawer()
{
	allocate(objectDefinition);
}

void WorldDrawer::draw(ShaderProgram &sh)
{
	render(sh, objectDefinition);
}

void WorldDrawer::render(ShaderProgram &sh, DrawInfo &info)
{
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void WorldDrawer::allocate(DrawInfo & info)
{
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);			//przechowuje atrybuty wierzcho³ków
	glBufferData(GL_ARRAY_BUFFER, info.verticesSize, info.vertices, GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
}

