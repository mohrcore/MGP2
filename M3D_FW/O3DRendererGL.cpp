#include "O3DRendererGL.h"

#include <algorithm>

#include "CommonTypes.h"



m3dfw::O3DRendererGL::O3DRendererGL(ShaderManager & sh_mngr) : _sh_mngr(sh_mngr), _current_prog(0xFFFF), _uniformarray_alloc(1024)
{
	generateTQ();
}

m3dfw::O3DRendererGL::~O3DRendererGL()
{
	deleteTQ();
}

struct VRTX
{
	VRTX() {}
	VRTX(m3dfw::Vec3f p, m3dfw::Vec3f n, m3dfw::Vec2f t) : vpos(p), normals(n), tx(t)
	{
	}

	m3dfw::Vec3f vpos;
	m3dfw::Vec3f normals;
	m3dfw::Vec2f tx;
};

void m3dfw::O3DRendererGL::generateTQ()
{
	float v_data[32] = {
		-0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f
	};

	GLuint i_data[6] = {
		3, 1, 0,
		3, 2, 1
	};

	glGenVertexArrays(1, &_tq_vao);
	glBindVertexArray(_tq_vao);
	glGenBuffers(1, &_tq_vbo);
	glGenBuffers(1, &_tq_ebo);

	glBindVertexArray(_tq_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _tq_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VRTX), v_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _tq_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), i_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 *sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(VRTX), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(VRTX), (void *)(6 * sizeof(float)));
}

void m3dfw::O3DRendererGL::deleteTQ()
{
	glDeleteVertexArrays(1, &_tq_vao);
	glDeleteBuffers(1, &_tq_vbo);
	glDeleteBuffers(1, &_tq_ebo);
}

/*
void m3dfw::O3DRendererGL::render(GfxObject & object)
{
	for (unsigned int i = 0; i < object.model.mesh_count; i++)
	{
		GMesh3d & mesh = object.model.meshes[i];
		RenderConfiguration & r_config = object.model.r_configs[i].getConfig(object.getActiveRenderConfigurationID());

		glBindVertexArray(mesh.vaoID);

		switch (r_config.render_mode)
		{
		case SHADED:

			bindTextures(object.model, i);

			_sh_mngr.getProgram(r_config.shading_program).bind();

			//glUniformMatrix4fv(_sh_mngr.getUniformLocation("transformation_matrix"))

			renderMesh(mesh);

		case UNSHADED:

			_sh_mngr.unbindProgram();

			renderMesh(mesh);

		case WIREFRAME_D:

			_sh_mngr.unbindProgram();

			renderMeshWireframe_D(mesh);
		}

		//glBindVertexArray(0);
	}
}
*/

void m3dfw::O3DRendererGL::render(const GfxObject & object, const Camera3d & camera, const m3dfw::List<m3dfw::GfxBasicLight> & lights)
{
	for (unsigned int i = 0; i < object.model->meshes.size(); i++)
	{
		const GMesh3d & mesh = object.model->meshes[i];
		auto material = object.model->materials[i];

		glBindVertexArray(mesh.vaoID);

		ShID progID = material->getProgramID();

		//This should be done in shader manager!!!
		if (progID != _current_prog)
		{
			_sh_mngr.getProgram(progID).bind();
			_current_prog = progID;
		}

		auto & prog = _sh_mngr.getProgram(progID);

		bindTextures(material);

		Mat4 transformation(Identity);
		Mat4 ws_transformation(Identity);
		transformation.scale(Vec3f(0.01f, 0.01f, 0.01f));
		prepareTransformationMatrix(transformation, object, camera);
		prepareWorldSpaceTransformationMatrix(ws_transformation, object);

		prog.setUniformMat4(material->getTransformationMatrixLocation(), transformation.data());
		prog.setUniformMat4(material->getWorldSpaceTransformationMatrixLocation(), ws_transformation.data());
		prog.setUniformVec3(material->getAmbientLocation(), Vec3f(0.05f, 0.05f, 0.05f));

		uploadLightData(*material, lights);

		renderMesh(mesh);
	}
}

void m3dfw::O3DRendererGL::renderTestQuadMat(const m3dfw::GMaterial & material)
{
	glBindVertexArray(_tq_vao);

	ShID progID = material.getProgramID();
	auto & prog = _sh_mngr.getProgram(progID);
	//auto & prog = _sh_mngr.getProgram(1);

	prog.bind();

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	

	Mat4 transformation(Identity);

	//transformation *= _projection;

	//transformation.rotate(Vec3f(0.0, 0.0, 0.5));
	transformation.translate(Vec3f(0.0f, 0.70f, 0.0f));
	transformation.rotate(Vec3f(0.0f, 0.0f, 2.0f));
	transformation.scale(Vec3f(1.0f, 0.5f, 1.0f));


	prog.setUniformMat4(material.getTransformationMatrixLocation(), transformation.data());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/*
void m3dfw::O3DRendererGL::bindTextures(const m3dfw::GfxModel3d & model, unsigned int mesh_id) const
{
	for (unsigned int i = 0; i < model.textures_for_mesh[mesh_id]; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, model.textures[mesh_id][i]->id);
	}
}
*/

void m3dfw::O3DRendererGL::prepareTransformationMatrix(m3dfw::Mat4 & target, const m3dfw::GfxObject & object, const m3dfw::Camera3d & camera) const
{
	//target.identity();

	//OGL-space
	target *= _projection;
	//View-space
	target.rotate(camera.angle);
	target.translate(camera.position);
	//World-space
	target.translate(object.position);
	target.rotate(object.rotation);
	target.scale(object.scale);

	//Shit optimization

	//Total multiply operations count: 576 (UGH!)
	//Could be: 225 with the best matrix multiplication optimalization (That's better), maybe even 125 if rotation could be done with just one multiplication - up to 4.6 times faster!
}

void m3dfw::O3DRendererGL::prepareWorldSpaceTransformationMatrix(m3dfw::Mat4 & target, const m3dfw::GfxObject & object) const
{
	target.translate(object.position);
	target.rotate(object.rotation);
	target.scale(object.scale);
}

void m3dfw::O3DRendererGL::bindTextures(Resource<m3dfw::GMaterial> material) const
{
	for (unsigned int i = 0; i < material->getTextureCount(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(i)->id);
	}
}

void m3dfw::O3DRendererGL::renderMesh(const m3dfw::GMesh3d & mesh) const
{
	glDrawElements(GL_TRIANGLES, mesh.i_count, GL_UNSIGNED_INT, 0);
}

void m3dfw::O3DRendererGL::renderMeshWireframe_D(const m3dfw::GMesh3d & mesh) const
{
	glDrawElements(GL_LINE_LOOP, mesh.i_count, GL_UNSIGNED_INT, 0);
}

void m3dfw::O3DRendererGL::setProjectionMatrix(float fov, float z_near, float z_far, float aspect_ratio)
{
	float tan_fov_2 = std::tan(fov / 2.0f);

	_projection.zero();

	_projection(0, 0) = 1.0f / (tan_fov_2 * aspect_ratio);
	_projection(1, 1) = 1.0f / tan_fov_2;
	_projection(2, 2) = (z_far + z_near) / (z_near - z_far);
	_projection(2, 3) = -((2.0f * z_far * z_near) / (z_near - z_far));
	_projection(3, 2) = -1.0f;
}

void m3dfw::O3DRendererGL::uploadLightData(const m3dfw::GMaterial & material, const m3dfw::List<m3dfw::GfxBasicLight> & lights)
{
	auto & prog = _sh_mngr.getProgram(_current_prog);

	float * f = _uniformarray_alloc.alloc<float>(lights.size() * 3);

	prog.setUniformInt(material.getLightsCountLocation(), lights.size());

	int i = 0;
	for (auto light : lights)
	{
		f[i * 3] = light.position.x;
		f[i * 3 + 1] = light.position.y;
		f[i * 3 + 2] = light.position.z;

		i++;
	}
	prog.setUniformArrVec3(material.getLightsPositionsLocation(), f, lights.size());
	i = 0;
	for (/*auto light : lights*/ List<GfxBasicLight>::ConstIterator it = lights.begin(); it != lights.end(); ++it)
	{
		f[i * 3] = it->color.x;
		f[i * 3 + 1] = it->color.y;
		f[i * 3 + 2] = it->color.z;

		i++;
	}
	prog.setUniformArrVec3(material.getLightsColorsLocation(), f, lights.size());

	_uniformarray_alloc.dealloc(f);
}