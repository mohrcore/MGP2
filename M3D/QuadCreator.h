#pragma once

#include <GL/glew.h>
#include "Util.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shaders.h"

class QuadCreator
{
public:

	QuadCreator();
	~QuadCreator();

private:

	void prepareDefaultQuad();

	void draw(const Rect2d & rect, Texture & texture, StaticShader & shader, Rect2d uv_crop, Vec2f r_offset);

	GLuint _q_vboID, _q_eboID, _q_vaoID; ///DefaultQuad (used for rendering 2D planes that do not have their own VBO's and VAO's)
};

