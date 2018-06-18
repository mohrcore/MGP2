#include <Gl/glew.h>

#include "Shaders.h"
#include "Camera.h"
#include "Mesh.h"

#include "Renderer.h"



Renderer::Renderer() : dquad_prepared(false)
{
	prepareDefaultQuad(DQ_MODE_TOPLEFT);

	//projectionMatrix.create(4, 4, false);
	projectionMatrix.identity();
}


Renderer::~Renderer()
{
	if (dquad_prepared)
	{
		glDeleteVertexArrays(1, &_q_vaoID);
		glDeleteBuffers(1, &_q_vboID);
		glDeleteBuffers(1, &_q_eboID);
	}
}


void Renderer::prepareDefaultQuad(GLuint mode)
{
	Vertex vd[4];
	GLuint id[6] = { 0, 3, 1, 1, 3, 2 };

	switch (mode)
	{
	case DQ_MODE_TOPLEFT:

		vd[0].pos = Vec3f(0.0f, 0.0f, -1.0f);
		vd[1].pos = Vec3f(1.0f, 0.0f, -1.0f);
		vd[2].pos = Vec3f(1.0f, 1.0f, -1.0f);
		vd[3].pos = Vec3f(0.0f, 1.0f, -1.0f);
		break;

	case DQ_MODE_CENTER:

		vd[0].pos = Vec3f(-0.5f, 0.5f, -1.0f);
		vd[1].pos = Vec3f(0.5f, 0.5f, -1.0f);
		vd[2].pos = Vec3f(0.5f, -0.5f, -1.0f);
		vd[3].pos = Vec3f(-0.5f, -0.5f, -1.0f);
		break;
	}

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

	dquad_prepared = true;

}

//void Renderer::renderEntity(Entity & e, StaticShader & shader)
//{
//	shader.bind();
//	shader.setEmbeddedUniforms(e);
//	shader.setProjectionMatrix(projectionMatrix);
//	shader.setViewMatrix(_cam->viewMatrix());
//
//	glBindVertexArray(e.model.getVAOID());
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, e.model.getTextureID());
//	glDrawElements(GL_TRIANGLES, e.model.getIndiciesCount(), GL_UNSIGNED_INT, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glActiveTexture(0);
//	glBindVertexArray(0);
//
//	shader.unbind();
//}

void Renderer::renderMesh(Mesh & m, StaticShader & shader)
{
	Mat4 tm;
	tm.identity();

	shader.bind();
	shader.setProjectionMatrix(projectionMatrix);
	shader.setViewMatrix(_cam->viewMatrix());
	shader.setTransformationMatrix(tm);

	r_mesh(m);

	shader.unbind();
}

void Renderer::renderEntityM(EntityM & e, StaticShader & shader)
{
	shader.bind();
	shader.setProjectionMatrix(projectionMatrix);
	shader.setViewMatrix(_cam->viewMatrix());
	shader.setUvOffset(Vec2f(0.0f, 0.0f));
	shader.setEmbeddedUniforms(e);

	for (int i = 0; i < e.meshes.size(); i++)
	{
		r_mesh(e.meshes[i]);
	}

	shader.unbind();
}

void Renderer::renderRect2d(const Rect2d & rect, Texture & texture, StaticShader & shader, Rect2d uv_crop, Vec2f r_offset)
{
	TransformationMatrix4 rect_tm;
	Mat4 rect_m;
	rect_m.identity();

	rect_m *= rect_tm.scale(Vec3f(rect.right, rect.bottom, 1.0f));
	rect_m *= rect_tm.translate(Vec3f(rect.left, rect.top, 0.0f));

	//Rendering
	shader.bind();
	shader.setTransformationMatrix(rect_m);
	shader.setSampler2d(0, 0);
	shader.setProjectionMatrix(projectionMatrix);
	shader.setViewMatrix(_cam->viewMatrix());
	shader.setUvOffset(Vec2f(uv_crop.left, uv_crop.top));
	shader.setUvCrop(Vec2f(uv_crop.right, uv_crop.bottom));
	shader.setRepeatOffset(r_offset);

	glBindVertexArray(_q_vaoID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
	glBindVertexArray(0);

	shader.unbind();
}

void Renderer::renderRect2d(const Rect2d & rect, Texture & texture, StaticShader & shader)
{
	renderRect2d(rect, texture, shader, Rect2d(0.0f, 0.0f, 0.0f, 0.0f), Vec2f(0.0f, 0.0f));
}

void Renderer::renderSprite(const Sprite & sprite, StaticShader & shader)
{
	shader.bind();
	shader.setUvOffset(Vec2f(sprite.getCropRect().left, sprite.getCropRect().top));
	shader.setRepeatOffset(Vec2f(sprite.getCropRect().right, sprite.getCropRect().bottom));
	renderRect2d(sprite.getRect2d(), *sprite.getTexture(), shader, sprite.getCropRect(), sprite.getRepeats());
	shader.unbind();
}

void Renderer::setProjectionMatrix(float fov, float Znear, float Zfar, float aspect_ratio)
{
	float tan_fov_2 = std::tan(fov / 2.0f);

	projectionMatrix.zero();

	projectionMatrix(0, 0) = 1.0f / (tan_fov_2 * aspect_ratio);
	projectionMatrix(1, 1) = 1.0f / tan_fov_2;
	projectionMatrix(2, 2) = -((Zfar + Znear) / (Zfar - Znear));
	projectionMatrix(3, 2) = -1.0f;
	projectionMatrix(2, 3) = -((2.0f * Zfar * Znear) / (Zfar - Znear));

	//projectionMatrix.identity();
}

void Renderer::setProjectionMatrix(float aspect_ratio)
{
	projectionMatrix.identity();

	projectionMatrix(0, 0) = 1.0f / aspect_ratio;
}

void Renderer::setProjectionMatrix(int width, int height)
{
	projectionMatrix(0, 0) = 2.0f / ((float)width);
	projectionMatrix(1, 1) = -2.0f / ((float)height);
	projectionMatrix(0, 3) = -1.0f;
	projectionMatrix(1, 3) = 1.0f;
}

void Renderer::setOutputParameters(int display_width, int display_height)
{
	d_w = display_width;
	d_h = display_height;
}

void Renderer::setActiveCamera(Camera & cam)
{
	_cam = &cam;
}

void Renderer::r_mesh(Mesh & m)
{
	glBindVertexArray(m.getVAOID());

	for (int i = 0; i < m.getTextureCount(); i++) //Binding textures
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m.textures[i]->getID());
	}

	glDrawElements(GL_TRIANGLES, m.getIndicesCount(), GL_UNSIGNED_INT, 0);

	for (int i = 0; i < m.getTextureCount(); i++) //Unbinding textures
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glActiveTexture(0);
	glBindVertexArray(0);
}