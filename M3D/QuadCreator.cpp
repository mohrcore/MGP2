#include "QuadCreator.h"



QuadCreator::QuadCreator()
{
	prepareDefaultQuad();
}

QuadCreator::~QuadCreator()
{
}


void QuadCreator::prepareDefaultQuad()
{
	Vertex vd[4];
	GLuint id[6] = { 0, 3, 1, 1, 3, 2 };

	vd[0].pos = Vec3f(0.0f, 0.0f, -1.0f);
	vd[1].pos = Vec3f(1.0f, 0.0f, -1.0f);
	vd[2].pos = Vec3f(1.0f, 1.0f, -1.0f);
	vd[3].pos = Vec3f(0.0f, 1.0f, -1.0f);

	vd[0].uv = Vec2f(0.0f, 0.0f);
	vd[1].uv = Vec2f(1.0f, 0.0f);
	vd[2].uv = Vec2f(1.0f, 1.0f);
	vd[3].uv = Vec2f(0.0f, 1.0f);


	glGenBuffers(1, &_q_vboID);
	glGenBuffers(1, &_q_eboID);
	glGenVertexArrays(1, &_q_vaoID);

	//Uploading data to GPU
	glBindVertexArray(_q_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, _q_vboID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vd, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _q_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), id, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}