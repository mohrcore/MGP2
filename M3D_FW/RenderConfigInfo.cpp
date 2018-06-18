#include "RenderConfigInfo.h"


m3dfw::RenderConfigInfo::RenderConfigInfo() 
{
	config_union.config = NULL;
}

m3dfw::RenderConfigInfo::RenderConfigInfo(const m3dfw::RenderConfiguration & r_config) : mode(INDIVIDUAL)
{
	config_union.config = new RenderConfiguration(r_config);
}

m3dfw::RenderConfigInfo::RenderConfigInfo(RGID group_id) : mode(GROUP)
{
	config_union.config = NULL;
}

m3dfw::RenderConfigInfo::~RenderConfigInfo()
{
	if (mode == INDIVIDUAL)
		if (config_union.config != NULL)
			delete config_union.config;
}