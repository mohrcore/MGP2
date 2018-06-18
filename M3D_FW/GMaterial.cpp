#include "GMaterial.h"



m3dfw::GMaterial::GMaterial(m3dfw::ShaderManager & sm) : _sm(sm)
{
}

m3dfw::GMaterial::GMaterial(const m3dfw::GMaterial & other) : _sm(other._sm), _program(other._program), _tmatrix(other._tmatrix), _time(other._time), _textures_cnt(other._textures_cnt), _textures(nullptr)
{
	_textures = copyResourceArray(other._textures_cnt, other._textures);
}

m3dfw::GMaterial::~GMaterial()
{
	clear();
}

m3dfw::GMaterial & m3dfw::GMaterial::operator=(const m3dfw::GMaterial & other)
{
	_program = other._program;
	_tmatrix = other._tmatrix;
	_time = other._time;
	_textures_cnt = other._textures_cnt;
	_textures = copyResourceArray(other._textures_cnt, other._textures);

	return *this;
}

bool m3dfw::GMaterial::setProgram(m3dfw::ShID id)
{
	_program = id;

	auto & prog = _sm.getProgram(id);

	_tmatrix = prog.getUniformHandle("transformation_matrix");
	if (_tmatrix == -1)
		return false;

	_wstmatrix = prog.getUniformHandle("ws_transformation_matrix");
	if (_wstmatrix == -1)
		return false;

	_ambient = prog.getUniformHandle("ambient");
	if (_ambient == -1)
		return false;

	_time = prog.getUniformHandle("time");
	_lights_pos = prog.getUniformHandle("lights_pos");
	_lights_col = prog.getUniformHandle("lights_col");
	_lights_cnt = prog.getUniformHandle("lights_cnt");
}

bool m3dfw::GMaterial::setTexture(unsigned int id, m3dfw::Resource<m3dfw::GTexture2d> texture)
{
	if (id >= _textures_cnt)
		return false;

	_textures[id] = texture;

	return true;
}

void m3dfw::GMaterial::setTextureCount(unsigned int cnt)
{
	if (_textures != nullptr)
		delete[] _textures;

	if (cnt == 0)
		return;

	_textures = M3DFW_createInitializedResourceArray(cnt, GTexture2d);

	_textures_cnt = cnt;
}

m3dfw::ShID m3dfw::GMaterial::getProgramID() const
{
	return _program;
}

m3dfw::Resource<m3dfw::GTexture2d> & m3dfw::GMaterial::getTexture(unsigned int id)
{
	return _textures[id];
}

unsigned int m3dfw::GMaterial::getTextureCount() const
{
	return _textures_cnt;
}

GLint m3dfw::GMaterial::getUniformLocation(const char * name) const
{
	return _sm.getProgram(_program).getUniformHandle(name);
}

GLuint m3dfw::GMaterial::getTransformationMatrixLocation() const
{
	return _tmatrix;
}

GLuint m3dfw::GMaterial::getWorldSpaceTransformationMatrixLocation() const
{
	return _wstmatrix;
}

GLuint m3dfw::GMaterial::getTimeLocation() const
{
	return _time;
}

GLuint m3dfw::GMaterial::getLightsPositionsLocation() const
{
	return _lights_pos;
}

GLuint m3dfw::GMaterial::getLightsColorsLocation() const
{
	return _lights_col;
}

GLuint m3dfw::GMaterial::getLightsCountLocation() const
{
	return _lights_cnt;
}

GLuint m3dfw::GMaterial::getAmbientLocation() const
{
	return _ambient;
}

void m3dfw::GMaterial::clear()
{
	if (_textures != nullptr)
	{
		delete[] _textures;
		_textures = nullptr;
	}

	_textures_cnt = 0;
}