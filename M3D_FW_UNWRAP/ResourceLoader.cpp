#include <M3DFW.h>

#include "EXPORT.h"

//ResourceLoader class unwrap

m3dfw::ResourceLoader PTR_EXPORT(*) m3dfw__new__ResourceLoader(m3dfw::ResourceManager * res_mngr)
{
	return new m3dfw::ResourceLoader(*res_mngr);
}

void EXPORT m3dfw__delete__ResourceLoader(m3dfw::ResourceLoader * o_ptr)
{
	delete o_ptr;
}

void m3dfw__ResourceLoader_importGfxModel3d(m3dfw::ResourceLoader * ptr, const char * path, const char * name)
{
	ptr->importGfxModel3d(path, name);
}

void m3dfw__ResourceLoader_importGTexture2d(m3dfw::ResourceLoader * ptr, const char * path, const char * name)
{
	ptr->importGTexture2d(path, name);
}

void m3dfw__ResourceLoader_importGMaterial(m3dfw::ResourceLoader * ptr, const char * path, const char * name, m3dfw::ShaderManager * sm)
{
	ptr->importGMaterial(path, name, *sm);
}