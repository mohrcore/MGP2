#pragma once

#include "Util.h"
#include "Vertex.h"
#include "Matrix.h"

class F_Renderer
{
public:

	F_Renderer();
	~F_Renderer();

	void renderData(GLuint vaoID, GLuint eboID, GLuint * texID, unsigned int ind_count, unsigned int tex_count);
};

