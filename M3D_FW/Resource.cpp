#include "Resource.h"


m3dfw::ResourceBase::ResourceBase()
{
}


m3dfw::ResourceBase::~ResourceBase()
{
}


void * m3dfw::ResourceBase::getResourcePtr()
{
	return _res;
}