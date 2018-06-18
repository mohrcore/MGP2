#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

#include "Util.h"
#include "Vertex.h"
#include "Texture.h"
#include "TextureBank.h"

class Mesh
{
public:

	Mesh();
	Mesh(const Mesh & arg); //TODO: Hey! It's fucking important to make a nice CC because of my shitty asset loading method which wastes time by overcopying stuff and fucks up the heap because of not copying dynamically allocated data.
	~Mesh();

	Vertex * vertices;
	GLuint * indices;
	Texture * * textures;

	void loadRawData(std::vector<Vertex> vert, std::vector<GLuint> ind, std::vector<Texture> & tex); //Loads vertex, index and textureID data
	void loadRawDataTP(std::vector<Vertex> vert, std::vector<GLuint> ind, const std::vector<std::string> & texture_paths, TextureBank & tb); //Loads vertices, indices and loads textures using TextureBank (RECOMMENDED!)

	void uploadData();

	GLuint getVAOID();

	int getVertexCount();
	int getIndicesCount();
	int getTextureCount();

private:

	void loadVertices(std::vector<Vertex> & vert);
	void loadIndices(std::vector<GLuint> & ind);
	void loadTextures(std::vector<Texture> & tex);

	GLuint _vaoID, _vboID, _eboID;

	int _v_count, _i_count, _t_count;

	void clear();
};

