#include "EditableModel3d.h"

#include "Util.h"


mfile::EditableModel3d::EditableModel3d()
{
}

mfile::EditableModel3d::~EditableModel3d()
{
}


unsigned int mfile::EditableModel3d::getMeshCount() const
{
	return mesh_cnt;
}

unsigned int mfile::EditableModel3d::getVec3AttribCount(mfile::GMesh3dID m_id) const
{
	return meshes[m_id].vec3_per_vertex;
}

unsigned int mfile::EditableModel3d::getVec2AttribCount(mfile::GMesh3dID m_id) const
{
	return meshes[m_id].vec2_per_vertex;
}

unsigned int mfile::EditableModel3d::getFloatAttribCount(mfile::GMesh3dID m_id) const
{
	return meshes[m_id].f_per_vertex;
}

void mfile::EditableModel3d::setMeshCount(unsigned int count)
{
	MOB_GMesh3d * old_meshes = meshes;

	meshes = new MOB_GMesh3d[count];

	unsigned int cpy_cnt = min<unsigned int>(mesh_cnt, count);

	for (unsigned int i = 0; i < cpy_cnt; i++)
		meshes[i] = old_meshes[i];

	mesh_cnt = count;

	delete[] old_meshes;
}

void mfile::EditableModel3d::setAttribCount(mfile::GMesh3dID m_id, unsigned char vec3_count, unsigned char vec2_count, unsigned char float_count)
{
	MOB_GMesh3d & mesh = meshes[m_id];

	if (mesh.v_data != nullptr)
	{
		float * old_data = mesh.v_data;

		//Old vertex size (float count)
		unsigned int f_cnt = mesh.getVertexSize() / sizeof(float);

		//New vertex size (float count)
		int nsz = f_cnt - (mesh.vec3_per_vertex - vec3_count) * 3 - (mesh.vec2_per_vertex - vec2_count) * 2 - (mesh.f_per_vertex - float_count);

		//Create new vertex data
		mesh.v_data = new float[mesh.vertices_cnt * nsz];

		// Rearrange vertex data
		for (unsigned int i1 = 0; i1 < mesh.vertices_cnt; i1++)
		{
			//Rearrange vec3 data
			for (unsigned char i2 = 0; i2 < min(mesh.vec3_per_vertex, vec3_count) * 3; i2++)
				mesh.v_data[i1 * nsz + i2] = old_data[i1 * f_cnt + i2];

			//Rearrange vec2 data
			for(unsigned char i2 = 0; i2 < min(mesh.vec2_per_vertex, vec2_count) * 2; i2++)
				mesh.v_data[i1 * nsz + vec3_count * 3 + i2] = old_data[i1 * f_cnt + mesh.vec3_per_vertex * 3 + i2];

			//Rearrange float data
			for (unsigned char i2 = 0; i2 < min(mesh.f_per_vertex, float_count); i2++)
				mesh.v_data[i1 * nsz + vec3_count * 3 + vec2_count * 2 + i2] = old_data[i1 * f_cnt + mesh.vec3_per_vertex * 3 + mesh.vec2_per_vertex * 2 + i2];
		}

		//Delete old vertex data
		delete[] old_data;
	}


	//Updata vertex data information
	mesh.vec3_per_vertex = vec3_count;
	mesh.vec2_per_vertex = vec2_count;
	mesh.f_per_vertex = float_count;
}

//void mfile::EditableModel3d::setTextureCount(mfile::GMesh3dID m_id, unsigned char count)
//{
//	MOB_GMesh3d & mesh = meshes[m_id];
//
//	unsigned char * old_data = mesh.textures;
//
//	mesh.textures = new unsigned char[count];
//
//	for (unsigned char i = 0; i < min(mesh.texture_cnt, count); i++)
//		mesh.textures[i] = old_data[i];
//
//	mesh.texture_cnt = count;
//
//	delete[] old_data;
//}