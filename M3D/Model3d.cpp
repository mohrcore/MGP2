#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "Model3d.h"



Model3d::Model3d()
{
	glGenVertexArrays(1, &_vaoID);
	glGenBuffers(1, &_vboID);
	glGenBuffers(1, &_ivboID);
	glGenBuffers(1, &_tvboID);

	uv_coords = nullptr;
}


Model3d::~Model3d()
{
	glDeleteVertexArrays(1, &_vaoID);
	glDeleteBuffers(1, &_vboID);
	glDeleteBuffers(1, &_ivboID);
	glDeleteBuffers(1, &_tvboID);
	glDeleteTextures(1, &_texID);

	delete[] vertex_data;
	delete[] index_data;
	delete[] uv_coords;
}


void Model3d::loadData(std::vector<Vertex> v, int * id, int ib_size)
{
	delete[] vertex_data;
	delete[] index_data;

	vertex_data = new Vertex[v.size()];
	for (int i = 0; i < v.size(); i++)
	{
		vertex_data[i] = v[i];
	}
	v_count = v.size();

	index_data = new int[ib_size];
	for (int i = 0; i < ib_size; i++)
	{
		index_data[i] = id[i];
	}
	i_count = ib_size;

}

void Model3d::loadTexture(std::string path)
{
	SDL_Surface * texsurf;

	texsurf = IMG_Load(path.c_str());
	if(texsurf == NULL)
		fatal_error("Error opening file: " + path + "\n" + IMG_GetError());

	glGenTextures(1, &_texID);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texsurf->w, texsurf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texsurf->pixels);
	//Linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	//Free memory
	SDL_FreeSurface(texsurf);
}

void Model3d::uploadData() //DEPR
{
	glBindVertexArray(_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(Vertex), vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ivboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_count * sizeof(int), index_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, col));
	if (_texID != NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _tvboID);
		glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(Vertex), vertex_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//void Model3d::draw()
//{
//	glBindVertexArray(_vaoID);
//	//glBindBuffer(GL_ARRAY_BUFFER, _vboID);
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, pos));
//	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *) offsetof(Vertex, col));
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, _texID);
//	glDrawElements(GL_TRIANGLES, i_count, GL_UNSIGNED_INT, 0);
//	//glDisableVertexAttribArray(0);
//	//glDisableVertexAttribArray(1);
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glActiveTexture(0);
//	glBindVertexArray(0);
//}

GLuint Model3d::getVAOID()
{
	return _vaoID;
}

GLuint Model3d::getTextureID()
{
	return _texID;
}

int Model3d::getIndiciesCount()
{
	return i_count;
}