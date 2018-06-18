#pragma once

#include "RenderConfigInfo.h"
#include "GfxSceneConfig.h"

namespace m3dfw
{
	class RenderConfigurations
	{
	public:

		RenderConfigurations(GfxSceneConfig & scene_config);
		~RenderConfigurations();

		RenderConfiguration & getConfig(unsigned int id);
		const RenderConfigInfo & getInfo(unsigned int id);

		void setGroup(unsigned int id, RGID group_id);
		void setIndividual(unsigned int id);

		unsigned int getConfigurationsCount();

		unsigned int addConfiguration(RenderConfiguration r_Config); // Return value is ID of the configuration
		unsigned int addConfiguration(RGID group_id); // --//--

	private:

		GfxSceneConfig & _sc_cfg;

		std::vector<RenderConfigInfo> _configurations;
	};
}