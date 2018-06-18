#include "DllLoader.h"



m3dfw::DllLoader::DllLoader()
{
}


m3dfw::DllLoader::~DllLoader()
{
}

bool m3dfw::DllLoader::libloader_loadLibrary(const std::string & path)
{
	_lib_handle = LoadLibrary(path.c_str());

	if (_lib_handle == NULL)
		return false;

	return true;
}

void * m3dfw::DllLoader::libloader_getFctPtr(const std::string & name)
{
	return (void *)GetProcAddress(_lib_handle, name.c_str());
}

void * m3dfw::DllLoader::libloader_getFctPtr(int ordinal)
{
	return (void *)GetProcAddress(_lib_handle, (LPCSTR)ordinal);
}