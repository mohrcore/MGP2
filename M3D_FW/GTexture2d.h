#pragma once

#include <GL/glew.h>


namespace m3dfw
{
	struct GTexture2d
	{
	public:

		GTexture2d();
		~GTexture2d();

		GLuint id;

		char * src_path;
	};
}


