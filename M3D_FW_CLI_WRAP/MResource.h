#pragma once

#include <M3DFW.h>


namespace m3dfw_cli
{
	public ref class ResourceBase
	{
	public:

		const System::IntPtr getResourcePtr();

	protected:

		m3dfw::ResourceBase * _instance;
	};

	public ref class ResourceBase_Ref
		: public ResourceBase
	{
	public:

		ResourceBase_Ref(System::IntPtr ptr);
	};
}