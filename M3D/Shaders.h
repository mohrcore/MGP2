#pragma once

#include <GL/glew.h>

#include "GLSLProgram.h"
#include "Matrix.h"
#include "Entity.h"
#include "EntityM.h"
#include "Light.h"

class StaticShader
	: public GLSLProgram
{
public:

	StaticShader();
	~StaticShader();

	virtual void setEmbeddedUniforms(Entity & e);
	virtual void setEmbeddedUniforms(EntityM & e);

	void setTransformationMatrix(Mat4 & mat);
	void setProjectionMatrix(Mat4 & mat);
	void setViewMatrix(Mat4 & mat);
	void setSampler2d(int no, int value);
	void setUvOffset(Vec2f offset);
	void setUvCrop(Vec2f crop);
	void setRepeatOffset(Vec2f offset);

	virtual void link();

private:

	TransformationMatrix4 tm;

	Mat4 temp_m; //Matrix for temporary calculations to avoid additional dynamic allocations

	GLuint _tmID, _pmID, _vmID, _uvID, _uvcID, _uvrID, _uvr_sID;
	GLuint _s2dID[32]; ///sampler2d

	int _s2d_count; ///Number of sampler2d uniforms
};


class StaticShader_PPL
	: public StaticShader
{
public:

	void setLightning(LightSource & light);

	virtual void link();

private:

	GLuint _lpID;
};


class DistanceFieldTextShader
	: public StaticShader
{
	void setThickness(float value);
	void setColor(Color value);

	virtual void link();

private:

	GLuint _thID, _coID; ///thickness, color
};