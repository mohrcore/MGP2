#include <M3DFW.h>

#include "EXPORT.h"


m3dfw::SmartPtrRC PTR_EXPORT(*) m3dfw__new__SmartPtrRC()
{
	return new m3dfw::SmartPtrRC();
}

void EXPORT m3dfw__delete__SmartPtrRC(m3dfw::SmartPtrRC * o_ptr)
{
	delete o_ptr;
}

void EXPORT m3dfw__SmartPtrRC_free(m3dfw::SmartPtrRC * o_ptr)
{
	o_ptr->free();
}

m3dfw::SmartPtrRC PTR_EXPORT(*) m3dfw__copy__SmartPtrRC(m3dfw::SmartPtrRC * ptr)
{
	return new m3dfw::SmartPtrRC(*ptr);
}