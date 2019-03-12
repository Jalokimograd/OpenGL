#include "RudderDrawer.h"


RudderDrawer::RudderDrawer()
{
	allocate(objectDefinition);
}

void RudderDrawer::draw(ShaderProgram &sh)
{
	render(sh, objectDefinition);
}
