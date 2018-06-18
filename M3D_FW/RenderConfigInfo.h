#pragma once

#include "ShaderManager.h"

#include <vector>

namespace m3dfw
{
	typedef unsigned int RGID; // Render Group ID

	enum RenderMode
	{
		SHADED,
		UNSHADED,
		WIREFRAME_D
	};

	enum RenderConfigMode
	{
		INDIVIDUAL,
		GROUP
	};

	struct RenderConfiguration
	{
		RenderMode render_mode;
		ShID shading_program;
	};

	union RenderGroupConfigUnion
	{
		RGID group;
		RenderConfiguration * config;
	};

	struct RenderConfigInfo
	{
		RenderConfigInfo();
		RenderConfigInfo(const RenderConfiguration & r_cfg);
		RenderConfigInfo(RGID group_id);
		~RenderConfigInfo();

		RenderConfigMode mode;

		RenderGroupConfigUnion config_union;
	};
}
