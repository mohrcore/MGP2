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

m3dfw::ResourceBase PTR_EXPORT(*) m3dfw__ResourceLoader_importGfxModel3d(m3dfw::ResourceLoader * ptr, const char * path, const char * name)
{
	return &ptr->importGfxModel3d(path, name);
}

m3dfw::ResourceBase PTR_EXPORT(*) m3dfw__ResourceLoader_importGTexture2d(m3dfw::ResourceLoader * ptr, const char * path, const char * name)
{
	return &ptr->importGTexture2d(path, name);
}

m3dfw::ResourceBase PTR_EXPORT(*) m3dfw__ResourceLoader_importGMaterial(m3dfw::ResourceLoader * ptr, const char * path, const char * name, m3dfw::ShaderManager * sm)
{
	return &ptr->importGMaterial(path, name, *sm);
}

bool m3dfw__loadMaterialResourcesFromMDPFile(const char * path, m3dfw::ResourceLoader * rloader, m3dfw::ShaderManager * sm)
{
	return m3dfw::loadMaterialResourcesFromMDPFile(path, *rloader, *sm);
}