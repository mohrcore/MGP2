#pragma once

#include <M3DFW.h>

#include "MResource.h"

namespace m3dfw_cli
{
	public ref class ResourceManager
	{
	public:

		//ResourceBase_Ref getResource(System::String name);

		bool isAnyKindOfResourceAvaible(System::String ^ name);

		void clearAllResources();

	protected:

		m3dfw::ResourceManager * _instance;
	};

	public ref class ResourceManager_GC
		: public ResourceManager
	{
	public:

		ResourceManager_GC();
		~ResourceManager_GC();
		!ResourceManager_GC();
	};

	public ref class ResourceManager_Ref
		: public ResourceManager
	{
	public:

		ResourceManager_Ref(System::IntPtr ptr);
	};
}