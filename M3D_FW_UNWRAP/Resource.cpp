#include <M3DFW.h>

#include "EXPORT.h"

//ResourceBase class unwrap

m3dfw::ResourceBase PTR_EXPORT(*) m3dfw__new__ResourceBase()
{
	return new m3dfw::ResourceBase();
}

void EXPORT m3dfw__delete__ResourceBase(m3dfw::ResourceBase * o_ptr)
{
	delete o_ptr;
}
