#pragma once

#include <string>
#include <GL/glew.h>

#include <MFiles.h>

#include "GMesh3d.h"
#include "GfxModel3d.h"
#include "GTexture2d.h"
#include "ResourceManager.h"

namespace m3dfw
{
	class GMesh3dLoader
	{
	public:

		GMesh3dLoader();
		~GMesh3dLoader();

		bool loadGMesh3dFromMOB_Mesh(GMesh3d & target, mfile::MOB_GMesh3d & mesh);
		void createTestQuad(GMesh3d & target, float left, float top, float right, float bottom, unsigned int shader_id); //creates simple quad mesh for testing purpouses

	private:

		void prepareObject(GMesh3d & target); //clears and generates all the needed vbo's and vao's.

		void uploadVertexData(GMesh3d & target, const void * data, unsigned int size);
		void uploadElementData(GMesh3d & target, const void * data, unsigned int size);

		void generateGLStuff(GMesh3d & target);

		Vertex _d_quad_v[4]; //hardcoded default quad vertex data
		GLuint _d_quad_i[6]; //hardcoded default quad index data
	};

	class GfxModel3dLoader
	{
	public:

		GfxModel3dLoader(ResourceManager & rm);
		//~GfxModel3dLoader();

		bool loadGfxModel3dFromMOB_Model(GfxModel3d & target, mfile::MOB_Model3d & model);

		GMesh3dLoader gmesh_loader;

	private:

		//void clearModel(GfxModel3d & target);

		ResourceManager & _rm;
	};
}

