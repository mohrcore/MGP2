#include <M3DFW.h>

#include "EXPORT.h"

//ResourceBase class unwrap

m3dfw::ResourceBase PTR_EXPORT(*) m3dfw__new__ResourceBase()
{
	return new m3dfw::ResourceBase();
}

m3dfw::ResourceBase PTR_EXPORT(*) m3dfw__copy__RsourceBase(m3dfw::ResourceBase * ptr)
{
	return new m3dfw::ResourceBase(*ptr);
}

void EXPORT m3dfw__delete__ResourceBase(m3dfw::ResourceBase * o_ptr)
{
	delete o_ptr;
}

void PTR_EXPORT(*) m3dfw__ResourceBase_getResourcePtr(m3dfw::ResourceBase * o_ptr)
{
	return o_ptr->getResourcePtr();
}