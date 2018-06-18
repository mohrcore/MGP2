#pragma once

#include <string>

#include "MFiles.h"

#include "GMaterial.h"
#include "ShaderManager.h"
#include "ResourceManager.h"


namespace m3dfw
{
	class GMaterialLoader
	{
	public:

		GMaterialLoader(ResourceManager & rm);
		~GMaterialLoader();

		bool loadGMaterialFromMOB_Material(GMaterial & target, const mfile::MOB_Material & source, std::string root_dir, ShaderManager & sm);

	private:

		ResourceManager & _rm;
	};
}


