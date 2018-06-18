#pragma once

#include "Util.h"

struct Vertex
{
	Vec3f pos;
	Vec2f uv;
	Vec3f normal;

	Vertex(Vec3f position, Vec2f uv_, Vec3f normal_);
	Vertex();
};