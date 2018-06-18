#pragma once

#include <GL/glew.h>

#include "CommonTypes.h"
#include "GTexture2d.h"

namespace m3dfw
{
	struct Vertex
	{
		Vertex();
		Vertex(const Vec3f & v_pos, const Vec2f & v_uv, const Vec3f & v_normal);

		Vec3f position;
		Vec2f uv;
		Vec3f normal;
	};

	struct GMesh3d
	{
	public:

		GMesh3d();
		~GMesh3d();

		void clear();

		void fill(); //Disables _empty flag.
		bool empty();

		unsigned int v_count, i_count; //number of vertices, number of indices
		GLuint vaoID, vboID, eboID;

	private:

		bool _empty;
	};
}


