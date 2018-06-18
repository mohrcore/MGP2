#include "MOB_Model3d_Writer.h"

#include "Util.h"

unsigned int calculateRequiredFileSpace(const mfile::MOB_Model3d & model)
{
	unsigned int req_sz = 0;

	req_sz += sizeof(model.mesh_cnt);
	req_sz += sizeof(model.material_cnt);
	req_sz += mfile::cStrSize(model.name);

	for (unsigned long i = 0; i < model.material_cnt; i++)
		req_sz += mfile::cStrSize(model.material_names[i]);

	for (unsigned long i = 0; i < model.mesh_cnt; i++)
	{
		mfile::MOB_GMesh3d & mesh = model.meshes[i];

		req_sz += sizeof(mesh.vec3_per_vertex);
		req_sz += sizeof(mesh.vec2_per_vertex);
		req_sz += sizeof(mesh.f_per_vertex);
		req_sz += sizeof(mesh.vertices_cnt);
		req_sz += sizeof(mesh.indices_cnt);
		req_sz += sizeof(mesh.material);

		req_sz += mesh.vertices_cnt * mesh.getVertexSize();
		req_sz += mesh.indices_cnt * sizeof(unsigned long);
	}

	return req_sz;
}

bool mfile::writeModel3d(mfile::MFile & target, mfile::MOB_Model3d & source)
{
	if (!target.good())
		return false;

	if (source.name == nullptr)
		copyCStr(target.getFilePath().c_str(), source.name);

	//Calculate required file (body) size
	unsigned int req_sz = calculateRequiredFileSpace(source);

	//Resize file's body
	target.resize(req_sz);

	target.goBeginning();

	//Write data
	target.writeCStr(source.name);
	target.write(source.mesh_cnt);
	target.write(source.material_cnt);

	for (unsigned long i = 0; i < source.material_cnt; i++)
		target.writeCStr(source.material_names[i]);

	for (unsigned long i = 0; i < source.mesh_cnt; i++)
		if (!writeGMesh3d(target, source.meshes[i]))
			return false;

	//target.writeCStr("test_str");

	return true;
}

bool mfile::writeGMesh3d(mfile::MFile & target, const mfile::MOB_GMesh3d & source)
{
	target.write(source.vertices_cnt);
	target.write(source.indices_cnt);
	//target.write(source.texture_cnt);
	target.write(source.material);
	target.write(source.vec3_per_vertex);
	target.write(source.vec2_per_vertex);
	target.write(source.f_per_vertex);
	target.writeRange(source.v_data, source.vertices_cnt * source.getVertexSize());
	target.writeRange(source.i_data, source.indices_cnt * sizeof(unsigned long));
	//target.writeRange(source.textures, source.texture_cnt);

	return true;
}