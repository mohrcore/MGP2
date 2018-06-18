#include "GfxModel3dLoader.h"


m3dfw::GMesh3dLoader::GMesh3dLoader()
	: _d_quad_v {
	Vertex(Vec3f(-0.5f, 0.5f, 0.0f), Vec2f(0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f)),
	Vertex(Vec3f(0.5f, 0.5f, 0.0f), Vec2f(1.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f)),
	Vertex(Vec3f(0.5f, -0.5f, 0.0f), Vec2f(1.0f, 1.0f), Vec3f(0.0f, 0.0f, 1.0f)),
	Vertex(Vec3f(-0.5f, -0.5f, 0.0f), Vec2f(0.0f, 1.0f), Vec3f(0.0f, 0.0f, 1.0f)) },
	_d_quad_i{ 1, 0, 3, 3, 2, 1 }
{
}


m3dfw::GMesh3dLoader::~GMesh3dLoader()
{
}


bool m3dfw::GMesh3dLoader::loadGMesh3dFromMOB_Mesh(m3dfw::GMesh3d & target, mfile::MOB_GMesh3d & mesh)
{
	target.v_count = mesh.vertices_cnt;
	target.i_count = mesh.indices_cnt;

	generateGLStuff(target);

	glBindVertexArray(target.vaoID);

	//Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, target.vboID);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices_cnt * mesh.getVertexSize(), mesh.v_data, GL_STATIC_DRAW);
	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, target.eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices_cnt * sizeof(unsigned long), mesh.i_data, GL_STATIC_DRAW);

	/*
	//Positon data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, VX_POS_OFFSET);
	//Texture coordinates data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, VX_UV_OFFSET);
	//Normal data
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, VX_NORMAL_OFFSET);
	*/

	// Binding every attribute in following order:
	// Vec3 attributes, Vec2 attributes, float attributes
	unsigned int vaa_id = 0;
	for (unsigned int i = 0; i < mesh.vec3_per_vertex; i++)
	{
		glEnableVertexAttribArray(vaa_id);
		glVertexAttribPointer(vaa_id, 3, GL_FLOAT, GL_FALSE, mesh.getVertexSize(), (void *)(i * 3 * sizeof(float)));
		vaa_id++;
	}
	for (unsigned int i = 0; i < mesh.vec2_per_vertex; i++)
	{
		glEnableVertexAttribArray(vaa_id);
		glVertexAttribPointer(vaa_id, 2, GL_FLOAT, GL_FALSE, mesh.getVertexSize(), (void *)((mesh.vec3_per_vertex * 3 + i * 2) * sizeof(float)));
		vaa_id++;
	}

	for (unsigned int i = 0; i < mesh.f_per_vertex; i++)
	{
		glEnableVertexAttribArray(vaa_id);
		glVertexAttribPointer(vaa_id, 1, GL_FLOAT, GL_FALSE, mesh.getVertexSize(), (void *)((mesh.vec3_per_vertex * 3 + mesh.vec2_per_vertex * 2 + i) * sizeof(float)));
		vaa_id++;
	}

	//Cleanup
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	target.fill();

	return true;
}

void m3dfw::GMesh3dLoader::generateGLStuff(m3dfw::GMesh3d & target)
{
	if (!target.empty())
		return;

	glGenVertexArrays(1, &target.vaoID);
	glBindVertexArray(target.vaoID);
	glGenBuffers(1, &target.vboID);
	glGenBuffers(1, &target.eboID);
}

void m3dfw::GMesh3dLoader::createTestQuad(m3dfw::GMesh3d & target, float left, float top, float right, float bottom, unsigned int shader_id)
{
	prepareObject(target);

	glBindVertexArray(target.vaoID);

	uploadVertexData(target, _d_quad_v, 4);
	uploadElementData(target, _d_quad_i, 6);

	target.fill(); //Disble target's _empty flag
}

void m3dfw::GMesh3dLoader::prepareObject(m3dfw::GMesh3d & target)
{
	target.clear();

	glGenVertexArrays(1, &target.vaoID);
	glGenBuffers(1, &target.vboID);
	glGenBuffers(1, &target.eboID);
}

void m3dfw::GMesh3dLoader::uploadVertexData(GMesh3d & target, const void * data, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, target.vboID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(m3dfw::Vertex), data, GL_STATIC_DRAW); //Uloadind vertex data
	
	target.v_count = size;
}

void m3dfw::GMesh3dLoader::uploadElementData(GMesh3d & target, const void * data, unsigned int size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, target.eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW); //Uloadind index data

	target.i_count = size;
}

m3dfw::GfxModel3dLoader::GfxModel3dLoader(m3dfw::ResourceManager & rm) : _rm(rm)
{
}

bool m3dfw::GfxModel3dLoader::loadGfxModel3dFromMOB_Model(m3dfw::GfxModel3d & target, mfile::MOB_Model3d & model)
{
	target.clear();

	const unsigned long mesh_cnt = model.mesh_cnt;
	const unsigned long mat_cnt = model.material_cnt;

	target.meshes.resize(mesh_cnt);

	for (unsigned long i = 0; i < mesh_cnt; i++)
	{
		const char * mat_name = model.material_names[model.meshes[i].material];

		if (!_rm.isResourceAvaible<GMaterial>(model.material_names[model.meshes[i].material]))
			return false;

		auto _res = _rm.getResource<GMaterial>(model.material_names[model.meshes[i].material]);

		target.materials.push_back(_res);

		if (!gmesh_loader.loadGMesh3dFromMOB_Mesh(target.meshes[i], model.meshes[i]))
			return false;
	}

	return true;
}