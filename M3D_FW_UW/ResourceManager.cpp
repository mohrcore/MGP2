#include <M3DFW.h>

#include "EXPORT.h"

//ResourceManager class unwrap

m3dfw::ResourceManager PTR_EXPORT(*) m3dfw__new__ResourceManager()
{
	return new m3dfw::ResourceManager();
}

void EXPORT m3dfw__delete__ResourceManager(m3dfw::ResourceManager * o_ptr)
{
	delete o_ptr;
}

bool EXPORT m3dfw__ResourceManager_isAnyKindOfResourceAvailable(m3dfw::ResourceManager * o_ptr, const char * name)
{
	return o_ptr->isAnyKindOfResourceAvaible(name);
}

void EXPORT m3dfw__ResourceManager_clearAllResources(m3dfw::ResourceManager * o_ptr)
{
	o_ptr->clearAllResources();
}

