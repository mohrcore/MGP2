#include "GLSLProgram.h"



GLSLProgram::GLSLProgram()
{
}


GLSLProgram::~GLSLProgram()
{
	glDeleteShader(_vshID);
	glDeleteShader(_fshID);
	glDeleteProgram(_programID);
}


void GLSLProgram::vertSource(const std::string & path)
{
	_vert_src = path;
}

void GLSLProgram::fragSource(const std::string & path)
{
	_frag_src = path;
}

void GLSLProgram::compileShader(GLuint shader, const std::string & source)
{
	//Compiling vertex shader
	const char * tmp = source.c_str();
	glShaderSource(shader, 1, &tmp, nullptr);
	glCompileShader(shader);
	//Checking if compilation was successful
	GLint c_success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &c_success);
	if (c_success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(shader); // Don't leak the shader.

		fatal_error("GLSL shader failed to compile.\nError log:\n-----\n" + std::string(&errorLog[0]));
	}
}


void GLSLProgram::compile()
{
	_programID = glCreateProgram();
	if (_programID == 0)
		fatal_error("Could not create GLSL program");

	_vshID = glCreateShader(GL_VERTEX_SHADER);
	if (_vshID == 0)
		fatal_error("Could not create vertex shader");

	_fshID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fshID == 0)
		fatal_error("Could not create fragment shader");

	std::string file_content, line;

	std::ifstream sh_file;

	sh_file.open(_vert_src);
	if (sh_file.fail())
		fatal_error("Could not open file: " + _vert_src);

	while (std::getline(sh_file, line))
		file_content += line + "\n";

	sh_file.close();

	compileShader(_vshID, file_content);

	file_content.clear();

	sh_file.open(_frag_src);
	if (sh_file.fail())
		fatal_error("Could not open file: " + _frag_src);

	while (std::getline(sh_file, line))
		file_content += line + "\n";

	sh_file.close();

	compileShader(_fshID, file_content);

	file_content.clear();
}

void GLSLProgram::bindAttribute(int no, const std::string & name)
{
	glBindAttribLocation(_programID, no, name.c_str());
	attribarrays.push_back(no);
}

void GLSLProgram::link()
{
	glAttachShader(_programID, _vshID);
	glAttachShader(_programID, _fshID);
	GLint is_linked;
	glLinkProgram(_programID);
	glGetProgramiv(_programID, GL_LINK_STATUS, &is_linked);
	if (is_linked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vshID);
		glDeleteShader(_fshID);

		//Use the infoLog as you see fit.

		fatal_error("Failed to link GLSL shaders to shader program");
	}

	glDetachShader(_programID, _vshID);
	glDetachShader(_programID, _fshID);
}

void GLSLProgram::bind()
{
	glUseProgram(_programID);
	for (int i = 0; i < attribarrays.size(); i++)
		glEnableVertexAttribArray(attribarrays[i]);
}

void GLSLProgram::unbind()
{
	glUseProgram(0);
	for (int i = 0; i < attribarrays.size(); i++)
		glDisableVertexAttribArray(attribarrays[i]);
}

void GLSLProgram::uniform(std::string name, float v1)
{
	glUniform1f(glGetUniformLocation(_programID, name.c_str()), v1);
}

void GLSLProgram::uniform(std::string name, float v1, float v2)
{
	glUniform2f(glGetUniformLocation(_programID, name.c_str()), v1, v2);
}

void GLSLProgram::uniform(std::string name, float v1, float v2, float v3)
{
	glUniform3f(glGetUniformLocation(_programID, name.c_str()), v1, v2, v3);
}

void GLSLProgram::uniform(std::string name, float v1, float v2, float v3, float v4)
{
	glUniform4f(glGetUniformLocation(_programID, name.c_str()), v1, v2, v3, v4);
}

void GLSLProgram::uniform(std::string name, int count, GLboolean transpose, GLfloat * data)
{
	glUniformMatrix4fv(glGetUniformLocation(_programID, name.c_str()), count, transpose, data);
}

GLuint GLSLProgram::getUniform(std::string name)
{
	return glGetUniformLocation(_programID, name.c_str());
}