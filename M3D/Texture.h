#pragma once

#include <GL/glew.h>
#include <string>

#include "Util.h"

enum __texture_type
{
	DIFFUSE_MAP,
	SPECULAR_MAP
};

class Texture
{
public:
	Texture();
	Texture(const Texture & arg);
	~Texture();

	void loadFromFile(std::string path, __texture_type type);
	void clear();

	//Texture & operator=(const Texture & arg);

	GLuint getID();
	__texture_type getType();

private:

	GLuint _id;
	__texture_type _type;

	bool empty;

	int _w, _h;
};

