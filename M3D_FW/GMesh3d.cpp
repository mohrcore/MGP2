#include "GMesh3d.h"


m3dfw::Vertex::Vertex()
{
}

m3dfw::Vertex::Vertex(const m3dfw::Vec3f & v_pos, const Vec2f & v_uv, const Vec3f & v_normal) : position(v_pos), uv(v_uv), normal(v_normal)
{
}


m3dfw::GMesh3d::GMesh3d() : _empty(true)
{
}

m3dfw::GMesh3d::~GMesh3d()
{
	clear();
}


void m3dfw::GMesh3d::clear()
{
	if (_empty)
		return;

	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &vboID);
	glDeleteBuffers(1, &eboID);

	_empty = true;
}

void m3dfw::GMesh3d::fill()
{
	_empty = false;
}

bool m3dfw::GMesh3d::empty()
{
	return _empty;
}