#include "MResource.h"


using namespace m3dfw_cli;


const System::IntPtr ResourceBase::getResourcePtr()
{
	return System::IntPtr(_instance->getResourcePtr());
}


ResourceBase_Ref::ResourceBase_Ref(System::IntPtr ptr)
{
	_instance = (m3dfw::ResourceBase *)ptr.ToPointer();
}