#include <M3DFW.h>

#include "EXPORT.h"

//GLSLProgramError struct unwrap

m3dfw::GLSLProgramError PTR_EXPORT(*) m3dfw__new__GLSLProgramError()
{
	return new m3dfw::GLSLProgramError();
}

m3dfw::GLSLProgramError PTR_EXPORT(*) m3dfw__new__GLSLProgramError(m3dfw::GLSLProgramErrorEnum * t, const char * d)
{
	return new m3dfw::GLSLProgramError(*t, d);
}

m3dfw::GLSLProgramErrorEnum EXPORT m3dfw__GLSLProgramError_type(m3dfw::GLSLProgramError * ptr)
{
	return ptr->type;
}

const char PTR_EXPORT(*) m3dfw__GLSLProgramError_details(m3dfw::GLSLProgramError * ptr)
{
	return ptr->details.c_str();
}

//GLSLProgram class unwrap

m3dfw::GLSLProgram PTR_EXPORT(*) m3dfw__new__GLSLProgram()
{
	return new m3dfw::GLSLProgram();
}

void EXPORT m3dfw__delete__GLSLProgram(m3dfw::GLSLProgram * ptr)
{
	delete ptr;
}

bool EXPORT m3dfw__GLSLProgram_complileFromSrc(m3dfw::GLSLProgram * ptr, const char * v_src, const char * f_src)
{
	return ptr->compileFromSrc(v_src, f_src);
}

void EXPORT m3dfw__GLSLProgram_clear(m3dfw::GLSLProgram * ptr)
{
	ptr->clear();
}

void EXPORT m3dfw__GLSLProgram_bind(m3dfw::GLSLProgram * ptr)
{
	ptr->bind();
}

m3dfw::GLSL_UniHandle EXPORT m3dfw__GLSLProgram_getUniformHandle(m3dfw::GLSLProgram * ptr, const char * name)
{
	return ptr->getUniformHandle(name);
}

void EXPORT m3dfw__GLSLProgram_setUniformFloat(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, float val)
{
	ptr->setUniformFloat(loc, val);
}

void EXPORT m3dfw__GLSLProgram_setUniformVec2(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, float x, float y)
{
	ptr->setUniformVec2(loc, m3dfw::Vec2f(x, y));
}

void EXPORT m3dfw__GLSLProgram_setUniformVec3(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, float x, float y, float z)
{
	ptr->setUniformVec3(loc, m3dfw::Vec3f(x, y, z));
}

void EXPORT m3dfw__GLSLProgram_setUniformVec4(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, float x, float y, float z, float w)
{
	ptr->setUniformVec4(loc, m3dfw::Vec4f(x, y, z, w));
}

void EXPORT m3dfw__GLSLProgram_setUniformInt(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, int val)
{
	ptr->setUniformInt(loc, val);
}

void EXPORT m3dfw__GLSLProgram_setUniformMat2(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc,const float * data)
{
	ptr->setUniformMat2(loc, data);
}

void EXPORT m3dfw__GLSLProgram_setUniformMat3(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, const float * data)
{
	ptr->setUniformMat3(loc, data);
}

void EXPORT m3dfw__GLSLProgram_setUniformMat4(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, const float * data)
{
	ptr->setUniformMat4(loc, data);
}

void EXPORT m3dfw__GLSLProgram_setUniformSampler2D(m3dfw::GLSLProgram * ptr, m3dfw::GLSL_UniHandle loc, unsigned int * value)
{
	ptr->setUniformSampler2D(loc, *value);
}

m3dfw::ShCK EXPORT m3wdf__GLSLProgram_getShaderCompatibilityKey(m3dfw::GLSLProgram * ptr)
{
	return ptr->getShaderCompatibilityKey();
}

m3dfw::GLSLProgramCompatibility EXPORT m3dfw__GLSLProgram_compare(m3dfw::GLSLProgram * ptr, m3dfw::GLSLProgram * other)
{
	return ptr->compare(*other);
}

m3dfw::GLSLProgramError EXPORT m3wdf__GLSLProgram_getError(m3dfw::GLSLProgram * ptr)
{
	return ptr->getError();
}

m3dfw::GLSLProgramParseInfo EXPORT m3wdf__GLSLProgram_getInfo(m3dfw::GLSLProgram * ptr)
{
	return ptr->getInfo();
}

bool EXPORT m3dfw__GLSLProgram_good(m3dfw::GLSLProgram * ptr)
{
	return ptr->good();
}

bool EXPORT m3dfw__GLSLProgram_compiled(m3dfw::GLSLProgram * ptr)
{
	return ptr->compiled();
}

//ShaderManager class unwrap

m3dfw::ShaderManager PTR_EXPORT(*) m3dfw__new__ShaderManager()
{
	return new m3dfw::ShaderManager;
}

void EXPORT m3dfw__delete__ShaderManager(m3dfw::ShaderManager * ptr)
{
	delete ptr;
}

void EXPORT m3df__ShaderManager_clear(m3dfw::ShaderManager * ptr)
{
	ptr->clear();
}

void EXPORT m3df__ShaderManager_ubindProgram(m3dfw::ShaderManager * ptr)
{
	ptr->unbindProgram();
}

m3dfw::ShID EXPORT m3dfw__ShaderManager_loadProgram(m3dfw::ShaderManager * ptr, const char * v_scr, const char * f_scr, const char * name)
{
	return ptr->loadProgram(v_scr, f_scr, name);
}

void EXPORT m3df__ShaderManager_deleteProgram(m3dfw::ShaderManager * ptr, m3dfw::ShID id)
{
	ptr->deleteProgram(id);
}

m3dfw::GLSLProgram PTR_EXPORT(*) m3dfw__ShaderManager_getProgram(m3dfw::ShaderManager * ptr, m3dfw::ShID id)
{
	return &ptr->getProgram(id);
}

m3dfw::ShID EXPORT m3dfw__ShaderManager__getID(m3dfw::ShaderManager * ptr, const char * name)
{
	return ptr->getID(name);
}

bool EXPORT m3dfw__ShaderManager__isShaderAvaible(m3dfw::ShaderManager * ptr, const char * name)
{
	return ptr->isShaderAvaible(name);
}