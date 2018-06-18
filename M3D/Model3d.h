#pragma once

#include <GL/glew.h>

#include <cstddef>
#include <vector>

#include "Vertex.h"

class Model3d
{
public:

	Model3d();
	~Model3d();

	void loadData(std::vector<Vertex> v, int * id, int ib_size);
	void loadTexture(std::string path);
	void uploadData();

	//void draw();

	GLuint getVAOID();
	GLuint getTextureID();
	int getIndiciesCount();

	Vertex * vertex_data;
	int * index_data;
	float * uv_coords;

private:

	int v_count, i_count;

	GLuint _vaoID, _vboID, _ivboID, _tvboID;
	GLuint _texID;
};

