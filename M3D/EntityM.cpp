#include <vector>

#include "Util.h"
#include "Mesh.h"

#include "EntityM.h"



EntityM::EntityM() : position(Vec3f(0.0f, 0.0f, 0.0f)), rotation(Vec3f(0.0f, 0.0f, 0.0f)), scale(Vec3f(1.0f, 1.0f, 1.0f))
{
}


EntityM::~EntityM()
{
	meshes.clear();
}


void EntityM::rotate(Vec3f angle)
{
	rotation += angle;
}

void EntityM::move(Vec3f vec)
{
	position += vec;
}

void EntityM::uploadData()
{
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].uploadData();
}