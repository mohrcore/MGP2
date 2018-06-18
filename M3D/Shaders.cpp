#include <GL/glew.h>

#include "GLSLProgram.h"
#include "Matrix.h"
#include "Entity.h"
#include "EntityM.h"

#include "Shaders.h"



StaticShader::StaticShader() : _s2d_count(1)
{
	//temp_m.create(4, 4, true); //Create matrix for temporary calculations
	temp_m.identity();
}


StaticShader::~StaticShader()
{
}


void StaticShader::setEmbeddedUniforms(Entity & e)
{
	temp_m.identity();

	temp_m *= tm.scale(e.scale);
	temp_m *= tm.rotate(e.rotation);
	setTransformationMatrix(temp_m * tm.translate(e.position));

	//Set values for Sampler2D's. these will correspond with GL_TEXTURE0 + n 's.
	for (int i = 0; i < _s2d_count; i++)
		setSampler2d(i, i);
}

void StaticShader::setEmbeddedUniforms(EntityM & e)
{
	temp_m.identity();

	temp_m *= tm.scale(e.scale);
	temp_m *= tm.rotate(e.rotation);
	setTransformationMatrix(temp_m * tm.translate(e.position));

	//Set values for Sampler2D's. these will correspond with GL_TEXTURE0 + n 's.
	for (int i = 0; i < _s2d_count; i++)
		setSampler2d(i, i);
}

void StaticShader::setTransformationMatrix(Mat4 & mat)
{
	glUniformMatrix4fv(_tmID, 1, GL_FALSE, &mat(0, 0));
}

void StaticShader::setProjectionMatrix(Mat4 & mat)
{
	glUniformMatrix4fv(_pmID, 1, GL_TRUE, &mat(0, 0));
}

void StaticShader::setViewMatrix(Mat4 & mat)
{
	glUniformMatrix4fv(_vmID, 1, GL_FALSE, &mat(0, 0));
}

void StaticShader::setUvOffset(Vec2f offset)
{
	glUniform2f(_uvID, offset.x, offset.y);
}

void StaticShader::setRepeatOffset(Vec2f offset)
{
	if (offset.x == 0 || offset.y == 0)
	{
		glUniform1i(_uvr_sID, GL_FALSE);
	}
	else
	{
		glUniform1i(_uvr_sID, GL_TRUE);
		glUniform2f(_uvrID, offset.x, offset.y);
	}
}

void StaticShader::setUvCrop(Vec2f crop)
{
	glUniform2f(_uvcID, crop.x, crop.y);
}

void StaticShader::link()
{
	GLSLProgram::link();

	_tmID = glGetUniformLocation(_programID, "transformation_matrix");
	_pmID = glGetUniformLocation(_programID, "projection_matrix");
	_vmID = glGetUniformLocation(_programID, "view_matrix");
	_s2dID[0] = glGetUniformLocation(_programID, "diffuse_map");
	_uvID = glGetUniformLocation(_programID, "uv_offset");
	_uvcID = glGetUniformLocation(_programID, "uv_crop");
	_uvrID = glGetUniformLocation(_programID, "br_margin");
	_uvr_sID = glGetUniformLocation(_programID, "br_margin_set");
	bind();
	glUniform1f(_uvr_sID, GL_FALSE);
	unbind();
}

void StaticShader::setSampler2d(int no, int value)
{
	glUniform1i(_s2dID[no], value);
}


void StaticShader_PPL::setLightning(LightSource & light)
{
	glUniform3f(_lpID, light.position.x, light.position.y, light.position.z);
}

void StaticShader_PPL::link()
{
	StaticShader::link();
	_lpID = glGetUniformLocation(_programID, "light_pos");
}


void DistanceFieldTextShader::link()
{
	StaticShader::link();

	_coID = glGetUniformLocation(_programID, "color");
	_thID = glGetUniformLocation(_programID, "thickness");
}

void DistanceFieldTextShader::setThickness(float value)
{
	glUniform1f(_thID, value);
}

void DistanceFieldTextShader::setColor(Color value)
{
	glUniform4f(_coID, (float)value.r / 256.0f, (float)value.g / 256.0f, (float)value.b / 256.0f, (float)value.a / 256.0f);
}