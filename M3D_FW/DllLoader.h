#pragma once

//#ifdef WINDOWS_BUILD

#include <string>

#include <Windows.h>

namespace m3dfw
{
	class DllLoader
	{
	public:

		DllLoader();
		~DllLoader();

		bool libloader_loadLibrary(const std::string & path);

		void * libloader_getFctPtr(const std::string & name);

		void * libloader_getFctPtr(int ordinal);

	private:

		HMODULE _lib_handle;
	};
}


//#endif