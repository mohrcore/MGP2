#include "Init.h"

#include <GL\glew.h>

bool m3dfw::init()
{
	GLenum success = glewInit();

	if (success == GLEW_OK)
		return true;
	return false;
}