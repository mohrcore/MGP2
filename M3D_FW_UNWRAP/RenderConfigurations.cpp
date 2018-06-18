#include <M3DFW.h>

#include "EXPORT.h"

//RenderConfigurations class unwrap

m3dfw::RenderConfigurations PTR_EXPORT(*) m3dfw__new__RenderConfigurations(m3dfw::GfxSceneConfig * scene_config)
{
	return new m3dfw::RenderConfigurations(*scene_config);
}

void EXPORT m3dfw__delete__RenderConfigurations(m3dfw::RenderConfigurations * ptr)
{
	delete ptr;
}

m3dfw::RenderConfiguration EXPORT m3dfw__RenderConfigurations_getConfig(m3dfw::RenderConfigurations * ptr, unsigned int id)
{
	return ptr->getConfig(id);
}

m3dfw::RenderConfigInfo EXPORT m3dfw__RenderConfigurations_getInfo(m3dfw::RenderConfigurations * ptr, unsigned int id)
{
	return ptr->getInfo(id);
}

void EXPORT m3dfw__RenderConfigurations_setGroup(m3dfw::RenderConfigurations * ptr, unsigned int id, m3dfw::RGID * group_id)
{
	ptr->setGroup(id,* group_id);
}

void EXPORT m3dfw__RendderConfigurations_setIndividual(m3dfw::RenderConfigurations * ptr, unsigned int id)
{
	ptr->setIndividual(id);
}

unsigned int EXPORT m3dfw__RenderConfigurations_getConfigurationsCount(m3dfw::RenderConfigurations * ptr)
{
	return ptr->getConfigurationsCount();
}

unsigned int EXPORT m3dfw__RenderConfigurations_addConfiguration(m3dfw::RenderConfigurations * ptr, m3dfw::RenderConfiguration * r_Config)
{
	return ptr->addConfiguration(*r_Config);
}

unsigned int EXPORT m3dfw__RenderConfigurations_addConfiguration(m3dfw::RenderConfigurations * ptr, m3dfw::RGID * group_id)
{
	return ptr->addConfiguration(*group_id);
}