#pragma once

#include "GfxObject.h"
#include "Camera3d.h"
#include "GfxLight.h"
#include "Matrix.h"
#include "ShaderManager.h"
#include "Resource.h"
#include "MemoryManagement.h"
#include "List.h"

#include <GL\glew.h>

namespace m3dfw
{
	class O3DRendererGL
	{
	public:

		O3DRendererGL(ShaderManager & sh_mngr);
		~O3DRendererGL();

		void render(const GfxObject & object, const Camera3d & camera, const m3dfw::List<GfxBasicLight> & lights);

		void renderTestQuadMat(const GMaterial & material);

		void setProjectionMatrix(float fov, float z_near, float z_far, float aspect_ratio);

	private:

		GLuint _tq_vao, _tq_vbo, _tq_ebo;

		void generateTQ();
		void deleteTQ();

		void prepareTransformationMatrix(Mat4 & target, const GfxObject & object, const Camera3d & camera) const;
		void prepareWorldSpaceTransformationMatrix(Mat4 & target, const GfxObject & object) const;

		void renderMesh(const GMesh3d & mesh) const;
		void renderMeshWireframe_D(const GMesh3d & mesh) const;

		void bindTextures(Resource<GMaterial> material) const;

		void uploadLightData(const GMaterial & material, const m3dfw::List<GfxBasicLight> & lights);

		m3dfw::StaticStackAllocator _uniformarray_alloc;

		Mat4 _projection;

		ShaderManager & _sh_mngr;

		ShID _current_prog;
	};
}
