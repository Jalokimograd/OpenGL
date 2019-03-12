#include "HullDrawer.h"

HullDrawer::HullDrawer()
{
	allocate(objectDefinition);
}

void HullDrawer::draw(ShaderProgram &sh)
{
	render(sh, objectDefinition);
}
