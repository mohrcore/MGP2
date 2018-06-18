#include <M3DFW.h>

#include "EXPORT.h"

//GfxScene class unwrap

m3dfw::GfxScene PTR_EXPORT(*) m3dfw__new__GfxScene()
{
	return new m3dfw::GfxScene();
}

void EXPORT m3dfw__delete__GfxScene(m3dfw::GfxScene * ptr)
{
	delete ptr;
}

//void EXPORT m3dfw__GfxScene_load(m3dfw::GfxScene * ptr, void * data_buffer)
//{
//	ptr->load(data_buffer);
//}

//void EXPORT m3dfw__GfxScene_clear(m3dfw::GfxScene * ptr)
//{
//	ptr->clear();
//}

//m3dfw::GfxObject PTR_EXPORT(*) m3dfw__GfxScene_getObject(m3dfw::GfxScene * ptr, unsigned int id)
//{
//	&ptr->getObject(id);
//}

//m3dfw::GfxSceneConfig EXPORT m3dfw__GfxScene_getConfiguration(m3dfw::GfxScene * ptr)
//{
//	ptr->getConfiguration();
//}
//
//unsigned int EXPORT m3dfw__GfxScene_getObjCount(m3dfw::GfxScene * ptr)
//{
//	return ptr->getObjCount();
//}