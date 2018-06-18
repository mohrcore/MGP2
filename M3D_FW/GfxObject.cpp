#include "GfxObject.h"



m3dfw::GfxObject::GfxObject(m3dfw::Resource<m3dfw::GfxModel3d> & model_r) : model(model_r), scale(1.0f, 1.0f, 1.0f) /*: _active_r_config(NULL)*/
{
}


m3dfw::GfxObject::~GfxObject()
{
}

//void m3dfw::GfxObject::setActiveRenderConfiguration(unsigned int id)
//{
//	_active_r_config = id;
//}
//
//unsigned int m3dfw::GfxObject::getActiveRenderConfigurationID() const
//{
//	return _active_r_config;
//}