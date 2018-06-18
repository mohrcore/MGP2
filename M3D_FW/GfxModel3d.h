#pragma once

#include <vector>

#include "GMesh3d.h"
#include "GMaterial.h"
#include "RenderConfigurations.h"
#include "Resource.h"


namespace m3dfw
{
	class GfxModel3d
	{
	public:

		GfxModel3d();
		~GfxModel3d();

		void clear();

		std::vector<GMesh3d> meshes;
		std::vector<Resource<GMaterial>> materials;

		//RenderConfigurations * r_configs;
	};
}


