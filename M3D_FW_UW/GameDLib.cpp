#include <M3DFW.h>

#include "EXPORT.h"

//GameDLib class unwrap

m3dfw::GameDLib PTR_EXPORT(*) m3dfw__new__GameDLib()
{
	return new m3dfw::GameDLib;
}

void EXPORT m3dfw__delete__GameDLib(m3dfw::GameDLib * o_ptr)
{
	delete o_ptr;
}

bool EXPORT m3dfw__GameDLib_loadLibrary(m3dfw::GameDLib * o_ptr, const char * path)
{
	return o_ptr->loadLibrary(path);
}

m3dfw::UserFct_ptr EXPORT m3dfw__GameDLib_getFunctionByName(m3dfw::GameDLib * o_ptr, const char * name)
{
	return o_ptr->getFunctionByName(name);
}

//UFctInfo struct unwrap

const char PTR_EXPORT(*) m3dfw__UFctInfo_name(m3dfw::UFctInfo * o_ptr)
{
	return o_ptr->name.c_str();
}

m3dfw::UserFct_ptr EXPORT m3dfw__UFctInfo_pointer(m3dfw::UFctInfo * o_ptr)
{
	return o_ptr->pointer;
}