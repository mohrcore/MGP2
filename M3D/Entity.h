#pragma once

#include <GL/glew.h>

#include "Util.h"
#include "Model3d.h"

class Entity
{
public:
	Entity();
	~Entity();

	Model3d model;

	Vec3f position, scale, rotation;

	void rotate(Vec3f angle);
	void move(Vec3f vec);

	//void setTransformationMatrixID(GLuint id);

private:

	GLuint _tmID;
};