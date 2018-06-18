#include "MOB_Model3d_Loader.h"

#include "Util.h"

bool mfile::loadModel3d(mfile::MFile & source, mfile::MOB_Model3d & target)
{
	if (!source.good())
		return false;

	if (!compareCStr(source.getHeaderData().type, "model_3d"))
		return false;

	target.clear();

	source.goBeginning();

	source.readCStr(target.name);
	source.read(target.mesh_cnt);
	//source.read(target.texture_cnt);
	source.read(target.material_cnt);

	target.meshes = new MOB_GMesh3d[target.mesh_cnt];
	//target.texture_names = new char *[target.texture_cnt];
	target.material_names = new char *[target.material_cnt];

	//for (unsigned long i = 0; i < target.texture_cnt; i++)
	//	source.readCStr(target.texture_names[i]);
	for (unsigned long i = 0; i < target.material_cnt; i++)
		source.readCStr(target.material_names[i]);

	for (unsigned long i = 0; i < target.mesh_cnt; i++)
		if (!loadGMesh3d(source, target.meshes[i]))
			return false;

	return true;
}

bool mfile::loadGMesh3d(mfile::MFile & source, mfile::MOB_GMesh3d & target)
{
	target.clear();

	source.read(target.vertices_cnt);
	source.read(target.indices_cnt);
	//source.read(target.texture_cnt);
	source.read(target.material);
	source.read(target.vec3_per_vertex);
	source.read(target.vec2_per_vertex);
	source.read(target.f_per_vertex);
	
	target.v_data = new float[ target.vertices_cnt * target.getVertexSize() / sizeof(float)];
	target.i_data = new unsigned long[target.indices_cnt];
	//target.textures = new unsigned char[target.texture_cnt];

	float * data_it = target.v_data;

	unsigned int vsz = target.getVertexSize();

	source.readRange(target.v_data, target.vertices_cnt * vsz);
	source.readRange(target.i_data, target.indices_cnt * sizeof(float));
	//source.readRange(target.textures, target.texture_cnt);

	return true;
}