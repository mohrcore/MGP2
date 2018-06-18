#include <M3DFW.h>

#include "EXPORT.h"

m3dfw::O3DRendererGL PTR_EXPORT(*) m3dfw__new__O3DRendererGL(m3dfw::ShaderManager * sm)
{
	return new m3dfw::O3DRendererGL(*sm);
}

void EXPORT m3dfw__delete__O3DRendererGL(m3dfw::O3DRendererGL * o_ptr)
{
	delete o_ptr;
}

void EXPORT m3dfw__O3DRendererGL_render(m3dfw::O3DRendererGL * o_ptr, m3dfw::GfxObject * object, const m3dfw::Camera3d * camera, const std::vector<m3dfw::GfxBasicLight> * lights)
{
	o_ptr->render(*object, *camera, *lights);
}

void EXPORT m3dfw__O3DRendererGL_setProjectionMatrix(m3dfw::O3DRendererGL * o_ptr, float fov, float z_near, float z_far, float aspect_ratio)
{
	o_ptr->setProjectionMatrix(fov, z_near, z_far, aspect_ratio);
}