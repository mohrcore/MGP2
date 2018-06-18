#pragma once

#include <Gl/glew.h>

#include "Shaders.h"
#include "Camera.h"
#include "Mesh.h"
#include "EntityM.h"
#include "Sprite.h"

#define DQ_MODE_TOPLEFT 0
#define DQ_MODE_CENTER 1

class Renderer
{
public:
	Renderer();
	~Renderer();

	//void renderEntity(Entity & e, StaticShader & shader);
	void renderMesh(Mesh & m, StaticShader & shader);
	void renderEntityM(EntityM & e, StaticShader & shader);
	void renderRect2d(const Rect2d & rect, Texture & texture, StaticShader & shader);
	void renderRect2d(const Rect2d & rect, Texture & texture, StaticShader & shader, Rect2d uv_crop, Vec2f r_offset);
	void renderSprite(const Sprite & sprite, StaticShader & shader);
	//void renderText

	void setProjectionMatrix(float fov, float Znear, float Zfar, float aspect_ratio);
	void setProjectionMatrix(float aspect_ratio); //Ortho, 2D
	void setProjectionMatrix(int width, int height); //For 2D usage, coordinates transformed to pixels

	void setOutputParameters(int display_width, int display_height);

	void setActiveCamera(Camera & cam);

private:


	Mat4 projectionMatrix;

	int d_w, d_h; ///Display width and height

	Camera * _cam;

	void r_mesh(Mesh & m); //render mesh without binding and setting up shader

	GLuint _q_vboID, _q_eboID, _q_vaoID; ///DefaultQuad (used for rendering 2D planes that do not have their own VBO's and VAO's)

	bool dquad_prepared;

	void prepareDefaultQuad(GLuint mode);
};

