#pragma once

#include <vector>
//#include <string>

#include <GL/glew.h>

#include "ShaderManager.h"
#include "GLSLProgramParseInfo.h"
#include "GTexture2d.h"
#include "Resource.h"

namespace m3dfw
{
	class GMaterial
	{
	public:

		GMaterial(ShaderManager & sm);
		GMaterial(const GMaterial & other);
		~GMaterial();

		GMaterial & operator=(const GMaterial & other);

		bool setProgram(ShID id);
		bool setTexture(unsigned int id, Resource<GTexture2d> texture);
		void setTextureCount(unsigned int cnt);

		ShID getProgramID() const;
		Resource<GTexture2d> & getTexture(unsigned int id);
		unsigned int getTextureCount() const;

		GLint getUniformLocation(const char * name) const;

		//Set of standard uniforms
		GLuint getTransformationMatrixLocation() const;
		GLuint getWorldSpaceTransformationMatrixLocation() const;
		GLuint getTimeLocation() const;
		GLuint getLightsPositionsLocation() const;
		GLuint getLightsColorsLocation() const;
		GLuint getLightsCountLocation() const;
		GLuint getAmbientLocation() const;

		void clear();

	private:

		//GLuint _unibuff;

		Resource<GTexture2d> * _textures;
		unsigned int _textures_cnt;

		ShID _program;

		GLint _tmatrix, _wstmatrix, _ambient;
		GLint _time, _lights_pos, _lights_col, _lights_cnt;

		ShaderManager & _sm;
	};
}


