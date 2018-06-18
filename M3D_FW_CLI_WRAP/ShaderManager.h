#pragma once

#include "Stdafx.h"


#include <M3DFW.h>


namespace m3dfw_cli
{
	public ref class ShaderManager
	{
	public:

		void clear();

		void unbindProgram();

		unsigned int loadProgram(System::String ^ v_src, System::String ^ f_src, System::String ^ name);
		void deleteProgram(unsigned int id);

		void * getInstance();

	protected:

		m3dfw::ShaderManager * _instance;
	};

	public ref class ShaderManager_GC
		: public ShaderManager
	{

	};

	public ref class ShaderManager_Ref
		: public ShaderManager
	{

	};
}