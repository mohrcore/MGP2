#pragma once

#include <vector>

#include "Util.h"
#include "Mesh.h"

class EntityM
{
public:

	EntityM();
	~EntityM();

	std::vector<Mesh> meshes;

	Vec3f position, scale, rotation;

	void rotate(Vec3f angle);
	void move(Vec3f vec);

	void uploadData();

private:

	GLuint _tmID;
};

