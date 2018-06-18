#pragma once

#include "GTexture2d.h"


namespace m3dfw
{
	enum TextureLoaderFlags : unsigned int
	{
		RGB = 0,
		RGBA = 1,
		NOLINFILTER = 2
	};

	class GTexture2dLoader
	{
	public:

		GTexture2dLoader();
		~GTexture2dLoader();

		bool loadTextureFromSDLSurface(GTexture2d & target, void * surf_ptr, char flags = TextureLoaderFlags::RGB);
	};
}


