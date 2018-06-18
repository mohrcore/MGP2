#include "ResourceManager.h"



m3dfw::ResourceManager::ResourceManager()
{
}


m3dfw::ResourceManager::~ResourceManager()
{
}

bool m3dfw::ResourceManager::isAnyKindOfResourceAvaible(const std::string & name) const
{
	if (_name_to_resource.count(name) == 0)
		return false;

	return true;
}

void m3dfw::ResourceManager::clearAllResources()
{
	_name_to_resource.clear();
}

//void m3dfw::ResourceManager::importResource(const std::string & path, const std::string & name, ResourceKind kind)
//{
//	ResourceBase * res;
//
//	switch (kind)
//	{
//	case GMESH3D:
//
//		importResourceGfxModel3d(path, res);
//	}
//
//	_name_to_resource[name] = res;
//}

//void m3dfw::ResourceManager::importResourceGfxModel3d(const std::string & path, ResourceBase * res_ptr)
//{
//	res_ptr = new Resource<GfxModel3d>(new GfxModel3d);
//
//	GfxModel3d & model = **(static_cast<Resource<GfxModel3d> *>(res_ptr));
//
//	MOB_Model import_model;
//
//	_mob_importer.loadFile(path);
//	_mob_importer.importData(&import_model);
//
//	// TODO: Create GfxModel3dLoader!!!!!!!!!!!!!!!!!!!!!1!
//	model.mesh_count = import_model.mesh_cnt;
//	model.textures_for_mesh = import_model.meshes[1].;
//
//	model.meshes = new GMesh3d[model.mesh_count];
//
//	for (unsigned long i = 0; i < model.mesh_count; i++)
//	{
//		_gmesh_loader.loadGMesh3dFromMOB_Mesh(model.meshes[i], import_model.meshes[i]);
//	}
//}