#include "RenderConfigurations.h"


m3dfw::RenderConfigurations::RenderConfigurations(GfxSceneConfig & scene_config) : _sc_cfg(scene_config)
{
}

m3dfw::RenderConfigurations::~RenderConfigurations()
{
	for (RenderConfigInfo info : _configurations)
	{
		if (info.mode == INDIVIDUAL)
			if (info.config_union.config != nullptr)
				delete info.config_union.config;
	}
}

void m3dfw::RenderConfigurations::setGroup(unsigned int id, RGID group_id)
{
	RenderConfigInfo & info = _configurations[id];

	if (info.mode == INDIVIDUAL)
		if (info.config_union.config != nullptr)
			delete info.config_union.config;

	info.mode = GROUP;
	info.config_union.group = group_id;
}

void m3dfw::RenderConfigurations::setIndividual(unsigned int id)
{
	RenderConfigInfo & info = _configurations[id];

	info.mode = INDIVIDUAL;
	info.config_union.config = new RenderConfiguration;
}

unsigned int m3dfw::RenderConfigurations::getConfigurationsCount()
{
	return _configurations.size();
}

unsigned int m3dfw::RenderConfigurations::addConfiguration(m3dfw::RenderConfiguration r_config)
{
	_configurations.push_back(RenderConfigInfo(r_config));
	return _configurations.size() - 1;
}

unsigned int m3dfw::RenderConfigurations::addConfiguration(RGID group_id)
{
	_configurations.push_back(RenderConfigInfo(group_id));
	return _configurations.size() - 1;
}

m3dfw::RenderConfiguration & m3dfw::RenderConfigurations::getConfig(unsigned int id)
{
	RenderConfigInfo & info = _configurations[id];

	switch (info.mode)
	{
	case INDIVIDUAL:
		return *info.config_union.config;

	case GROUP:
		return _sc_cfg._rendergroups.getGroupConfig(id);
	}
}

const m3dfw::RenderConfigInfo & m3dfw::RenderConfigurations::getInfo(unsigned int id)
{
	return _configurations[id];
}