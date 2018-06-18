#include "GfxEnvironment.h"

#define M3DFW_ENV_LIGHTS_CNT 1024


m3dfw::GfxEnvironment::GfxEnvironment() : _lights_cnt(M3DFW_ENV_LIGHTS_CNT)
{
	//_lights.resize(M3DFW_ENV_LIGHTS_CNT);
}

m3dfw::GfxEnvironment::~GfxEnvironment()
{
}

m3dfw::List<m3dfw::GfxBasicLight> & m3dfw::GfxEnvironment::lights()
{
	return _lights;
}