#pragma once

#include "CommonTypes.h"
#include "GfxModel3d.h"
#include "RenderConfigurations.h"
#include "Resource.h"

namespace m3dfw
{
	class GfxObject
	{
	public:

		GfxObject(Resource <GfxModel3d> & model_r);
		~GfxObject();

		Resource<GfxModel3d> model;

		Vec3f position;
		Vec3f rotation;
		Vec3f scale;

		//void setActiveRenderConfiguration(unsigned int id);
		//unsigned int getActiveRenderConfigurationID() const;

	private:

		//unsigned int _active_r_config;
	};
}

