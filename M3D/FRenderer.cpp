#include "FRenderer.h"



F_Renderer::F_Renderer()
{
}

F_Renderer::~F_Renderer()
{
}

void F_Renderer::renderData(GLuint vaoID, GLuint eboID, GLuint * texID, unsigned int ind_count, unsigned int tex_count)
{
	glBindVertexArray(vaoID);

	for (int i = 0; i < tex_count; i++) //Binding textures
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texID[i]);
	}

	glDrawElements(GL_TRIANGLES, ind_count, GL_UNSIGNED_INT, 0);

	for (int i = 0; i < tex_count; i++) //Unbinding textures
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glActiveTexture(0);
	glBindVertexArray(0);
}