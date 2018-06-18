#pragma once

#include <vector>

//Common interface definitions fo GameDynamicLibraries

#define GDLIB_GET_USR_FCT_LIST 1


namespace m3d
{
	//TODO: Write these classes
	class UFctSender {};
	class UFctData {};
}

namespace m3dfw
{
	class UFctInfo;

	typedef void(__cdecl * UserFct_ptr)(m3d::UFctSender&, const m3d::UFctData&);
	typedef void(__cdecl * VecUFct_ptr)(std::vector<UFctInfo>&);
}