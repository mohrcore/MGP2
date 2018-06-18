#include <M3DFW.h>

#include "EXPORT.h"

m3dfw::GfxObject PTR_EXPORT(*) m3dfw__new__GfxObject(m3dfw::Resource<m3dfw::GfxModel3d> * model_r)
{
	return new m3dfw::GfxObject(*model_r);
}

void m3dfw__delete__GfxObject(m3dfw::GfxObject * o_ptr)
{
	delete o_ptr;
}

m3dfw::Resource<m3dfw::GfxModel3d> PTR_EXPORT(*) m3dfw__GfxObject_Get_model(m3dfw::GfxObject * o_ptr)
{
	return &o_ptr->model;
}

m3dfw::Vec3f PTR_EXPORT(*) m3dfw__GfxObject_Get_position(m3dfw::GfxObject * o_ptr)
{
	return &o_ptr->position;
}

m3dfw::Vec3f PTR_EXPORT(*) m3dfw__GfxObject_Get_rotation(m3dfw::GfxObject * o_ptr)
{
	return &o_ptr->rotation;
}

m3dfw::Vec3f PTR_EXPORT(*) m3dfw__GfxObject_Get_scale(m3dfw::GfxObject * o_ptr)
{
	return &o_ptr->scale;
}

void m3dfw__GfxObject_Set_model(m3dfw::GfxObject * o_ptr, m3dfw::Resource<m3dfw::GfxModel3d> * value)
{
	o_ptr->model = *value;
}

void m3dfw__GfxObject_Set_position(m3dfw::GfxObject * o_ptr, m3dfw::Vec3f * value)
{
	o_ptr->position = *value;
}

void m3dfw__GfxObject_Set_rotation(m3dfw::GfxObject * o_ptr, m3dfw::Vec3f * value)
{
	o_ptr->rotation = *value;
}

void m3dfw__GfxObject_Set_scale(m3dfw::GfxObject * o_ptr, m3dfw::Vec3f * value)
{
	o_ptr->scale = *value;
}