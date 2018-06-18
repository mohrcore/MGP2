#include <M3DFW.h>

#include "EXPORT.h"

//RenderConfiguration struct unwrap

m3dfw::RenderMode EXPORT m3dfw__RenderConfiguration_render_mode(m3dfw::RenderConfiguration * ptr)
{
	return ptr->render_mode;
}

m3dfw::ShID EXPORT m3dfw__RenderConfiguration_shading_program(m3dfw::RenderConfiguration * ptr)
{
	return ptr->shading_program;
}

//RenderGroupConfigUnion union unwrap

m3dfw::RGID EXPORT m3dfw__RenderGroupConfigUnion_group(m3dfw::RenderGroupConfigUnion * ptr)
{
	return ptr->group;
}

m3dfw::RenderConfiguration PTR_EXPORT(*) m3dfw__RenderGroupConfigUnion_config(m3dfw::RenderGroupConfigUnion * ptr)
{
	return ptr->config;
}


//RenderConfigInfo struct unwrap

m3dfw::RenderConfigInfo PTR_EXPORT(*) m3dfw__new__RenderConfigInfo()
{
	return new m3dfw::RenderConfigInfo();
}

m3dfw::RenderConfigInfo PTR_EXPORT(*) m3dfw__new__RenderConfigInfo(const m3dfw::RenderConfiguration * r_cfg)
{
	return new m3dfw::RenderConfigInfo(*r_cfg);
}

m3dfw::RenderConfigInfo PTR_EXPORT(*) m3dfw__new__RenderConfigInfo(m3dfw::RGID * group_id)
{
	return new m3dfw::RenderConfigInfo(*group_id);
}

void EXPORT m3dfw__delete__RenderCOnfigInfo(m3dfw::RenderConfigInfo * ptr)
{
	delete ptr;
}

m3dfw::RenderConfigMode EXPORT m3dfw__RenderConfigInfo_mode(m3dfw::RenderConfigInfo * ptr)
{
	return ptr->mode;
}

m3dfw::RenderGroupConfigUnion EXPORT m3dfw__RenderConfigInfo_config_union(m3dfw::RenderConfigInfo * ptr)
{
	return ptr->config_union;
}