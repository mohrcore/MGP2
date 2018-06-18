#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <vector>

#include "Util.h"

class GLSLProgram
{
public:

	GLSLProgram();
	~GLSLProgram();

	void vertSource(const std::string & path);
	void fragSource(const std::string & path);

	void bindAttribute(int no, const std::string & name);

	GLuint getUniform(std::string name);

	void uniform(std::string name, float v1); //vec1
	void uniform(std::string name, float v1, float v2); //vec2
	void uniform(std::string name, float v1, float v2, float v3); //vec3
	void uniform(std::string name, float v1, float v2, float v3, float v4); //vec4
	void uniform(std::string name, int count, GLboolean transpose, GLfloat * data);


	void compile();
	virtual void link();

	void bind();
	void unbind();

protected:

	void compileShader(GLuint shader, const std::string & source);

	std::vector<GLuint> attribarrays;

	std::string _vert_src, _frag_src;

	GLuint _vshID, _fshID;
	GLuint _programID;
};

