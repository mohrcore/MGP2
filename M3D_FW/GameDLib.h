#pragma once

#include <map>
#include <string>
#include <vector>

#include "DllLoader.h"

#include "GameDLib_DEF.h"

#ifdef WINDOWS_BUILD
#define LIB_CLASS m3dfw::DllLoader
#else
#define LIB_CLASS NULL
#endif

///Gets a function pointer from a library file using N as a name or ordinal and casts it to a pointer type specified by T.
#define GET_DLIBFUNCTION(T, N) ((T)libloader_getFctPtr(N))

//namespace m3d
//{
//	class UFctSender;
//	class UFctData;
//}

namespace m3dfw
{
	class UFctInfo
	{
	public:

		std::string name;
		UserFct_ptr pointer;

		//void operator()(m3d::UFctSender&, const m3d::UFctData&);
	};

	class GameDLib
		: public DllLoader
	{
	public:

		GameDLib();
		~GameDLib();

		bool loadLibrary(const std::string & path);

		UserFct_ptr getFunctionByName(const std::string & name);

	private:

		void loadVectorToMap(std::vector<UFctInfo> & data);

		std::map<std::string, UserFct_ptr> _functions;
	};
}