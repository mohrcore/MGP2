#include <GL/glew.h>
#include <string>
#include <vector>

#include "Util.h"
#include "Vertex.h"
#include "Texture.h"

#include "Mesh.h"



Mesh::Mesh() : vertices(nullptr), indices(nullptr), textures(nullptr), _v_count(0), _i_count(0), _t_count(0)
{
	glGenVertexArrays(1, &_vaoID);
	glGenBuffers(1, &_vboID);
	glGenBuffers(1, &_eboID);
}

Mesh::Mesh(const Mesh & arg) : _v_count(arg._v_count), _i_count(arg._i_count), _t_count(arg._t_count)
{
	glGenVertexArrays(1, &_vaoID);
	glGenBuffers(1, &_vboID);
	glGenBuffers(1, &_eboID);

	vertices = new Vertex[_v_count];
	indices = new GLuint[_i_count];
	textures = new Texture *[_t_count];

	for (int i = 0; i < _v_count; i++)
		vertices[i] = arg.vertices[i];

	for (int i = 0; i < _i_count; i++)
		indices[i] = arg.indices[i];

	for (int i = 0; i < _t_count; i++)
		textures[i] = arg.textures[i];
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vaoID);
	glDeleteBuffers(1, &_vboID);
	glDeleteBuffers(1, &_eboID);

	clear();
}


void Mesh::clear()
{
	if(vertices != nullptr)
		delete[] vertices;
	if(indices != nullptr)
		delete[] indices;
	if(textures != nullptr)
		delete[] textures;

	vertices = nullptr;
	indices = nullptr;
	textures = nullptr;
}

void Mesh::loadRawData(std::vector<Vertex> vert, std::vector<GLuint> ind, std::vector<Texture> & tex)
{
	clear();

	loadVertices(vert);
	loadIndices(ind);
	loadTextures(tex);
}

void Mesh::loadRawDataTP(std::vector<Vertex> vert, std::vector<GLuint> ind, const std::vector<std::string> & texture_paths, TextureBank & tb)
{
	clear();

	loadVertices(vert);
	loadIndices(ind);

	textures = new Texture *[texture_paths.size()];

	for (int i = 0; i < texture_paths.size(); i++)
	{
		textures[i] = tb.getTextureByPath(texture_paths[i]);
	}

	_t_count = texture_paths.size();
}

void Mesh::loadVertices(std::vector<Vertex> & vert)
{
	vertices = new Vertex[vert.size()];

	for (int i = 0; i < vert.size(); i++)
		vertices[i] = vert[i];
	_v_count = vert.size();
}

void Mesh::loadIndices(std::vector<GLuint> & ind)
{
	indices = new GLuint[ind.size()];

	for (int i = 0; i < ind.size(); i++)
		indices[i] = ind[i];
	_i_count = ind.size();
}

void Mesh::loadTextures(std::vector<Texture> & tex)
{
	textures = new Texture *[tex.size()];

	for (int i = 0; i < tex.size(); i++)
		textures[i] = &tex[i];
	_t_count = tex.size();
}

void Mesh::uploadData()
{
	glBindVertexArray(_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, _v_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _i_count * sizeof(GLuint), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
	if (textures != nullptr)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
	}

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint Mesh::getVAOID()
{
	return _vaoID;
}

int Mesh::getVertexCount()
{
	return _v_count;
}

int Mesh::getIndicesCount()
{
	return _i_count;
}

int Mesh::getTextureCount()
{
	return _t_count;
}