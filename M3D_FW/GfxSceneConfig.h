#pragma once

#include <string>

#include "RenderGroups.h"

namespace m3dfw
{
	class GfxSceneConfig
	{
	public:

		GfxSceneConfig();
		//GfxSceneConifg(const std::string & config_str);
		~GfxSceneConfig();

		RenderGroups _rendergroups;
	};
}


