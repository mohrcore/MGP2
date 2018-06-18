#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Util.h"

#include "Texture.h"



Texture::Texture() : empty(true)
{
}

Texture::Texture(const Texture & arg)
{
	_w = arg._w;
	_h = arg._h;

	GLubyte * data = new GLubyte[arg._w * arg._h];

	glBindTexture(GL_TEXTURE_2D, arg._id);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)data);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	empty = false();
}

Texture::~Texture()
{
	clear();
}


void Texture::loadFromFile(std::string path, __texture_type type)
{
	SDL_Surface * texsurf;

	texsurf = IMG_Load(path.c_str());
	if (texsurf == NULL)
		fatal_error("Error opening file: " + path + "\n" + IMG_GetError());

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texsurf->w, texsurf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texsurf->pixels);
	//Linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	_w = texsurf->w;
	_h = texsurf->h;

	//Free memory
	SDL_FreeSurface(texsurf);

	_type = type;

	empty = false();
}

//Texture & Texture::operator=(const Texture & arg)
//{
//	clear();
//
//	_w = arg._w;
//	_h = arg._h;
//
//	char * data = new char[arg._w * arg._h];
//
//	//glBindTexture(GL_TEXTURE_2D, arg._id);
//	glGetTextureImage(arg._id, 0, GL_RGBA, GL_BYTE, arg._w * arg._h, (void *)data);
//	//glBindTexture(GL_TEXTURE_2D, 0);
//
//	glGenTextures(1, &_id);
//	glBindTexture(GL_TEXTURE_2D, _id);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_BYTE, (void *)data);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	empty = false();
//
//	delete[] data;
//
//	return *this;
//}

GLuint Texture::getID()
{
	return _id;
}

__texture_type Texture::getType()
{
	return _type;
}

void Texture::clear()
{
	if (!empty)
	{
		glDeleteTextures(1, &_id);
		empty = true;
	}
}