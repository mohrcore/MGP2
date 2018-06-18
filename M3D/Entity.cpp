#include <GL/glew.h>

#include "Model3d.h"
#include "Util.h"

#include "Entity.h"



Entity::Entity() : position(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rotation(0.0f, 0.0f, 0.0f)
{
}


Entity::~Entity()
{
}


void Entity::rotate(Vec3f angle)
{
	rotation += angle;
}

void Entity::move(Vec3f vec)
{
	position += vec;
}