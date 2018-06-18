#include <M3DFW.h>

#include "EXPORT.h"

//RenderGroup class unwrap

m3dfw::RenderConfiguration EXPORT m3dfw__RenderGroup_config(m3dfw::RenderGroup * ptr)
{
	return ptr->config;
}

//RenderGroups class unwrap

m3dfw::RenderGroups PTR_EXPORT(*) m3dfw__new__RenderGroups(unsigned int rendergroups_count = __M3DFWINT_DEFAULT_RENDERGROUPS_COUNT)
{
	return new m3dfw::RenderGroups(rendergroups_count);
}

void EXPORT m3dfw__delete__RenderGroups(m3dfw::RenderGroups * ptr)
{
	delete ptr;
}

m3dfw::RenderConfiguration EXPORT m3dfw__RenderGroups_getGroupConfig(m3dfw::RenderGroups * ptr, m3dfw::RGID * id)
{
	return ptr->getGroupConfig(*id);
}