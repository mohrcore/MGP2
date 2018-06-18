#include <M3DFW.h>

#include "EXPORT.h"

//GfxSceneConfig class unwrap

m3dfw::GfxSceneConfig PTR_EXPORT(*) m3dfw__new__GfxSceneConfig()
{
	return new m3dfw::GfxSceneConfig();
}

void EXPORT m3dfw__delete__GfxSceneConfig(m3dfw::GfxSceneConfig * ptr)
{
	delete ptr;
}

