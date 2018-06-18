#include "GfxModel3d.h"



m3dfw::GfxModel3d::GfxModel3d()
{
}


m3dfw::GfxModel3d::~GfxModel3d()
{
	clear();
}


void m3dfw::GfxModel3d::clear()
{
	meshes.clear();

	materials.clear();
}