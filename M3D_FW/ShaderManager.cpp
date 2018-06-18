#include "ShaderManager.h"

//#include <stdexcept>


m3dfw::ShaderManager::ShaderManager() : _max_id(0), _bound_prog(0xFFFFFFFF)
{
}

m3dfw::ShaderManager::~ShaderManager()
{
}

void m3dfw::ShaderManager::unbindProgram()
{
	//if (_bound_prog == 0xFFFFFFFF)
	//	return;

	//GLSLProgram & prog = _programs[_bound_prog];

	glUseProgram(0);

	//for (int i = 0; i < prog.attrib_array.size(); i++)
	//	glDisableVertexAttribArray(prog.attrib_array[i]);

	//_bound_prog = 0xFFFFFFFF;
}

m3dfw::ShID m3dfw::ShaderManager::loadProgram(const std::string & v_src, const std::string & f_src, const std::string & name)
{
	ShID id = generateNewShaderID();

	

	if (!_programs[id].compileFromSrc(v_src, f_src))
		throw ShaderManagerExceptions::ShaderCompilationFailedException;

	_name_to_id[name] = id;

	return id;
}

void m3dfw::ShaderManager::deleteProgram(m3dfw::ShID id)
{
	_programs.erase(id);
}

void m3dfw::ShaderManager::clear()
{
	_programs.clear();
	_name_to_id.clear();

	_max_id = 0;
}

m3dfw::GLSLProgram & m3dfw::ShaderManager::getProgram(m3dfw::ShID id)
{
	return _programs[id];
}

m3dfw::ShID m3dfw::ShaderManager::getID(const std::string & name)
{
	return _name_to_id[name];
}

m3dfw::ShID m3dfw::ShaderManager::generateNewShaderID()
{
	_max_id++;
	return _max_id;
}

bool m3dfw::ShaderManager::isShaderAvaible(const std::string & name) const
{
	if (_name_to_id.count(name) == 0)
		return false;

	return true;
}


m3dfw::GLSLProgram::GLSLProgram() : _id(NULL), _error(GLSLProgramErrorEnum::None, "No program loaded"), _compiled(false), _stack_alloc1(128), _good(true)
{
}

m3dfw::GLSLProgram::~GLSLProgram()
{
	clear();
}

//m3dfw::GLSLProgramCompatibility m3dfw::ShaderManager::deepCompatibilityCompare(m3dfw::GLSLProgram & key, m3dfw::GLSLProgram & candidate)
//{
//	m3dfw::GLSLProgramParseInfo & key_i = key.programInfo;
//	m3dfw::GLSLProgramParseInfo & candidate_i = candidate.programInfo;
//
//	if (key_i.getInCount() != candidate_i.getInCount())
//		return m3dfw::GLSLProgramCompatibility::NONE;
//
//	unsigned int i_cnt = key_i.getInCount();
//
//	for (unsigned int i = 0; i < i_cnt; i++)
//		if (key_i.getIn(i).type != candidate_i.getIn(i).type)
//			return m3dfw::GLSLProgramCompatibility::NONE;
//
//
//
//}

// SHIT
void m3dfw::GLSLProgram::generateShCK()
{
	_shck = 0;

	int in_cnt = _programInfo.getInCount() % 32;
	int uni_cnt = _programInfo.getUniformCount() % 32;

	_shck += in_cnt;
	_shck += uni_cnt * 32;

	int e = 2;

	for (int i = 0; i < max(in_cnt, 4); i++)
	{
		_shck += (ShCK)_programInfo.getIn(i).type * intPow<ShCK>(32, e);
		e++;
	}

	for (int i = 0; i < max(uni_cnt, 4); i++)
	{
		_shck += (ShCK)_programInfo.getUniform(i).type * intPow<ShCK>(32, e);
		e++;
	}

	//Final value!
	_shck += (((ShCK)_programInfo.getIn(_programInfo.getInCount() - 1).type + (ShCK)_programInfo.getUniform(_programInfo.getUniformCount() - 1).type) % 32) * intPow<ShCK>(32, e);
}

m3dfw::ShCK m3dfw::GLSLProgram::getShaderCompatibilityKey() const
{
	return _shck;
}

void m3dfw::GLSLProgram::bind() const
{
	glUseProgram(_id);

	for (unsigned int i = 0; i < _programInfo.getInCount(); i++)
		glEnableVertexAttribArray(i);
}

m3dfw::GLSL_UniHandle m3dfw::GLSLProgram::getUniformHandle(const std::string & name) const
{
	try
	{
		return _uniforms.at(name);
	}
	catch (std::out_of_range)
	{
		return -1;
	}
}

void m3dfw::GLSLProgram::setUniformFloat(m3dfw::GLSL_UniHandle loc, float val) const
{
	glUniform1f(loc, val);
}

void m3dfw::GLSLProgram::setUniformVec2(m3dfw::GLSL_UniHandle loc, m3dfw::Vec2f val) const
{
	glUniform2f(loc, val.x, val.y);
}

void m3dfw::GLSLProgram::setUniformVec3(m3dfw::GLSL_UniHandle loc, m3dfw::Vec3f val) const
{
	glUniform3f(loc, val.x, val.y, val.z);
}

void m3dfw::GLSLProgram::setUniformVec4(m3dfw::GLSL_UniHandle loc, m3dfw::Vec4f val) const
{
	glUniform4f(loc, val.x, val.y, val.z, val.w);
}

void m3dfw::GLSLProgram::setUniformInt(m3dfw::GLSL_UniHandle loc, int val) const
{
	glUniform1i(loc, val);
}

void m3dfw::GLSLProgram::setUniformMat2(m3dfw::GLSL_UniHandle loc, const float * data) const
{
	glUniformMatrix2fv(loc, 1, GL_TRUE, data);
}

void m3dfw::GLSLProgram::setUniformMat3(m3dfw::GLSL_UniHandle loc, const float * data) const
{
	glUniformMatrix3fv(loc, 1, GL_TRUE, data);
}

void m3dfw::GLSLProgram::setUniformMat4(m3dfw::GLSL_UniHandle loc, const float * data) const
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}

void m3dfw::GLSLProgram::setUniformSampler2D(m3dfw::GLSL_UniHandle loc, unsigned int value) const
{
	glUniform1i(loc, value);
}

void m3dfw::GLSLProgram::setUniformArrFloat(m3dfw::GLSL_UniHandle loc, const std::vector<float> & data)
{
	glUniform1fv(loc, data.size(), &data[0]);
}

void m3dfw::GLSLProgram::setUniformArrVec2(m3dfw::GLSL_UniHandle loc, const std::vector<m3dfw::Vec2f> & data)
{
	float * cdata = _stack_alloc1.alloc<float>(data.size() * 2);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		cdata[i * 2] = data[i].x;
		cdata[i * 2 + 1] = data[i].y;
	}

	glUniform2fv(loc, data.size(), cdata);

	_stack_alloc1.dealloc(cdata);
}

void m3dfw::GLSLProgram::setUniformArrVec3(m3dfw::GLSL_UniHandle loc, const std::vector<m3dfw::Vec3f> & data)
{
	float * cdata = _stack_alloc1.alloc<float>(data.size() * 3);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		cdata[i * 3] = data[i].x;
		cdata[i * 3 + 1] = data[i].y;
		cdata[i * 3 + 2] = data[i].z;
	}

	glUniform3fv(loc, data.size(), cdata);

	_stack_alloc1.dealloc(cdata);
}

void m3dfw::GLSLProgram::setUniformArrVec4(m3dfw::GLSL_UniHandle loc, const std::vector<m3dfw::Vec4f> & data)
{
	float * cdata = _stack_alloc1.alloc<float>(data.size() * 4);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		cdata[i * 4] = data[i].x;
		cdata[i * 4 + 1] = data[i].y;
		cdata[i * 4 + 2] = data[i].z;
		cdata[i * 4 + 3] = data[i].w;
	}

	glUniform4fv(loc, data.size(), cdata);

	_stack_alloc1.dealloc(cdata);
}

void m3dfw::GLSLProgram::setUniformArrVec2(m3dfw::GLSL_UniHandle loc, const float * data, unsigned int count)
{
	glUniform2fv(loc, count, data);
}

void m3dfw::GLSLProgram::setUniformArrVec3(m3dfw::GLSL_UniHandle loc, const float * data, unsigned int count)
{
	glUniform3fv(loc, count, data);
}

void m3dfw::GLSLProgram::setUniformArrVec4(m3dfw::GLSL_UniHandle loc, const float * data, unsigned int count)
{
	glUniform4fv(loc, count, data);
}

m3dfw::GLSLProgramCompatibility m3dfw::GLSLProgram::compare(const m3dfw::GLSLProgram & other) const
{
	if (_shck != other._shck)
		return NONE;

	return EVERYTHING;
}

bool m3dfw::GLSLProgram::compileFromSrc(const std::string & v_src, const std::string & f_src)
{
	std::ifstream stream;

	unsigned int vsz, fsz;
	char * vsrc, * fsrc;
	
	if (!extractSrc(v_src, vsrc, vsz))
	{
		_good = false;
		_error = GLSLProgramError(GLSLProgramErrorEnum::ErrorOpeningFile_Vertex, "Error opening file: \"" + v_src + "\"");
		return false;
	}

	if (!extractSrc(f_src, fsrc, fsz))
	{
		_good = false;
		_error = GLSLProgramError(GLSLProgramErrorEnum::ErrorOpeningFile_Fragment, "Error opening file: \"" + v_src + "\"");
		return false;
	}

	if (!compile(vsrc, fsrc, vsz, fsz))
	{
		fatalError("GLSL compilation error: " + getError().details);
		return false;
	}

	_programInfo.clear();

	_programInfo.parse(v_src, GLSLParseMode::ParseUniform | GLSLParseMode::ParseIn);
	_programInfo.parse(f_src, GLSLParseMode::ParseUniform);

	for (unsigned int i = 0; i < _programInfo.getInCount(); i++)
		bindAttrib(i, _programInfo.getIn(i).name.c_str());

	if (!link())
	{
		fatalError("GLSL linking error: " + getError().details);
		return false;
	}

	for (unsigned int i = 0; i < _programInfo.getUniformCount(); i++)
		_uniforms[_programInfo.getUniform(i).name] = glGetUniformLocation(_id, _programInfo.getUniform(i).name.c_str());

	_compiled = true;

	return true;
}

void m3dfw::GLSLProgram::bindAttrib(GLuint id, const char * name)
{
	glBindAttribLocation(_id, id, name);
}

bool m3dfw::GLSLProgram::compile(const char * v_src, const char * f_src, unsigned int vsz, unsigned int fsz)
{
	GLuint vsh = glCreateShader(GL_VERTEX_SHADER);
	GLuint fsh = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vsh, 1, (GLchar * *)&v_src, (GLint *)&vsz);
	glCompileShader(vsh);

	GLint compiled = 0;

	glGetShaderiv(vsh, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint loglength = 0;
		glGetShaderiv(vsh, GL_INFO_LOG_LENGTH, &loglength);
		char * log = new char[loglength];
		glGetShaderInfoLog(vsh, loglength, &loglength, log);
		glDeleteShader(vsh);
		glDeleteShader(fsh);

		_good = false;
		_error = GLSLProgramError(GLSLProgramErrorEnum::ShaderCompilationError_Vertex, "GLSL vertex shader compilation error.\nCompilation log:\n-----\n" + std::string(log) + "\n-----");

		delete log;

		return false;
	}

	glShaderSource(fsh, 1, (GLchar * *)&f_src, (GLint *)&fsz);
	glCompileShader(fsh);

	glGetShaderiv(fsh, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint loglength = 0;
		glGetShaderiv(fsh, GL_INFO_LOG_LENGTH, &loglength);
		char * log = new char[loglength];
		glGetShaderInfoLog(fsh, loglength, &loglength, log);
		glDeleteShader(vsh);
		glDeleteShader(fsh);

		_good = false;
		_error = GLSLProgramError(GLSLProgramErrorEnum::ShaderCompilationError_Fragment, "GLSL fragment shader compilation error.\nCompilation log:\n-----\n" + std::string(log) + "\n-----");

		delete log;

		return false;
	}

	_id = glCreateProgram();
	glAttachShader(_id, vsh);
	glAttachShader(_id, fsh);

	_vshID = vsh;
	_fshID = fsh;

	_good = true;
	return true;
}

bool m3dfw::GLSLProgram::link()
{
	glLinkProgram(_id);

	GLint linked = 0;

	glGetProgramiv(_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint loglength = 0;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &loglength);
		char * log = new char[loglength];
		glGetProgramInfoLog(_id, loglength, &loglength, log);
		glDeleteProgram(_id);
		glDeleteShader(_vshID);
		glDeleteShader(_fshID);

		_good = false;
		_error = GLSLProgramError(GLSLProgramErrorEnum::ProgramLinkingError, "GLSL program linking error.\nLinker log:\n-----" + std::string(log) + "\n-----");

		delete log;

		return false;
	}

	glDetachShader(_id, _vshID);
	glDetachShader(_id, _fshID);

	_good = true;
	return true;
}

bool m3dfw::GLSLProgram::extractSrc(const std::string & path, char * & target, unsigned int & len) const
{
	std::ifstream stream;

	stream.open(path);

	if (!stream.good())
		return false;

	len = getFileSize(stream);
	target = new char[len + 1];
	stream.read(target, len);
	target[len] = '\0';
	stream.close();
}

void m3dfw::GLSLProgram::clear()
{
	if (!_compiled)
		return;

	GLenum error = glGetError();

	glDeleteProgram(_id);
	error = glGetError();
	glDeleteShader(_vshID);
	error = glGetError();
	glDeleteShader(_fshID);
	error = glGetError();

	_compiled = false;
	_good = true;
}

bool m3dfw::GLSLProgram::good() const
{
	return _good;
}

bool m3dfw::GLSLProgram::compiled() const
{
	return _compiled;
}

const m3dfw::GLSLProgramError & m3dfw::GLSLProgram::getError()
{
	return _error;
}

const m3dfw::GLSLProgramParseInfo & m3dfw::GLSLProgram::getInfo()
{
	return _programInfo;
}

m3dfw::GLSLProgramError::GLSLProgramError()
{
}

m3dfw::GLSLProgramError::GLSLProgramError(m3dfw::GLSLProgramErrorEnum t, const std::string & d) : type(t), details(d)
{
}