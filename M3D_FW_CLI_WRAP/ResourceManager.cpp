#include "ResourceManager.h"

#include <msclr\marshal_cppstd.h>


using namespace m3dfw_cli;
using namespace msclr::interop;


//ResourceBase_Ref ResourceManager_Base::getResource(System::String name)
//{
//	std::string str = marshal_as<std::string>(%name);
//	return ResourceBase_Ref(&_instance->getResource(str));
//}

bool ResourceManager::isAnyKindOfResourceAvaible(System::String ^ name)
{
	return _instance->isAnyKindOfResourceAvaible(marshal_as<std::string>(name));
}

void ResourceManager::clearAllResources()
{
	_instance->clearAllResources();
}


ResourceManager_GC::ResourceManager_GC()
{
	_instance = new m3dfw::ResourceManager();
}

ResourceManager_GC::!ResourceManager_GC()
{
	delete _instance;
}

ResourceManager_GC::~ResourceManager_GC()
{
	this->!ResourceManager_GC();
}


ResourceManager_Ref::ResourceManager_Ref(System::IntPtr ptr)
{
	_instance = (m3dfw::ResourceManager *)ptr.ToPointer();
}