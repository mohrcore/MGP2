#pragma once

#include "GfxLight.h"
#include "MemoryManagement.h"
#include "List.h"


namespace m3dfw
{
	//typedef unsigned int GfxLightID;

	class GfxEnvironment
	{
	public:

		GfxEnvironment();
		~GfxEnvironment();

		List<GfxBasicLight> & lights();

	private:

		const unsigned int _lights_cnt;
		List<GfxBasicLight> _lights;
	};
}


