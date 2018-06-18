#include "GTexture2dLoader.h"


#include <SDL.h>
#include <GL/glew.h>


m3dfw::GTexture2dLoader::GTexture2dLoader()
{
}


m3dfw::GTexture2dLoader::~GTexture2dLoader()
{
}


bool m3dfw::GTexture2dLoader::loadTextureFromSDLSurface(m3dfw::GTexture2d & target, void * surf_ptr, char flags)
{
	GLenum fmt = GL_RGB;

	if (flags & TextureLoaderFlags::RGBA)
		fmt = GL_RGBA;

	SDL_Surface * surf = static_cast<SDL_Surface *>(surf_ptr);

	GLuint id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	//Linear filtering
	if (!(flags & TextureLoaderFlags::NOLINFILTER))
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surf->w, surf->h, 0, fmt, GL_UNSIGNED_BYTE, surf->pixels);

	target.id = id;

	return true;
}