#include "GameDLib.h"



m3dfw::GameDLib::GameDLib()
{
}


m3dfw::GameDLib::~GameDLib()
{
}


bool m3dfw::GameDLib::loadLibrary(const std::string & path)
{
	if (!libloader_loadLibrary(path))
		return false;

	std::vector<UFctInfo> fct_vec;

	GET_DLIBFUNCTION(VecUFct_ptr, GDLIB_GET_USR_FCT_LIST)(fct_vec);

	loadVectorToMap(fct_vec);
}

void m3dfw::GameDLib::loadVectorToMap(std::vector<UFctInfo> & data)
{
	_functions.clear();

	for (auto && it : data)
		_functions[it.name] = it.pointer;
}

m3dfw::UserFct_ptr m3dfw::GameDLib::getFunctionByName(const std::string & name)
{
	return _functions[name];
}